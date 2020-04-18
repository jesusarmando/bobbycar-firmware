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
class DualGraphDisplay : public DemoDisplay, public SwitchScreenAction<GraphsMenu>
{
    using Base = DemoDisplay;

public:
    void initScreen() override;
    void redraw() override;

private:
    Label m_titleLabel{5, 5}; // 230, 25

    Graph m_graph0{0, 40, 133};
    Graph m_graph1{0, 179, 133};
};

void DualGraphDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);

    m_titleLabel.start();
    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    m_graph0.start({statistics::gas});
    m_graph1.start({statistics::brems});
}

void DualGraphDisplay::redraw()
{
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    m_titleLabel.redraw("Gas/Brems dual");

    m_graph0.redraw({statistics::gas});
    m_graph1.redraw({statistics::brems});
}
}
