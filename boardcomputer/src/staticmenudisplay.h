#pragma once

#include "menudisplay.h"

namespace {
template<typename ...T>
class StaticMenuDisplay;

template<typename T0>
class StaticMenuDisplay<T0> : public MenuDisplay
{
public:
    const std::reference_wrapper<MenuItem> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() const override { return std::end(arr); };

private:
    T0 item0;

    const std::array<std::reference_wrapper<MenuItem>, 1> arr{{
        std::ref<MenuItem>(item0)
    }};
};

template<typename T0, typename T1>
class StaticMenuDisplay<T0, T1> : public MenuDisplay
{
public:
    const std::reference_wrapper<MenuItem> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;

    const std::array<std::reference_wrapper<MenuItem>, 2> arr{{
        std::ref<MenuItem>(item0),
        std::ref<MenuItem>(item1)
    }};
};

template<typename T0, typename T1, typename T2>
class StaticMenuDisplay<T0, T1, T2> : public MenuDisplay
{
public:
    const std::reference_wrapper<MenuItem> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;

    const std::array<std::reference_wrapper<MenuItem>, 3> arr{{
        std::ref<MenuItem>(item0),
        std::ref<MenuItem>(item1),
        std::ref<MenuItem>(item2)
    }};
};

template<typename T0, typename T1, typename T2, typename T3>
class StaticMenuDisplay<T0, T1, T2, T3> : public MenuDisplay
{
public:
    const std::reference_wrapper<MenuItem> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;

    const std::array<std::reference_wrapper<MenuItem>, 4> arr{{
        std::ref<MenuItem>(item0),
        std::ref<MenuItem>(item1),
        std::ref<MenuItem>(item2),
        std::ref<MenuItem>(item3)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
class StaticMenuDisplay<T0, T1, T2, T3, T4> : public MenuDisplay
{
public:
    const std::reference_wrapper<MenuItem> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;

    const std::array<std::reference_wrapper<MenuItem>, 5> arr{{
        std::ref<MenuItem>(item0),
        std::ref<MenuItem>(item1),
        std::ref<MenuItem>(item2),
        std::ref<MenuItem>(item3),
        std::ref<MenuItem>(item4)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
class StaticMenuDisplay<T0, T1, T2, T3, T4, T5> : public MenuDisplay
{
public:
    const std::reference_wrapper<MenuItem> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;

    const std::array<std::reference_wrapper<MenuItem>, 6> arr{{
        std::ref<MenuItem>(item0),
        std::ref<MenuItem>(item1),
        std::ref<MenuItem>(item2),
        std::ref<MenuItem>(item3),
        std::ref<MenuItem>(item4),
        std::ref<MenuItem>(item5)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class StaticMenuDisplay<T0, T1, T2, T3, T4, T5, T6> : public MenuDisplay
{
public:
    const std::reference_wrapper<MenuItem> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;
    T6 item6;

    const std::array<std::reference_wrapper<MenuItem>, 7> arr{{
        std::ref<MenuItem>(item0),
        std::ref<MenuItem>(item1),
        std::ref<MenuItem>(item2),
        std::ref<MenuItem>(item3),
        std::ref<MenuItem>(item4),
        std::ref<MenuItem>(item5),
        std::ref<MenuItem>(item6)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class StaticMenuDisplay<T0, T1, T2, T3, T4, T5, T6, T7> : public MenuDisplay
{
public:
    const std::reference_wrapper<MenuItem> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() const override { return std::end(arr); };

private:
    T0 item0;
    T1 item1;
    T2 item2;
    T3 item3;
    T4 item4;
    T5 item5;
    T6 item6;
    T7 item7;

    const std::array<std::reference_wrapper<MenuItem>, 8> arr{{
        std::ref<MenuItem>(item0),
        std::ref<MenuItem>(item1),
        std::ref<MenuItem>(item2),
        std::ref<MenuItem>(item3),
        std::ref<MenuItem>(item4),
        std::ref<MenuItem>(item5),
        std::ref<MenuItem>(item6),
        std::ref<MenuItem>(item7)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class StaticMenuDisplay<T0, T1, T2, T3, T4, T5, T6, T7, T8> : public MenuDisplay
{
public:
    const std::reference_wrapper<MenuItem> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() const override { return std::end(arr); };

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

    const std::array<std::reference_wrapper<MenuItem>, 9> arr{{
        std::ref<MenuItem>(item0),
        std::ref<MenuItem>(item1),
        std::ref<MenuItem>(item2),
        std::ref<MenuItem>(item3),
        std::ref<MenuItem>(item4),
        std::ref<MenuItem>(item5),
        std::ref<MenuItem>(item6),
        std::ref<MenuItem>(item7),
        std::ref<MenuItem>(item8)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class StaticMenuDisplay<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : public MenuDisplay
{
public:
    const std::reference_wrapper<MenuItem> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() const override { return std::end(arr); };

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

    const std::array<std::reference_wrapper<MenuItem>, 10> arr{{
        std::ref<MenuItem>(item0),
        std::ref<MenuItem>(item1),
        std::ref<MenuItem>(item2),
        std::ref<MenuItem>(item3),
        std::ref<MenuItem>(item4),
        std::ref<MenuItem>(item5),
        std::ref<MenuItem>(item6),
        std::ref<MenuItem>(item7),
        std::ref<MenuItem>(item8),
        std::ref<MenuItem>(item9)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class StaticMenuDisplay<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : public MenuDisplay
{
public:
    const std::reference_wrapper<MenuItem> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() const override { return std::end(arr); };

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

    const std::array<std::reference_wrapper<MenuItem>, 11> arr{{
        std::ref<MenuItem>(item0),
        std::ref<MenuItem>(item1),
        std::ref<MenuItem>(item2),
        std::ref<MenuItem>(item3),
        std::ref<MenuItem>(item4),
        std::ref<MenuItem>(item5),
        std::ref<MenuItem>(item6),
        std::ref<MenuItem>(item7),
        std::ref<MenuItem>(item8),
        std::ref<MenuItem>(item9),
        std::ref<MenuItem>(item10)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class StaticMenuDisplay<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : public MenuDisplay
{
public:
    const std::reference_wrapper<MenuItem> *begin() const override { return std::begin(arr); };
    const std::reference_wrapper<MenuItem> *end() const override { return std::end(arr); };

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

    const std::array<std::reference_wrapper<MenuItem>, 12> arr{{
        std::ref<MenuItem>(item0),
        std::ref<MenuItem>(item1),
        std::ref<MenuItem>(item2),
        std::ref<MenuItem>(item3),
        std::ref<MenuItem>(item4),
        std::ref<MenuItem>(item5),
        std::ref<MenuItem>(item6),
        std::ref<MenuItem>(item7),
        std::ref<MenuItem>(item8),
        std::ref<MenuItem>(item9),
        std::ref<MenuItem>(item10),
        std::ref<MenuItem>(item11)
    }};
};
}
