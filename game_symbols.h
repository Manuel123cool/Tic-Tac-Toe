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

#pragma once
#include <SFML/Graphics.hpp>
#include "game_grid.h"

class GameSymbols
{
private:
    sf::RenderWindow &m_window;
    GameGrid &m_gameGrid;

    float m_crossLineHeight;
    const float m_crossLineWidth = 20;
    const float m_spaceToCorner = 20;

    sf::Vector2f m_baseCrossLineRight;
    sf::Vector2f m_baseCrossLineLeft;

    void setBaseCrossLinesPos();
public:
    GameSymbols(sf::RenderWindow &window, GameGrid &gameGrid);
    static void setPosUponIndex(int i ,sf::Shape &shape, float baseX, float baseY, GameGrid &gameGrid);
    static void setShape(sf::RectangleShape &shape, sf::Vector2f size, sf::Color color, float rotation = 0.f);
    void update();
};
