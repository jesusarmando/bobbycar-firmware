#pragma once

#include "demodisplay.h"
#include "actions/switchscreenaction.h"
#include "textinterface.h"
#include "label.h"
#include "globals.h"
#include "statistics.h"

namespace {
class GraphsMenu;
}

namespace {
class GraphDisplay : public DemoDisplay, public SwitchScreenAction<GraphsMenu>, public virtual TextInterface, public virtual StatisticsInterface
{
    using Base = DemoDisplay;

public:
    void initScreen() override;
    void redraw() override;

private:
    void render(bool delta);

    static constexpr int screenHeight = 320, topMargin = 40, bottomMargin = 10, labelOffset = -5;
    static constexpr int graphHeight = screenHeight-topMargin-bottomMargin;

    Label m_titleLabel{5, 5}; // 230, 25

    std::array<Label, 9> m_labels{{
        Label{0, int(topMargin+(graphHeight/8.f*0)+labelOffset)},
        Label{0, int(topMargin+(graphHeight/8.f*1)+labelOffset)},
        Label{0, int(topMargin+(graphHeight/8.f*2)+labelOffset)},
        Label{0, int(topMargin+(graphHeight/8.f*3)+labelOffset)},
        Label{0, int(topMargin+(graphHeight/8.f*4)+labelOffset)},
        Label{0, int(topMargin+(graphHeight/8.f*5)+labelOffset)},
        Label{0, int(topMargin+(graphHeight/8.f*6)+labelOffset)},
        Label{0, int(topMargin+(graphHeight/8.f*7)+labelOffset)},
        Label{0, int(topMargin+(graphHeight/8.f*8)+labelOffset)}
    }};

    std::array<int, 200> m_lastPixels;

    float m_min{0.};
    float m_max{1000.};
};

void GraphDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);

    m_titleLabel.start();
    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.drawFastVLine(39, topMargin, tft.height()-topMargin-bottomMargin, TFT_WHITE);

    for (auto iter = std::begin(m_labels); iter != std::end(m_labels); iter++)
    {
        tft.drawFastHLine(35, float(topMargin)+(float(graphHeight)/(m_labels.size()-1)*std::distance(std::begin(m_labels), iter)), 4, TFT_WHITE);
        iter->start();
    }

    render(false);
}

void GraphDisplay::redraw()
{
    render(true);
}

void GraphDisplay::render(bool delta)
{
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    m_titleLabel.redraw(text());

    tft.setTextFont(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    for (auto iter = std::begin(m_labels); iter != std::end(m_labels); iter++)
        iter->redraw(String(int(m_max+((m_min-m_max)/(m_labels.size()-1)*std::distance(std::begin(m_labels), iter)))));

    int x{40};
    auto iter = std::cbegin(getBuffer());
    auto iter1 = std::begin(m_lastPixels);
    for (; iter != std::end(getBuffer()); ++iter, iter1++)
    {
        int y = scaleBetween<float>(*iter, m_min, m_max, screenHeight-bottomMargin, topMargin);
        if (!delta || *iter1 != y)
        {
            if (delta)
                tft.drawFastVLine(x, *iter1-1, 3, TFT_BLACK);
            tft.drawFastVLine(x, y-1, 3, TFT_WHITE);
            *iter1 = y;
        }
        x++;
    }
}
}
