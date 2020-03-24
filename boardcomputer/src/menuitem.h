#pragma once

namespace {
class MenuItem {
public:
    MenuItem(const char *text) : m_text{text} {}

    virtual void triggered() const = 0;

    const char *text() const { return m_text; }

private:
    const char * const m_text;
};
}
