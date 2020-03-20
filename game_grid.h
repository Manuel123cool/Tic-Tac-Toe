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
#include <array>
class Game;

class GameGrid
{
public:
    enum Setter {PLAYER, COMPUTER, NOT_PLAYED};
    struct Rect
    {
        Setter setter;
        sf::RectangleShape shape;
    };
private:
    std::array<Rect, 9> m_recGrid;
    sf::RenderWindow &m_window;
    const float m_margin = 10.f;
    const float m_rectSize = 190.f;
    bool m_drowStateOn = false;
    bool m_notClickable = false;
public:
    GameGrid(sf::RenderWindow &window);
    void draw() const;
    void checkPressed(sf::Event &event, Game &game);
    Rect& operator[] (const int index);
    float getRectSize() const;
    float getMargin() const;
    void setDrawState(bool drawState);
    void setNotClickable(bool notClickable);
};
