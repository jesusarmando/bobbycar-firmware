#pragma once

#include "demodisplay.h"
#include "actions/switchscreenaction.h"
#include "textinterface.h"
#include "widgets/label.h"
#include "widgets/graph.h"
#include "globals.h"
#include "statistics.h"

namespace {
class GraphsMenu;
}

namespace {
class GraphDisplay : public DemoDisplay, public SwitchScreenAction<GraphsMenu>, public virtual TextInterface, public virtual StatisticsInterface
{
    using Base = DemoDisplay;

public:
    void initScreen() override;
    void redraw() override;

private:
    static constexpr int screenHeight = 320, topMargin = 40, bottomMargin = 10, labelOffset = -5;
    static constexpr int graphHeight = screenHeight-topMargin-bottomMargin;

    Label m_titleLabel{5, 5}; // 230, 25

    Graph m_graph{0, 40, 270};
};

void GraphDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);

    m_titleLabel.start();
    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    m_graph.start({getBuffer()});
}

void GraphDisplay::redraw()
{
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    m_titleLabel.redraw(text());

    m_graph.redraw({getBuffer()});
}
}
