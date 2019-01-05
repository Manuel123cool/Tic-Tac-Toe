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
            gameGrid.checkPreesed(event, game);
        }
        window.clear(sf::Color(207, 207, 207));
        gameGrid.draw();
        gameSymbols.update();
        game.update();
        window.display();
    }
    return 0;
}

