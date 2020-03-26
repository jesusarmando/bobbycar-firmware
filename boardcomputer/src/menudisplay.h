#pragma once

#include <functional>
#include <utility>

#include "display.h"
#include "globals.h"
#include "menuitem.h"

namespace {
class MenuDisplayInterface : public Display
{
public:
    void start() override;
    void update() override;

    void rotate(int offset) override;
    void button(bool pressed) override;

    virtual const char *title() const = 0;

    virtual const std::reference_wrapper<const MenuItemInterface> *begin() const = 0;
    virtual const std::reference_wrapper<const MenuItemInterface> *end() const = 0;

protected:
    void requestRedraw();
    void setSelectedItem(const std::reference_wrapper<const MenuItemInterface> *item);

private:
    void redraw() const;

    const std::reference_wrapper<const MenuItemInterface> *m_prev{}, *m_current{};
    bool m_needsRedraw{};
    bool m_pressed{};
};

template<const char *Ttext, typename ...T>
class MenuDisplay;

template<const char *Ttext, typename T0>
class MenuDisplay<Ttext, T0> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

private:
    T0 item0;

    const std::array<std::reference_wrapper<const MenuItemInterface>, 1> carr{{
        std::cref<MenuItemInterface>(item0)
    }};
};

template<const char *Ttext, typename T0, typename T1>
class MenuDisplay<Ttext, T0, T1> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

private:
    T0 item0;
    T1 item1;

    const std::array<std::reference_wrapper<const MenuItemInterface>, 2> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2>
class MenuDisplay<Ttext, T0, T1, T2> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;

    const std::array<std::reference_wrapper<const MenuItemInterface>, 3> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3>
class MenuDisplay<Ttext, T0, T1, T2, T3> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;

    const std::array<std::reference_wrapper<const MenuItemInterface>, 4> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2),
        std::cref<MenuItemInterface>(item3)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;

    const std::array<std::reference_wrapper<const MenuItemInterface>, 5> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2),
        std::cref<MenuItemInterface>(item3),
        std::cref<MenuItemInterface>(item4)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;

    const std::array<std::reference_wrapper<const MenuItemInterface>, 6> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2),
        std::cref<MenuItemInterface>(item3),
        std::cref<MenuItemInterface>(item4),
        std::cref<MenuItemInterface>(item5)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5, T6> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;
    T6 item6;

    const std::array<std::reference_wrapper<const MenuItemInterface>, 7> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2),
        std::cref<MenuItemInterface>(item3),
        std::cref<MenuItemInterface>(item4),
        std::cref<MenuItemInterface>(item5),
        std::cref<MenuItemInterface>(item6)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5, T6, T7> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;
    T6 item6;
    T7 item7;

    const std::array<std::reference_wrapper<const MenuItemInterface>, 8> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2),
        std::cref<MenuItemInterface>(item3),
        std::cref<MenuItemInterface>(item4),
        std::cref<MenuItemInterface>(item5),
        std::cref<MenuItemInterface>(item6),
        std::cref<MenuItemInterface>(item7)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5, T6, T7, T8> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

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

    const std::array<std::reference_wrapper<const MenuItemInterface>, 9> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2),
        std::cref<MenuItemInterface>(item3),
        std::cref<MenuItemInterface>(item4),
        std::cref<MenuItemInterface>(item5),
        std::cref<MenuItemInterface>(item6),
        std::cref<MenuItemInterface>(item7),
        std::cref<MenuItemInterface>(item8)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

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

    const std::array<std::reference_wrapper<const MenuItemInterface>, 10> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2),
        std::cref<MenuItemInterface>(item3),
        std::cref<MenuItemInterface>(item4),
        std::cref<MenuItemInterface>(item5),
        std::cref<MenuItemInterface>(item6),
        std::cref<MenuItemInterface>(item7),
        std::cref<MenuItemInterface>(item8),
        std::cref<MenuItemInterface>(item9)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

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

    const std::array<std::reference_wrapper<const MenuItemInterface>, 11> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2),
        std::cref<MenuItemInterface>(item3),
        std::cref<MenuItemInterface>(item4),
        std::cref<MenuItemInterface>(item5),
        std::cref<MenuItemInterface>(item6),
        std::cref<MenuItemInterface>(item7),
        std::cref<MenuItemInterface>(item8),
        std::cref<MenuItemInterface>(item9),
        std::cref<MenuItemInterface>(item10)
    }};
};

template<const char *Ttext, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class MenuDisplay<Ttext, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : public MenuDisplay<Ttext>
{
public:
    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

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

    const std::array<std::reference_wrapper<const MenuItemInterface>, 12> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2),
        std::cref<MenuItemInterface>(item3),
        std::cref<MenuItemInterface>(item4),
        std::cref<MenuItemInterface>(item5),
        std::cref<MenuItemInterface>(item6),
        std::cref<MenuItemInterface>(item7),
        std::cref<MenuItemInterface>(item8),
        std::cref<MenuItemInterface>(item9),
        std::cref<MenuItemInterface>(item10),
        std::cref<MenuItemInterface>(item11)
    }};
};

template<const char *Ttext>
class MenuDisplay<Ttext> : public MenuDisplayInterface
{
public:
    const char *title() const override final { return Ttext; }
};

void MenuDisplayInterface::start()
{
    m_current = begin();
    m_needsRedraw = true;
    m_pressed = false;

    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(title(), 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE);

    int y = 45;
    for (auto iter = begin(); iter != end(); iter++)
    {
        tft.drawString((*iter).get().text(), 10, y, 4);

        y += 25;
    }
}

void MenuDisplayInterface::update()
{
    if (m_needsRedraw)
    {
        m_needsRedraw = false;
        redraw();
    }

    if (m_pressed)
        m_current->get().triggered();
}

void MenuDisplayInterface::rotate(int offset)
{
    auto selected = m_current + offset;
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

void MenuDisplayInterface::requestRedraw()
{
    m_needsRedraw = true;
}

void MenuDisplayInterface::setSelectedItem(const std::reference_wrapper<const MenuItemInterface> *item)
{
    m_prev = m_current;
    m_current = item;
    requestRedraw();
}

void MenuDisplayInterface::redraw() const
{
    int y = 45;
    for (auto iter = begin(); iter != end(); iter++)
    {
        if (iter == m_current)
            tft.drawRect(5, y-2, tft.width() - 5, 25, TFT_WHITE);
        else if (iter == m_prev)
            tft.drawRect(5, y-2, tft.width() - 5, 25, TFT_BLACK);

        y += 25;
    }
}
}
