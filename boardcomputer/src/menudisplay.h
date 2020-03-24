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
    void update() override final;
    void redraw() override final;

    int framerate() const override final { return 60; }

    void rotate(int offset) override;
    void button(bool pressed) override;

    virtual const char *title() const = 0;

    virtual const std::reference_wrapper<const MenuItemInterface> *begin() const = 0;
    virtual const std::reference_wrapper<const MenuItemInterface> *end() const = 0;

protected:
    const std::reference_wrapper<const MenuItemInterface> *m_current{};
    bool m_needsRedraw{};

private:
    bool m_pressed{};

    void redrawMenu() const;
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
    Display::start();

    tft.setRotation(0);
    if (!m_current)
        m_current = begin();

    m_needsRedraw = true;
    m_pressed = false;
}

void MenuDisplayInterface::update()
{
    if (m_pressed)
        m_current->get().triggered();
}

void MenuDisplayInterface::redraw()
{
    if (m_needsRedraw)
    {
        redrawMenu();
        m_needsRedraw = false;
    }
}

void MenuDisplayInterface::rotate(int offset)
{
    auto selected = m_current + offset;
    if (selected < begin())
        selected = begin();
    if (selected >= end())
        selected = end() - 1;
    m_current = selected;
    m_needsRedraw = true;
}

void MenuDisplayInterface::button(bool pressed)
{
    if (!pressed)
        m_pressed = true;
}

void MenuDisplayInterface::redrawMenu() const
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(title(), 5, 5, 4);

    int y = 50;
    for (auto iter = begin(); iter != end(); iter++)
    {
        const auto selected = iter == m_current;

        tft.setTextColor(selected ? TFT_ORANGE : TFT_WHITE);

        tft.drawString((*iter).get().text(), 10, y, 4);

        if (selected)
            tft.drawRect(5, y-2, tft.width() - 5, 25, TFT_WHITE);

        y += 25;
    }
}
}
