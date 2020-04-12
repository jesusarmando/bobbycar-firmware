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
}
