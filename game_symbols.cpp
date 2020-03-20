/*  Tic-Tac-Toe: a simple Tic-Tac-Toe game
    Copyright (C) 2020  Manuel Maria Kümpel

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "game_symbols.h"
#include <math.h>
#include "iostream"

GameSymbols::GameSymbols(sf::RenderWindow &window, GameGrid &gameGrid) :
    m_window(window), m_gameGrid(gameGrid)
{
    setBaseCrossLinesPos();
}

void GameSymbols::setBaseCrossLinesPos()
{
    float cathetus = std::sin(45 * 3.1416/180) * m_crossLineWidth;
    float dioginalGabe = std::sin(45 * 3.1416/180) * cathetus;

    float dioginalLength = std::sqrt(std::pow(m_gameGrid.getRectSize(), 2.f) * 2);
    m_crossLineHeight = dioginalLength - dioginalGabe * 2 - m_spaceToCorner * 2;

    float y = cathetus + m_gameGrid.getMargin();
    float x = m_gameGrid.getMargin() + m_gameGrid.getRectSize() - cathetus * 2;
    m_baseCrossLineRight = sf::Vector2f(x, y);

    x = cathetus + m_gameGrid.getMargin();
    y = m_gameGrid.getMargin() + cathetus * 2;
    m_baseCrossLineLeft = sf::Vector2f(x, y);
}

void GameSymbols::update()
{
    for (int i{0}; i < 9; ++i)
    {
        if(m_gameGrid[i].setter == GameGrid::PLAYER)
        {
            sf::RectangleShape rectShapeRight;
            setShape(rectShapeRight, sf::Vector2f(m_crossLineWidth, m_crossLineHeight), sf::Color::Green, 45.f);
            setPosUponIndex(i, rectShapeRight, m_baseCrossLineRight.x, m_baseCrossLineRight.y, m_gameGrid);

            sf::RectangleShape rectShapeLeft;
            setShape(rectShapeLeft, sf::Vector2f(m_crossLineWidth, m_crossLineHeight), sf::Color::Green, -45.f);
            setPosUponIndex(i, rectShapeLeft, m_baseCrossLineLeft.x, m_baseCrossLineLeft.y, m_gameGrid);

            m_window.draw(rectShapeLeft);
            m_window.draw(rectShapeRight);
        }

        if(m_gameGrid[i].setter == GameGrid::COMPUTER)
        {
            sf::CircleShape shape(65.f);
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineThickness(m_crossLineWidth);
            shape.setOutlineColor(sf::Color(255, 128, 0));

            setPosUponIndex(i, shape, m_crossLineWidth * 2, m_crossLineWidth * 2, m_gameGrid);
            m_window.draw(shape);
        }
    }
}

void GameSymbols::setPosUponIndex(int i ,sf::Shape &shape, float baseX, float baseY, GameGrid &gameGrid)
{
    if (i < 3)
    {
        shape.setPosition(baseX + i * (gameGrid.getMargin() + gameGrid.getRectSize()), baseY);
    }
    else if (i < 6)
    {
        shape.setPosition(
            baseX + (i - 3) * (gameGrid.getMargin() + gameGrid.getRectSize()),
                (baseY + gameGrid.getMargin() + gameGrid.getRectSize()));

    }
    else
    {
        float rightX = baseX + (i - 6) * (gameGrid.getMargin() + gameGrid.getRectSize());
        float rightY = baseY + 2 * (gameGrid.getMargin() + gameGrid.getRectSize());
        shape.setPosition( rightX, rightY);
    }
}

void GameSymbols::setShape(sf::RectangleShape &shape, sf::Vector2f size, sf::Color color, float rotation)
{
    shape.setSize(sf::Vector2f(size));
    shape.setFillColor(color);
    shape.setRotation(rotation);
}
