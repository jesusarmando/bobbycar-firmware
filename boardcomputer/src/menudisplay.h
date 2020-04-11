#pragma once

#include <array>
#include <algorithm>
#include <functional>
#include <utility>

#include "display.h"
#include "label.h"
#include "globals.h"
#include "menuitem.h"
#include "titleinterface.h"

namespace {
class MenuDisplay : public Display, public virtual TitleInterface
{
public:
    void start() override;
    void update() override;
    void redraw() override;
    void stop() override;

    void rotate(int offset) override;
    void button(bool pressed) override;

    virtual const std::reference_wrapper<MenuItem> *begin() const = 0;
    virtual const std::reference_wrapper<MenuItem> *end() const = 0;

    MenuDisplay *asMenuDisplay() override { return this; }
    const MenuDisplay *asMenuDisplay() const override { return this; }

    int selectedIndex() const { return m_selectedIndex; }

protected:
    void setSelectedIndex(int selectedIndex) { m_selectedIndex = selectedIndex; }

private:
    Label<5, 5, 230, 25> m_titleLabel;

    Label<10, 45+(0*27), 220, 25> m_label0;
    Label<10, 45+(1*27), 220, 25> m_label1;
    Label<10, 45+(2*27), 220, 25> m_label2;
    Label<10, 45+(3*27), 220, 25> m_label3;
    Label<10, 45+(4*27), 220, 25> m_label4;
    Label<10, 45+(5*27), 220, 25> m_label5;
    Label<10, 45+(6*27), 220, 25> m_label6;
    Label<10, 45+(7*27), 220, 25> m_label7;
    Label<10, 45+(8*27), 220, 25> m_label8;
    Label<10, 45+(9*27), 220, 25> m_label9;

    std::array<std::reference_wrapper<LabelInterface>, 10> getLabels()
    {
        return {
            std::ref<LabelInterface>(m_label0),
            std::ref<LabelInterface>(m_label1),
            std::ref<LabelInterface>(m_label2),
            std::ref<LabelInterface>(m_label3),
            std::ref<LabelInterface>(m_label4),
            std::ref<LabelInterface>(m_label5),
            std::ref<LabelInterface>(m_label6),
            std::ref<LabelInterface>(m_label7),
            std::ref<LabelInterface>(m_label8),
            std::ref<LabelInterface>(m_label9)
        };
    }

    int m_selectedIndex;
    int m_scrollOffset;
    int m_highlightedIndex;

    int m_rotateOffset;
    bool m_pressed;
};

void MenuDisplay::start()
{
    m_selectedIndex = 0;
    m_scrollOffset = 0;
    m_highlightedIndex = -1;

    m_rotateOffset = 0;
    m_pressed = false;

    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);

    m_titleLabel.start();
    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    for (auto iter = begin(); iter != end(); iter++)
        iter->get().start();
}

void MenuDisplay::update()
{
    if (!m_pressed)
    {
        const auto offset = m_rotateOffset;
        m_rotateOffset = 0;

        const auto itemCount = std::distance(begin(), end());
        if (itemCount)
        {
            if (m_selectedIndex == -1)
                m_selectedIndex = 0;

            m_selectedIndex = m_selectedIndex + offset;

            if (m_selectedIndex < 0)
                m_selectedIndex = 0;
            if (m_selectedIndex >= itemCount)
                m_selectedIndex = itemCount - 1;

            if (m_selectedIndex < m_scrollOffset)
                m_scrollOffset = m_selectedIndex;
            if (m_selectedIndex >= m_scrollOffset + getLabels().size())
                m_scrollOffset = m_selectedIndex - getLabels().size() + 1;
        }
        else
        {
            m_selectedIndex = -1;
            m_scrollOffset = 0;
        }

        for (auto iter = begin(); iter != end(); iter++)
            iter->get().update();
    }
    else if (m_selectedIndex >= 0)
    {
        m_pressed = false;
        (begin()+m_selectedIndex)->get().triggered();
    }
}

void MenuDisplay::redraw()
{
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    m_titleLabel.redraw(title());

    const auto menuBegin = begin();
    const auto menuEnd = end();

    auto menuIter = menuBegin + m_scrollOffset;

    const auto labels = getLabels();

    auto labelsIter = std::begin(labels);

    int newHighlightedIndex{-1};

    const auto drawItemRect = [](const LabelInterface &label, const auto color){
        tft.drawRect(label.getX()-5,
                     label.getY()-2,
                     label.getWidth()+10,
                     label.getHeight()+2,
                     color);
    };

    for (; menuIter != menuEnd && labelsIter != std::end(labels); menuIter++, labelsIter++)
    {
        const auto index = std::distance(menuBegin, menuIter);
        const auto relativeIndex = index - m_scrollOffset;
        const auto selected = index == m_selectedIndex;

        bool forceLabelRedraw{};

        if (selected)
            newHighlightedIndex = relativeIndex;
        else if (relativeIndex == m_highlightedIndex)
        {
            drawItemRect(labelsIter->get(), TFT_BLACK);
            forceLabelRedraw = true;
        }

        tft.setTextFont(menuIter->get().font());
        tft.setTextColor(menuIter->get().color(), TFT_BLACK);
        const auto labelDrawn = labelsIter->get().redraw(menuIter->get().title(), forceLabelRedraw);

        if (selected && (labelDrawn || relativeIndex != m_highlightedIndex))
        {
            drawItemRect(labelsIter->get(), TFT_WHITE);
        }
    }

    for (; labelsIter != std::end(labels); labelsIter++)
    {
        const auto relativeIndex = std::distance(std::begin(labels), labelsIter);

        if (relativeIndex == m_highlightedIndex)
            drawItemRect(labelsIter->get(), TFT_BLACK);

        labelsIter->get().clear();
    }

    m_highlightedIndex = newHighlightedIndex;
}

void MenuDisplay::stop()
{
    for (auto iter = begin(); iter != end(); iter++)
        iter->get().stop();
}

void MenuDisplay::rotate(int offset)
{
    m_rotateOffset += offset;
}

void MenuDisplay::button(bool pressed)
{
    if (!pressed)
        m_pressed = true;
}
}
