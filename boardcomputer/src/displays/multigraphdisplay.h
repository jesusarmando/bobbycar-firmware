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
class MultiGraphDisplay : public DemoDisplay, public SwitchScreenAction<GraphsMenu>
{
    using Base = DemoDisplay;

public:
    void initScreen() override;
    void redraw() override;

private:
    static constexpr int screenHeight = 320, topMargin = 40, bottomMargin = 10, labelOffset = -5;
    static constexpr int graphHeight = screenHeight-topMargin-bottomMargin;

    Label m_titleLabel{5, 5}; // 230, 25

    GraphBase<200, 2> m_graph{0, 40, 270};
};

void MultiGraphDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);

    m_titleLabel.start();
    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    m_graph.start({statistics::gas, statistics::brems});
}

void MultiGraphDisplay::redraw()
{
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    m_titleLabel.redraw("Gas/Brems multi");

    m_graph.redraw({statistics::gas, statistics::brems});
}
}
