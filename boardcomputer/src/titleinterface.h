#pragma once

#include <WString.h>

namespace {
class TitleInterface {
public:
    virtual String title() const = 0;
};

template<const char *T>
class StaticTitle : public virtual TitleInterface
{
public:
    String title() const override { return T; }
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
