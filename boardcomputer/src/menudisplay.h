#pragma once

#include <array>
#include <algorithm>
#include <functional>
#include <utility>

#include "display.h"
#include "titleinterface.h"
#include "actions/actioninterface.h"
#include "label.h"
#include "globals.h"
#include "menuitems/menuitem.h"

namespace {
class MenuDisplay : public Display, public virtual TitleInterface, public virtual ActionInterface
{
public:
    void start() override;
    void update() override;
    void redraw() override;
    void stop() override;

    void rotate(int offset) override;
    void button(bool pressed) override;

    void triggered() override { (begin()+m_selectedIndex)->get().triggered(); }

    virtual const std::reference_wrapper<MenuItem> *begin() const = 0;
    virtual const std::reference_wrapper<MenuItem> *end() const = 0;

    MenuDisplay *asMenuDisplay() override { return this; }
    const MenuDisplay *asMenuDisplay() const override { return this; }

    int selectedIndex() const { return m_selectedIndex; }

protected:
    void setSelectedIndex(int selectedIndex) { m_selectedIndex = selectedIndex; }

private:
    Label m_titleLabel{5, 5, 230, 25};

    static constexpr auto horizontalSpacing = 10;
    static constexpr auto topMargin = 40;
    static constexpr auto lineHeight = 25;
    static constexpr auto verticalSpacing = 3;

    std::array<Label, 10> m_labels {{
        Label{horizontalSpacing, topMargin+(0*(lineHeight+verticalSpacing)), 240-(horizontalSpacing*2), lineHeight},
        Label{horizontalSpacing, topMargin+(1*(lineHeight+verticalSpacing)), 240-(horizontalSpacing*2), lineHeight},
        Label{horizontalSpacing, topMargin+(2*(lineHeight+verticalSpacing)), 240-(horizontalSpacing*2), lineHeight},
        Label{horizontalSpacing, topMargin+(3*(lineHeight+verticalSpacing)), 240-(horizontalSpacing*2), lineHeight},
        Label{horizontalSpacing, topMargin+(4*(lineHeight+verticalSpacing)), 240-(horizontalSpacing*2), lineHeight},
        Label{horizontalSpacing, topMargin+(5*(lineHeight+verticalSpacing)), 240-(horizontalSpacing*2), lineHeight},
        Label{horizontalSpacing, topMargin+(6*(lineHeight+verticalSpacing)), 240-(horizontalSpacing*2), lineHeight},
        Label{horizontalSpacing, topMargin+(7*(lineHeight+verticalSpacing)), 240-(horizontalSpacing*2), lineHeight},
        Label{horizontalSpacing, topMargin+(8*(lineHeight+verticalSpacing)), 240-(horizontalSpacing*2), lineHeight},
        Label{horizontalSpacing, topMargin+(9*(lineHeight+verticalSpacing)), 240-(horizontalSpacing*2), lineHeight},
    }};

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

    tft.fillScreen(TFT_BLACK);

    m_titleLabel.start();
    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    for (auto &label : m_labels)
        label.start();

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
    else if (m_selectedIndex >= 0)
    {
        m_pressed = false;
        triggered();
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

    auto labelsIter = std::begin(m_labels);

    int newHighlightedIndex{-1};

    const auto drawItemRect = [](const auto &label, const auto color){
        tft.drawRect(label.x()-5,
                     label.y()-2,
                     label.width()+10,
                     label.height()+2,
                     color);
    };

    for (; menuIter != menuEnd && labelsIter != std::end(m_labels); menuIter++, labelsIter++)
    {
        const auto index = std::distance(menuBegin, menuIter);
        const auto relativeIndex = index - m_scrollOffset;
        const auto selected = index == m_selectedIndex;

        bool forceLabelRedraw{};

        if (selected)
            newHighlightedIndex = relativeIndex;
        else if (relativeIndex == m_highlightedIndex)
        {
            drawItemRect(*labelsIter, TFT_BLACK);
            forceLabelRedraw = true;
        }

        tft.setTextFont(menuIter->get().font());
        tft.setTextColor(menuIter->get().color(), TFT_BLACK);
        const auto labelDrawn = labelsIter->redraw(menuIter->get().title(), forceLabelRedraw);

        if (selected && (labelDrawn || relativeIndex != m_highlightedIndex))
        {
            drawItemRect(*labelsIter, TFT_WHITE);
        }
    }

    for (; labelsIter != std::end(m_labels); labelsIter++)
    {
        const auto relativeIndex = std::distance(std::begin(m_labels), labelsIter);

        if (relativeIndex == m_highlightedIndex)
            drawItemRect(*labelsIter, TFT_BLACK);

        labelsIter->clear();
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
