#pragma once

#include <WString.h>

namespace {
class TextInterface {
public:
    virtual String text() const = 0;
};

template<const char *Ttext>
class StaticText : public virtual TextInterface
{
public:
    static constexpr const char *STATIC_TEXT = Ttext;

    String text() const override { return Ttext; }
};

class ChangeableText : public virtual TextInterface
{
public:
    String text() const override { return m_title; }
    void setTitle(const String &title) { m_title = title; }

private:
    String m_title;
};

template<const char *Ttext, typename Ttype, Ttype *Tptr, typename TreturnType, TreturnType (Ttype::*Tmethod)()>
class StatusTextHelper : public virtual TextInterface
{
public:
    String text() const override { return String{Ttext} + (Tptr->*Tmethod)(); }
};

template<typename T>
class CachedText : public virtual T
{
public:
    String text() const override
    {
        if (!m_loaded)
        {
            m_text = T::text();
            m_loaded = true;
        }

        return m_text;
    }

private:
    mutable bool m_loaded{};
    mutable String m_text;
};

template<typename T>
class StaticallyCachedText : public virtual T
{
public:
    String text() const override
    {
        static const auto text = T::text();
        return text;
    }
};
}
