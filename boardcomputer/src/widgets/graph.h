#pragma once

#include <functional>

#include "globals.h"
#include "ringbuffer.h"
#include "label.h"
//#include "utils.h"

namespace {
template<size_t LENGTH, size_t COUNT>
class GraphBase
{
    static constexpr int labelOffset = -5;
    static constexpr int leftMargin = 40;

public:
    static constexpr int WIDTH = LENGTH+40;

    GraphBase(int x, int y, int height);

    void start(const std::array<std::reference_wrapper<const ring_buffer<float, LENGTH>>, COUNT> &buffers);
    void redraw(const std::array<std::reference_wrapper<const ring_buffer<float, LENGTH>>, COUNT> &buffers);

private:
    void render(const std::array<std::reference_wrapper<const ring_buffer<float, LENGTH>>, COUNT> &buffers, bool delta);

    const int m_x, m_y, m_height;

    std::array<Label, 5> m_labels;

    std::array<std::array<int, COUNT>, LENGTH> m_lastPixels;

    float m_min;
    float m_max;
};

using Graph=GraphBase<200, 1>;

template<size_t LENGTH, size_t COUNT>
GraphBase<LENGTH, COUNT>::GraphBase(int x, int y, int height) :
    m_x{x}, m_y{y}, m_height{height},
    m_labels{
        Label{m_x, int(m_y+(m_height/4.f*0)+labelOffset)},
        Label{m_x, int(m_y+(m_height/4.f*1)+labelOffset)},
        Label{m_x, int(m_y+(m_height/4.f*2)+labelOffset)},
        Label{m_x, int(m_y+(m_height/4.f*3)+labelOffset)},
        Label{m_x, int(m_y+(m_height/4.f*4)+labelOffset)},
    }
{
}

template<size_t LENGTH, size_t COUNT>
void GraphBase<LENGTH, COUNT>::start(const std::array<std::reference_wrapper<const ring_buffer<float, LENGTH>>, COUNT> &buffers)
{
    m_min = 0.f;
    m_max = 10.f;

    tft.drawFastVLine(m_x+leftMargin-1, m_y, m_height, TFT_WHITE);

    for (auto iter = std::begin(m_labels); iter != std::end(m_labels); iter++)
    {
        tft.drawFastHLine(m_x+leftMargin-5, float(m_y)+(float(m_height)/(m_labels.size()-1)*std::distance(std::begin(m_labels), iter)), 4, TFT_WHITE);
        iter->start();
    }

    render(buffers, false);
}

template<size_t LENGTH, size_t COUNT>
void GraphBase<LENGTH, COUNT>::redraw(const std::array<std::reference_wrapper<const ring_buffer<float, LENGTH>>, COUNT> &buffers)
{
    render(buffers, true);
}

template<size_t LENGTH, size_t COUNT>
void GraphBase<LENGTH, COUNT>::render(const std::array<std::reference_wrapper<const ring_buffer<float, LENGTH>>, COUNT> &buffers, bool delta)
{
    float min, max;
    bool first{true};
    for (const ring_buffer<float, LENGTH> &buffer : buffers)
    {
        auto minmax = std::minmax_element(std::cbegin(buffer), std::cend(buffer));

        if (first || *minmax.first < min)
            min = *minmax.first;
        if (first || *minmax.second > max)
            max = *minmax.second;
        first = false;
    }

    if (min < m_min)
        m_min = min*0.9f;
    else if (min > m_min*1.1f)
        m_min = min*1.1f;

    if (max > m_max)
        m_max = max*1.1f;
    else if (max < m_max*0.9f)
        m_max = max*1.1f;

    if (m_max-m_min < 2.f)
    {
        m_min-=1.f;
        m_max+=1.f;
    }

    if (m_min > 0 && m_max > 0)
        m_min = 0;
    if (m_min < 0 && m_max < 0)
        m_max = 0;

    tft.setTextFont(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    for (auto iter = std::begin(m_labels); iter != std::end(m_labels); iter++)
        iter->redraw(String(int(m_max+((m_min-m_max)/(m_labels.size()-1)*std::distance(std::begin(m_labels), iter)))));

    int x{leftMargin};
    for (auto pixelsIter = std::begin(m_lastPixels); pixelsIter!=std::end(m_lastPixels); pixelsIter++)
    {
        const auto index0 = std::distance(std::begin(m_lastPixels), pixelsIter);
        auto &pixels = *pixelsIter;

        for (auto iter = std::begin(pixels); iter != std::end(pixels); iter++)
        {
            const auto index1 = std::distance(std::begin(pixels), iter);

            const std::reference_wrapper<const ring_buffer<float, LENGTH>> &ref = *(std::begin(buffers)+index1);
            const ring_buffer<float, LENGTH> &buffer = ref.get();

            const float &val = *(std::begin(buffer)+index0);

            int y = scaleBetween<float>(val, m_min, m_max, m_y+m_height-1, m_y+1);
            if (!delta || *iter != y)
            {
                if (delta)
                    tft.drawFastVLine(x, *iter-1, 3, TFT_BLACK);
                tft.drawFastVLine(x, y-1, 3, TFT_WHITE);
                *iter = y;
            }
        }

        x++;
    }
}
}
