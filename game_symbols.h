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
