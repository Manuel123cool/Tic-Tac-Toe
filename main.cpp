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

#include <SFML/Graphics.hpp>
#include <iostream>
#include "game_symbols.h"
#include "game.h"
#include "game_grid.h"

int main()
{
    int windowWidth = 600;
    int windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
        "Tic-Tac-Toe", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    GameGrid gameGrid(window);
    GameSymbols gameSymbols(window, gameGrid);
    Game game(window, gameGrid);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
               if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            gameGrid.checkPressed(event, game);
        }
        window.clear(sf::Color(207, 207, 207));
        gameGrid.draw();
        gameSymbols.update();
        game.update();
        window.display();
    }
    return 0;
}

