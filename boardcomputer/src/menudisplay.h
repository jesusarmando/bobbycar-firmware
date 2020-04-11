#pragma once

#include <array>
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

    const std::reference_wrapper<MenuItemInterface> *selectedItem() const { return m_selected; }

protected:
    void setSelectedItem(const std::reference_wrapper<MenuItemInterface> *item);

private:
    Label<5, 5, 230, 25> m_titleLabel;
    int m_lastY;

    const std::reference_wrapper<MenuItemInterface> *m_selected{};
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
    m_selected = begin();
    m_pressed = false;
    m_lastY = 0;

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
        for (auto iter = begin(); iter != end(); iter++)
            iter->get().update();
    }
    else
    {
        m_pressed = false;
        m_selected->get().triggered();
    }
}

void MenuDisplayInterface::redraw()
{
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    m_titleLabel.repaint(title());

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    const auto * const selected = m_selected;

    int y = 45;
    for (auto iter = begin(); iter != end(); iter++)
        iter->get().redraw(y, iter == selected);

    if (y < m_lastY)
        tft.fillRect(0, y, tft.width(), m_lastY - y, TFT_BLACK);

    m_lastY = y;
}

void MenuDisplayInterface::stop()
{
    for (auto iter = begin(); iter != end(); iter++)
        iter->get().stop();
}

void MenuDisplayInterface::rotate(int offset)
{
    auto selected = m_selected + offset;
    if (selected < begin())
        selected = begin();
    if (selected >= end())
        selected = end() - 1;
    setSelectedItem(selected);
}

void MenuDisplayInterface::button(bool pressed)
{
    if (!pressed)
        m_pressed = true;
}

void MenuDisplayInterface::setSelectedItem(const std::reference_wrapper<MenuItemInterface> *item)
{
    m_selected = item;
}
}
