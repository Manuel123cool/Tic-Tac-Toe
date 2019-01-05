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
    void checkPreesed(sf::Event &event, Game &game);
    Rect& operator[] (const int index);
    float getRectSize() const;
    float getMargin() const;
    void setDrawState(bool drawState);
    void setNotClickable(bool notClickable);
};
