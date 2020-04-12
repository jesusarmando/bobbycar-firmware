#pragma once

#include <WString.h>

namespace {
class TitleInterface {
public:
    virtual String title() const = 0;
};

template<const char *Ttext>
class StaticTitle : public virtual TitleInterface
{
public:
    static constexpr const char *STATIC_TEXT = Ttext;

    String title() const override { return Ttext; }
};

class DynamicTitle : public virtual TitleInterface
{
public:
    String title() const override { return m_title; }
    void setTitle(const String &title) { m_title = title; }

private:
    String m_title;
};
}
