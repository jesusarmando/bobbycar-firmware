#pragma once

#include <bitset>
#include <memory>

#include <Arduino.h>
#include <HardwareSerial.h>

#include "demodisplay.h"
#include "actions/switchscreenaction.h"

namespace {
class DemosMenu;
}

namespace {
class GameOfLifeDisplay : public DemoDisplay, public SwitchScreenAction<DemosMenu>
{
    using Base = DemoDisplay;

public:
    void start() override;
    void initScreen() override;
    void redraw() override;
    void stop() override;

private:

    //Draws the grid on the display
    void drawGrid();

    //Initialise Grid
    void initGrid();

    // Check the Moore neighborhood
    int getNumberOfNeighbors(int x, int y);

    //Compute the CA. Basically everything related to CA starts here
    void computeCA();

    //static const constexpr auto GRIDX = 80;
    //static const constexpr auto GRIDY = 60;
    //static const constexpr auto CELLXY = 4;

    static const constexpr auto GRIDX = 160;
    static const constexpr auto GRIDY = 120;
    static const constexpr auto CELLXY = 2;

    static const constexpr auto GEN_DELAY = 0;

    template<typename T> auto index(T x, T y)
    {
        if (x >= GRIDX)
        {
            Serial.printf("x: %i", x);
            return 0;
        }
        if (y >= GRIDY)
        {
            Serial.printf("y: %i", x);
            return 0;
        }
        return (x * GRIDX) + y;
    }

    struct Data
    {
        std::bitset<GRIDX*GRIDY> grid, newgrid;
    };

    std::unique_ptr<Data> m_data;

    int gen = 0;
};

void GameOfLifeDisplay::start()
{
    m_data = std::make_unique<Data>();
}

void GameOfLifeDisplay::initScreen()
{
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
}

void GameOfLifeDisplay::redraw()
{
    if (gen == 0)
    {
        tft.fillScreen(TFT_BLACK);
        initGrid();
    }

    computeCA();
    drawGrid();

    m_data->grid = m_data->newgrid;
//    for (int16_t x = 1; x < GRIDX-1; x++) {
//        for (int16_t y = 1; y < GRIDY-1; y++) {
//            grid[index(x,y)] = m_data->newgrid[index(x,y)];
//        }
//    }

    if (++gen == 200)
        gen = 0;
}

void GameOfLifeDisplay::stop()
{
    Base::stop();
    tft.setRotation(0);
    m_data = nullptr;
}

void GameOfLifeDisplay::drawGrid()
{
    uint16_t color = TFT_WHITE;
    for (int16_t x = 1; x < GRIDX - 1; x++) {
        for (int16_t y = 1; y < GRIDY - 1; y++) {
            if ((m_data->grid[index(x,y)]) != (m_data->newgrid[index(x,y)])) {
                if (m_data->newgrid[index(x,y)] == 1)
                    color = 0xFFFF; //random(0xFFFF);
                else
                    color = 0;
                tft.fillRect(CELLXY * x, CELLXY * y, CELLXY, CELLXY, color);
            }
        }
    }
}

void GameOfLifeDisplay::initGrid()
{
    for (int16_t x = 0; x < GRIDX; x++) {
        for (int16_t y = 0; y < GRIDY; y++) {
            m_data->newgrid[index(x,y)] = 0;

            if (x == 0 || x == GRIDX - 1 || y == 0 || y == GRIDY - 1)
                m_data->grid[index(x,y)] = 0;
            else
            {
                if (random(3) == 1)
                    m_data->grid[index(x,y)] = 1;
                else
                    m_data->grid[index(x,y)] = 0;
            }

        }
    }
}

int GameOfLifeDisplay::getNumberOfNeighbors(int x, int y)
{
    int n{};
    for (auto xOffset : {-1,0,1})
        for (auto yOffset : {-1,0,1})
        {
            if (xOffset == 0 && yOffset == 0)
                continue;

            const auto new_x = x+xOffset;
            const auto new_y = y+yOffset;

            if (new_x >= 0 && new_y >= 0 &&
                new_x < GRIDX && new_y < GRIDY)
                n += m_data->grid[index(new_x, new_y)];
        }

    return n;
}

void GameOfLifeDisplay::computeCA()
{
    for (int16_t x = 1; x < GRIDX; x++) {
        for (int16_t y = 1; y < GRIDY; y++) {
            int neighbors = getNumberOfNeighbors(x, y);
            if (m_data->grid[index(x,y)] == true && (neighbors == 2 || neighbors == 3 ))
                m_data->newgrid[index(x,y)] = true;
            else if (m_data->grid[index(x,y)] == 1)
                m_data->newgrid[index(x,y)] = false;
            if (m_data->grid[index(x,y)] == false && (neighbors == 3))
                m_data->newgrid[index(x,y)] = true;
            else if (m_data->grid[index(x,y)] == 0)
                m_data->newgrid[index(x,y)] = false;
        }
    }
}

}
