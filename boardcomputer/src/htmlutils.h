#pragma once

#include "htmltag.h"

namespace {
void breakLine(AsyncResponseStream &stream)
{
    stream.print("<br/>");
}

void label(AsyncResponseStream &stream, const char *name, const char *text)
{
    HtmlTag label(stream, "label", String(" for=\"") + name + "\"");
    stream.print(text);
}

template<typename T>
void numberInput(AsyncResponseStream &stream, T value, const char *id, const char *name, const char *text)
{
    label(stream, id, text);

    breakLine(stream);

    stream.print("<input type=\"number\" id=\"");
    stream.print(id);
    stream.print("\" name=\"");
    stream.print(name);
    stream.print("\" value=\"");
    stream.print(value);
    stream.print("\" required />");
}

template<typename T>
void numberInput(AsyncResponseStream &stream, T value, const char *name, const char *text)
{
    numberInput(stream, value, name, name, text);
}

void submitButton(AsyncResponseStream &stream)
{
    HtmlTag button(stream, "button", " type=\"submit\"");
    stream.print("Submit");
}

void checkboxInput(AsyncResponseStream &stream, bool value, const char *id, const char *name, const char *text)
{
    label(stream, id, text);

    breakLine(stream);

    stream.print("<input type=\"checkbox\" id=\"");
    stream.print(id);
    stream.print("\" name=\"");
    stream.print(name);
    stream.print("\" value=\"on\"");
    if (value)
        stream.print(" checked");
    stream.print(" />");
}

void checkboxInput(AsyncResponseStream &stream, bool value, const char *name, const char *text)
{
    checkboxInput(stream, value, name, name, text);
}

void selectOption(AsyncResponseStream &stream, const char *value, const char *text, bool selected)
{
    String str{" value=\""};
    str += value;
    str += "\"";

    if (selected)
        str += " selected";

    HtmlTag option(stream, "option", str);
    stream.print(text);
}
}
