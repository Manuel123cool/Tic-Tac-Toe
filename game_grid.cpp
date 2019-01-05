#include "game_grid.h"
#include "game_symbols.h"
#include "game.h"
#include <iostream>
GameGrid::GameGrid(sf::RenderWindow &window) : m_window(window)
{
    for (float i{0.f}; i < m_recGrid.size(); ++i)
    {
        GameSymbols::setPosUponIndex(i, m_recGrid[i].shape, m_margin, m_margin, *this);
        GameSymbols::setShape(m_recGrid[i].shape, sf::Vector2f(m_rectSize, m_rectSize), sf::Color(255, 255, 255));

        for (auto &rect : m_recGrid)
            rect.setter = NOT_PLAYED;
    }
}

void GameGrid::checkPreesed(sf::Event &event, Game &game)
{
    if (event.type == sf::Event::MouseButtonPressed && !m_notClickable)
    {
        if (m_drowStateOn)
        {
            game.renewGame();
            return;
        }
        for (int i{0}; i < m_recGrid.size(); ++i)
        {
            if(m_recGrid[i].setter != NOT_PLAYED)
                continue;
            if (m_recGrid[i].shape.getGlobalBounds().
                contains(event.mouseButton.x, event.mouseButton.y))
            {
                m_recGrid[i].setter = PLAYER;
                game.computerPlay();
            }
        }
    }
}

void GameGrid::draw() const
{
    for (const auto &rect : m_recGrid)
        m_window.draw(rect.shape);
}

GameGrid::Rect& GameGrid::operator[] (const int index)
{
    return m_recGrid.at(index);
}

float GameGrid::getRectSize() const
{
    return m_rectSize;
}

float GameGrid::getMargin() const
{
    return m_margin;
}

void GameGrid::setDrawState(bool drawState)
{
    m_drowStateOn = drawState;
}

void GameGrid::setNotClickable(bool notClickable)
{
    m_notClickable = notClickable;
}

