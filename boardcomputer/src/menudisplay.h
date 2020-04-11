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
class MenuDisplayInterface : public Display, public virtual TitleInterface
{
public:
    void start() override;
    void update() override;
    void redraw() override;
    void stop() override;

    void rotate(int offset) override;
    void button(bool pressed) override;

    virtual const std::reference_wrapper<MenuItemInterface> *begin() const = 0;
    virtual const std::reference_wrapper<MenuItemInterface> *end() const = 0;

    MenuDisplayInterface *asMenuDisplayInterface() override { return this; }
    const MenuDisplayInterface *asMenuDisplayInterface() const override { return this; }

    int selectedIndex() const { return m_selectedIndex; }

protected:
    void setSelectedIndex(int selectedIndex) { m_selectedIndex = selectedIndex; }

private:
    int m_rotateOffset;

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
    bool m_pressed{};
};

template<const char *Ttext, typename ...T>
class MenuDisplay;

template<const char *Ttext, typename T0>
class MenuDisplay<Ttext, T0> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    T0 item0;

    const std::array<std::reference_wrapper<MenuItemInterface>, 1> arr{{
        std::ref<MenuItemInterface>(item0)
    }};
};

template<const char *Ttext, typename T0, typename T1>
class MenuDisplay<Ttext, T0, T1> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;

    const std::array<std::reference_wrapper<MenuItemInterface>, 2> arr{{
        std::ref<MenuItemInterface>(item0),
        std::ref<MenuItemInterface>(item1)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2>
class MenuDisplay<Ttext, T0, T1, T2> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;

    const std::array<std::reference_wrapper<MenuItemInterface>, 3> arr{{
        std::ref<MenuItemInterface>(item0),
        std::ref<MenuItemInterface>(item1),
        std::ref<MenuItemInterface>(item2)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3>
class MenuDisplay<Ttext, T0, T1, T2, T3> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;

    const std::array<std::reference_wrapper<MenuItemInterface>, 4> arr{{
        std::ref<MenuItemInterface>(item0),
        std::ref<MenuItemInterface>(item1),
        std::ref<MenuItemInterface>(item2),
        std::ref<MenuItemInterface>(item3)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;

    const std::array<std::reference_wrapper<MenuItemInterface>, 5> arr{{
        std::ref<MenuItemInterface>(item0),
        std::ref<MenuItemInterface>(item1),
        std::ref<MenuItemInterface>(item2),
        std::ref<MenuItemInterface>(item3),
        std::ref<MenuItemInterface>(item4)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;

    const std::array<std::reference_wrapper<MenuItemInterface>, 6> arr{{
        std::ref<MenuItemInterface>(item0),
        std::ref<MenuItemInterface>(item1),
        std::ref<MenuItemInterface>(item2),
        std::ref<MenuItemInterface>(item3),
        std::ref<MenuItemInterface>(item4),
        std::ref<MenuItemInterface>(item5)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5, T6> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;
    T6 item6;

    const std::array<std::reference_wrapper<MenuItemInterface>, 7> arr{{
        std::ref<MenuItemInterface>(item0),
        std::ref<MenuItemInterface>(item1),
        std::ref<MenuItemInterface>(item2),
        std::ref<MenuItemInterface>(item3),
        std::ref<MenuItemInterface>(item4),
        std::ref<MenuItemInterface>(item5),
        std::ref<MenuItemInterface>(item6)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5, T6, T7> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;
    T6 item6;
    T7 item7;

    const std::array<std::reference_wrapper<MenuItemInterface>, 8> arr{{
        std::ref<MenuItemInterface>(item0),
        std::ref<MenuItemInterface>(item1),
        std::ref<MenuItemInterface>(item2),
        std::ref<MenuItemInterface>(item3),
        std::ref<MenuItemInterface>(item4),
        std::ref<MenuItemInterface>(item5),
        std::ref<MenuItemInterface>(item6),
        std::ref<MenuItemInterface>(item7)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5, T6, T7, T8> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;
    T6 item6;
    T7 item7;
    T8 item8;

    const std::array<std::reference_wrapper<MenuItemInterface>, 9> arr{{
        std::ref<MenuItemInterface>(item0),
        std::ref<MenuItemInterface>(item1),
        std::ref<MenuItemInterface>(item2),
        std::ref<MenuItemInterface>(item3),
        std::ref<MenuItemInterface>(item4),
        std::ref<MenuItemInterface>(item5),
        std::ref<MenuItemInterface>(item6),
        std::ref<MenuItemInterface>(item7),
        std::ref<MenuItemInterface>(item8)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;
    T6 item6;
    T7 item7;
    T8 item8;
    T9 item9;

    const std::array<std::reference_wrapper<MenuItemInterface>, 10> arr{{
        std::ref<MenuItemInterface>(item0),
        std::ref<MenuItemInterface>(item1),
        std::ref<MenuItemInterface>(item2),
        std::ref<MenuItemInterface>(item3),
        std::ref<MenuItemInterface>(item4),
        std::ref<MenuItemInterface>(item5),
        std::ref<MenuItemInterface>(item6),
        std::ref<MenuItemInterface>(item7),
        std::ref<MenuItemInterface>(item8),
        std::ref<MenuItemInterface>(item9)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;
    T6 item6;
    T7 item7;
    T8 item8;
    T9 item9;
    T10 item10;

    const std::array<std::reference_wrapper<MenuItemInterface>, 11> arr{{
        std::ref<MenuItemInterface>(item0),
        std::ref<MenuItemInterface>(item1),
        std::ref<MenuItemInterface>(item2),
        std::ref<MenuItemInterface>(item3),
        std::ref<MenuItemInterface>(item4),
        std::ref<MenuItemInterface>(item5),
        std::ref<MenuItemInterface>(item6),
        std::ref<MenuItemInterface>(item7),
        std::ref<MenuItemInterface>(item8),
        std::ref<MenuItemInterface>(item9),
        std::ref<MenuItemInterface>(item10)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<MenuItemInterface> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItemInterface> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;
    T6 item6;
    T7 item7;
    T8 item8;
    T9 item9;
    T10 item10;
    T11 item11;

    const std::array<std::reference_wrapper<MenuItemInterface>, 12> arr{{
        std::ref<MenuItemInterface>(item0),
        std::ref<MenuItemInterface>(item1),
        std::ref<MenuItemInterface>(item2),
        std::ref<MenuItemInterface>(item3),
        std::ref<MenuItemInterface>(item4),
        std::ref<MenuItemInterface>(item5),
        std::ref<MenuItemInterface>(item6),
        std::ref<MenuItemInterface>(item7),
        std::ref<MenuItemInterface>(item8),
        std::ref<MenuItemInterface>(item9),
        std::ref<MenuItemInterface>(item10),
        std::ref<MenuItemInterface>(item11)
    }};
};

template<const char *Ttext>
class MenuDisplay<Ttext> : public MenuDisplayInterface, public TitleImpl<Ttext>
{
};

void MenuDisplayInterface::start()
{
    m_selectedIndex = 0;
    m_scrollOffset = 0;
    m_highlightedIndex = -1;
    m_pressed = false;

    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);

    m_titleLabel.start();
    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    for (auto iter = begin(); iter != end(); iter++)
        iter->get().start();
}

void MenuDisplayInterface::update()
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

void MenuDisplayInterface::redraw()
{
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    m_titleLabel.redraw(title());

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

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

void MenuDisplayInterface::stop()
{
    for (auto iter = begin(); iter != end(); iter++)
        iter->get().stop();
}

void MenuDisplayInterface::rotate(int offset)
{
    m_rotateOffset += offset;
}

void MenuDisplayInterface::button(bool pressed)
{
    if (!pressed)
        m_pressed = true;
}
}
