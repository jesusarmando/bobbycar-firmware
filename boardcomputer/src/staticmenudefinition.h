#pragma once

#include "menudefinitioninterface.h"

namespace {
template<typename ...T>
class StaticMenuDefinition;

template<typename T0>
class StaticMenuDefinition<T0> : public virtual MenuDefinitionInterface
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
class StaticMenuDefinition<T0, T1> : public virtual MenuDefinitionInterface
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
class StaticMenuDefinition<T0, T1, T2> : public virtual MenuDefinitionInterface
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
class StaticMenuDefinition<T0, T1, T2, T3> : public virtual MenuDefinitionInterface
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
class StaticMenuDefinition<T0, T1, T2, T3, T4> : public virtual MenuDefinitionInterface
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
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5> : public virtual MenuDefinitionInterface
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
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6> : public virtual MenuDefinitionInterface
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
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7> : public virtual MenuDefinitionInterface
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
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8> : public virtual MenuDefinitionInterface
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
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> : public virtual MenuDefinitionInterface
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
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> : public virtual MenuDefinitionInterface
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
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> : public virtual MenuDefinitionInterface
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

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12> : public virtual MenuDefinitionInterface
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
    T12 item12;

    const std::array<std::reference_wrapper<MenuItem>, 13> arr{{
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
        std::ref<MenuItem>(item11),
        std::ref<MenuItem>(item12)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13> : public virtual MenuDefinitionInterface
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
    T12 item12;
    T13 item13;

    const std::array<std::reference_wrapper<MenuItem>, 14> arr{{
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
        std::ref<MenuItem>(item11),
        std::ref<MenuItem>(item12),
        std::ref<MenuItem>(item13)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14> : public virtual MenuDefinitionInterface
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
    T12 item12;
    T13 item13;
    T14 item14;

    const std::array<std::reference_wrapper<MenuItem>, 15> arr{{
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
        std::ref<MenuItem>(item11),
        std::ref<MenuItem>(item12),
        std::ref<MenuItem>(item13),
        std::ref<MenuItem>(item14)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15> : public virtual MenuDefinitionInterface
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
    T12 item12;
    T13 item13;
    T14 item14;
    T15 item15;

    const std::array<std::reference_wrapper<MenuItem>, 16> arr{{
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
        std::ref<MenuItem>(item11),
        std::ref<MenuItem>(item12),
        std::ref<MenuItem>(item13),
        std::ref<MenuItem>(item14),
        std::ref<MenuItem>(item15)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16> : public virtual MenuDefinitionInterface
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
    T12 item12;
    T13 item13;
    T14 item14;
    T15 item15;
    T16 item16;

    const std::array<std::reference_wrapper<MenuItem>, 17> arr{{
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
        std::ref<MenuItem>(item11),
        std::ref<MenuItem>(item12),
        std::ref<MenuItem>(item13),
        std::ref<MenuItem>(item14),
        std::ref<MenuItem>(item15),
        std::ref<MenuItem>(item16)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17> : public virtual MenuDefinitionInterface
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
    T12 item12;
    T13 item13;
    T14 item14;
    T15 item15;
    T16 item16;
    T17 item17;

    const std::array<std::reference_wrapper<MenuItem>, 18> arr{{
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
        std::ref<MenuItem>(item11),
        std::ref<MenuItem>(item12),
        std::ref<MenuItem>(item13),
        std::ref<MenuItem>(item14),
        std::ref<MenuItem>(item15),
        std::ref<MenuItem>(item16),
        std::ref<MenuItem>(item17)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18> : public virtual MenuDefinitionInterface
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
    T12 item12;
    T13 item13;
    T14 item14;
    T15 item15;
    T16 item16;
    T17 item17;
    T18 item18;

    const std::array<std::reference_wrapper<MenuItem>, 19> arr{{
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
        std::ref<MenuItem>(item11),
        std::ref<MenuItem>(item12),
        std::ref<MenuItem>(item13),
        std::ref<MenuItem>(item14),
        std::ref<MenuItem>(item15),
        std::ref<MenuItem>(item16),
        std::ref<MenuItem>(item17),
        std::ref<MenuItem>(item18)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19> : public virtual MenuDefinitionInterface
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
    T12 item12;
    T13 item13;
    T14 item14;
    T15 item15;
    T16 item16;
    T17 item17;
    T18 item18;
    T19 item19;

    const std::array<std::reference_wrapper<MenuItem>, 20> arr{{
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
        std::ref<MenuItem>(item11),
        std::ref<MenuItem>(item12),
        std::ref<MenuItem>(item13),
        std::ref<MenuItem>(item14),
        std::ref<MenuItem>(item15),
        std::ref<MenuItem>(item16),
        std::ref<MenuItem>(item17),
        std::ref<MenuItem>(item18),
        std::ref<MenuItem>(item19)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20> : public virtual MenuDefinitionInterface
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
    T12 item12;
    T13 item13;
    T14 item14;
    T15 item15;
    T16 item16;
    T17 item17;
    T18 item18;
    T19 item19;
    T20 item20;

    const std::array<std::reference_wrapper<MenuItem>, 21> arr{{
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
        std::ref<MenuItem>(item11),
        std::ref<MenuItem>(item12),
        std::ref<MenuItem>(item13),
        std::ref<MenuItem>(item14),
        std::ref<MenuItem>(item15),
        std::ref<MenuItem>(item16),
        std::ref<MenuItem>(item17),
        std::ref<MenuItem>(item18),
        std::ref<MenuItem>(item19),
        std::ref<MenuItem>(item20)
    }};
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
class StaticMenuDefinition<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21> : public virtual MenuDefinitionInterface
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
    T12 item12;
    T13 item13;
    T14 item14;
    T15 item15;
    T16 item16;
    T17 item17;
    T18 item18;
    T19 item19;
    T20 item20;
    T21 item21;

    const std::array<std::reference_wrapper<MenuItem>, 22> arr{{
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
        std::ref<MenuItem>(item11),
        std::ref<MenuItem>(item12),
        std::ref<MenuItem>(item13),
        std::ref<MenuItem>(item14),
        std::ref<MenuItem>(item15),
        std::ref<MenuItem>(item16),
        std::ref<MenuItem>(item17),
        std::ref<MenuItem>(item18),
        std::ref<MenuItem>(item19),
        std::ref<MenuItem>(item20),
        std::ref<MenuItem>(item21)
    }};
};
}
