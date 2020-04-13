#pragma once

#include <array>
#include <algorithm>
#include <functional>

#include "display.h"
#include "textinterface.h"
#include "label.h"
#include "globals.h"
#include "menudefinitioninterface.h"
#include "menuitem.h"

namespace {
class MenuDisplay : public Display, public virtual TextInterface, public virtual MenuDefinitionInterface
{
public:
    void start() override;
    void initScreen() override;
    void update() override;
    void redraw() override;
    void stop() override;

    void rotate(int offset) override;
    void button() override;

    virtual void itemPressed(int index) { (begin()+index)->get().triggered(); }

    MenuDisplay *asMenuDisplay() override { return this; }
    const MenuDisplay *asMenuDisplay() const override { return this; }

    int selectedIndex() const { return m_selectedIndex; }

protected:
    void setSelectedIndex(int selectedIndex) { m_selectedIndex = selectedIndex; }

private:
    Label m_titleLabel{5, 5}; // 230, 25

    static constexpr auto iconWidth = 25;
    static constexpr auto horizontalSpacing = 10;
    static constexpr auto topMargin = 40;
    static constexpr auto lineHeight = 25;
    static constexpr auto verticalSpacing = 3;

    std::array<Label, 10> m_labels {{
        Label{horizontalSpacing + iconWidth, topMargin+(0*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
        Label{horizontalSpacing + iconWidth, topMargin+(1*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
        Label{horizontalSpacing + iconWidth, topMargin+(2*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
        Label{horizontalSpacing + iconWidth, topMargin+(3*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
        Label{horizontalSpacing + iconWidth, topMargin+(4*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
        Label{horizontalSpacing + iconWidth, topMargin+(5*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
        Label{horizontalSpacing + iconWidth, topMargin+(6*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
        Label{horizontalSpacing + iconWidth, topMargin+(7*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
        Label{horizontalSpacing + iconWidth, topMargin+(8*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
        Label{horizontalSpacing + iconWidth, topMargin+(9*(lineHeight+verticalSpacing))}, // 240-(horizontalSpacing*2)-iconWidth, lineHeight
    }};

    std::array<const Icon<24, 24> *, 10> m_icons;

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
}

void MenuDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);

    m_titleLabel.start();
    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    for (auto &label : m_labels)
        label.start();

    for (auto iter = begin(); iter != end(); iter++)
        iter->get().start();

    m_icons.fill(nullptr);
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
            if (m_selectedIndex >= m_scrollOffset + m_labels.size())
                m_scrollOffset = m_selectedIndex - m_labels.size() + 1;
        }
        else
        {
            m_selectedIndex = -1;
            m_scrollOffset = 0;
        }

        for (auto iter = begin(); iter != end(); iter++)
            iter->get().update();
    }
    else
    {
        m_pressed = false;
        if (m_selectedIndex >= 0)
            itemPressed(m_selectedIndex);
    }
}

void MenuDisplay::redraw()
{
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    m_titleLabel.redraw(text());

    const auto menuBegin = begin();
    const auto menuEnd = end();

    auto menuIter = menuBegin + m_scrollOffset;

    auto labelsIter = std::begin(m_labels);

    auto iconsIter = std::begin(m_icons);

    int newHighlightedIndex{-1};

    const auto drawItemRect = [](const auto &label, const auto color){
        tft.drawRect(5,
                     label.y()-1,
                     240 - 10,
                     lineHeight+2,
                     color);
    };

    for (; menuIter != menuEnd && labelsIter != std::end(m_labels); menuIter++, labelsIter++, iconsIter++)
    {
        const auto index = std::distance(menuBegin, menuIter);
        const auto relativeIndex = index - m_scrollOffset;
        const auto selected = index == m_selectedIndex;

        if (selected)
            newHighlightedIndex = relativeIndex;
        else if (relativeIndex == m_highlightedIndex)
            drawItemRect(*labelsIter, TFT_BLACK);

        tft.setTextFont(menuIter->get().font());
        tft.setTextColor(menuIter->get().color(), TFT_BLACK);
        const auto labelDrawn = labelsIter->redraw(menuIter->get().text());

        if (menuIter->get().icon() != *iconsIter)
        {
            auto icon = menuIter->get().icon();
            if (icon)
            {
                tft.setSwapBytes(true);
                tft.pushImage(5, labelsIter->y()+1, icon->WIDTH, icon->HEIGHT, icon->buffer);
                tft.setSwapBytes(false);
            }
            else
                tft.fillRect(5, labelsIter->y()+1, 24, 24, TFT_BLACK);
            *iconsIter = icon;
        }

        if (selected && (labelDrawn || relativeIndex != m_highlightedIndex))
        {
            drawItemRect(*labelsIter, TFT_WHITE);
        }
    }

    for (; labelsIter != std::end(m_labels); labelsIter++, iconsIter++)
    {
        const auto relativeIndex = std::distance(std::begin(m_labels), labelsIter);

        if (relativeIndex == m_highlightedIndex)
            drawItemRect(*labelsIter, TFT_BLACK);

        labelsIter->clear();

        if (*iconsIter)
        {
            tft.fillRect(5, labelsIter->y()+1, 24, 24, TFT_BLACK);
            *iconsIter = nullptr;
        }
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

void MenuDisplay::button()
{
    m_pressed = true;
}
}
