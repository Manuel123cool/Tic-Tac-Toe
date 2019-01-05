#pragma once
#include <SFML/Graphics.hpp>
#include "game_grid.h"
#include <array>
#include <string>

class Game
{
public:
    enum RowStatus {POSSIBLE_PlAYER_WIN, POSSIBLE_COMPUTER_WIN, PLAYER_WIN, COMPUTER_WIN, DROW, IN_GAME, NO_STATE};
private:
    struct RowStatusPlusWinRect
    {
        RowStatus rowStatus;
        int winRect;
    };
    struct GameState
    {
        RowStatus state;
        int row;
    };
    sf::RenderWindow &m_window;
    GameGrid &m_gameGrid;
    int whichRow(int x, int y) const;
    RowStatusPlusWinRect checkRow(int row, int x, int y) const;
    void playRandom();
    int getRandomNumber(int min, int max);
    void winAndLoss(int row);
    void drawState(std::string stateString, sf::Vector2f pos);
    GameState m_gameState;
    int m_countFrame = 0;
public:
    Game(sf::RenderWindow &window, GameGrid &gamegrid);
    void computerPlay();
    void update();
    void renewGame();
    void setGameState(RowStatus gameState, int row = 0);
private:
    const std::array<std::array<int, 3>, 8> m_rows =
    {{
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,1,2},
        {3,4,5},
        {6,7,8},
        {0,4,8},
        {2,4,6}
    }};
};
