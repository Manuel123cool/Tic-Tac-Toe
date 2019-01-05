#include "game.h"
#include <SFML/Graphics.hpp>
#include "iostream"
#include "game_symbols.h"
#include <math.h>
Game::Game(sf::RenderWindow &window, GameGrid &gameGrid) :
    m_window(window), m_gameGrid(gameGrid)
{
    m_gameState.state = NO_STATE;
}


void Game::computerPlay()
{
    int row;
    RowStatusPlusWinRect status;

    int computerWinRec = -1;
    int playerPosWinRec = -1;
    int computerWinRow;
    for (int i{0}; i < 9; ++i)
    {
        for (int j{0}; j < 9; ++j)
        {
            if(i == j)
                continue;

            row = whichRow(i, j);
            status = checkRow(row, i, j);
            switch (status.rowStatus)
            {
                case PLAYER_WIN:
                    setGameState(PLAYER_WIN, row);
                    return;
                case POSSIBLE_COMPUTER_WIN:
                    computerWinRec = status.winRect;
                    computerWinRow = row;
                case POSSIBLE_PlAYER_WIN:
                    playerPosWinRec = status.winRect;
            };
        }
    }
    if (computerWinRec != -1)
    {
        m_gameGrid[computerWinRec].setter = GameGrid::COMPUTER;
        setGameState(COMPUTER_WIN, computerWinRow);
        return;
    }
    else if (playerPosWinRec != -1)
    {
        m_gameGrid[playerPosWinRec].setter = GameGrid::COMPUTER;
        return;
    }
    playRandom();
}

int Game::whichRow(int x, int y) const
{
    bool inRowX;
    bool inRowY;
    int whichRow;
    for (int i{0}; i < m_rows.size(); ++i)
    {
        inRowX = false;
        inRowY = false;
        for (const auto &row : m_rows[i])
        {
            if (x == row)
                inRowX = true;
            if (y == row)
                inRowY = true;
            if (inRowX && inRowY)
                whichRow = i;
        }
        if (inRowX && inRowY)
            return whichRow;
    }
    return -1;
}

Game::RowStatusPlusWinRect Game::checkRow(int row, int x, int y) const
{
    int winRect = 0;
    RowStatusPlusWinRect rowStatus;
    rowStatus.rowStatus = NO_STATE;

    if (row == -1)
    {
        return rowStatus;
    }

    for (const auto &row : m_rows[row])
            if (row != x && row != y)
                winRect = row;
    rowStatus.winRect = winRect;

    if (m_gameGrid[x].setter == m_gameGrid[y].setter)
    {
        if (m_gameGrid[x].setter == GameGrid::PLAYER)
        {
            if (m_gameGrid[winRect].setter == GameGrid::PLAYER)
                rowStatus.rowStatus = PLAYER_WIN;
            else if (m_gameGrid[winRect].setter == GameGrid::NOT_PLAYED)
                rowStatus.rowStatus = POSSIBLE_PlAYER_WIN;
        }
        else if (m_gameGrid[x].setter == GameGrid::COMPUTER)
        {
            if (m_gameGrid[winRect].setter == GameGrid::NOT_PLAYED)
                rowStatus.rowStatus = POSSIBLE_COMPUTER_WIN;
        }
    }

    return rowStatus;
}

void Game::playRandom()
{
    int random;
    int count = 0;
    do
    {
        random = getRandomNumber(0, 8);
        ++count;
        if (count > 200)
        {
            //std::cout << "Its a draw\n";
            setGameState(DROW);
            return;
        }
    } while (!(m_gameGrid[random].setter == GameGrid::NOT_PLAYED));
    m_gameGrid[random].setter = GameGrid::COMPUTER;
}

int Game::getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (RAND_MAX + 1.0);
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

void Game::winAndLoss(int row)
{
    sf::RectangleShape shape;
    int crossWidth = 10;
    float crossLineHeight = 600 - m_gameGrid.getMargin();
    float x;
    float y;
    float rotation = 0;
    if (row < 3)
    {
        y = m_gameGrid.getMargin();
        x = y + m_gameGrid.getRectSize() / 2;
        x -= crossWidth / 2;
        x += row * m_gameGrid.getRectSize() + m_gameGrid.getMargin() * row;
        shape.setPosition(sf::Vector2f(x, y));
    }
    else if (row < 6)
    {
        x = m_gameGrid.getMargin();
        y = x + m_gameGrid.getRectSize() / 2;
        y += crossWidth / 2;
        y += (row - 3)* m_gameGrid.getRectSize() + m_gameGrid.getMargin() * (row - 3);

        shape.setPosition(x, y);
        rotation = -90;
    }
    else
    {
        float cathetus = std::sin(45 * 3.1416/180) * crossWidth;
        float dioginalGabe = std::sin(45 * 3.1416/180) * cathetus;

        float dioginalLength = std::sqrt(std::pow(600 - m_gameGrid.getMargin(), 2) * 2);
        crossLineHeight = dioginalLength - dioginalGabe * 2;

        float y = m_gameGrid.getMargin();
        float x = m_gameGrid.getMargin() * 3 + m_gameGrid.getRectSize() * 3 - cathetus;
        if (row == 7)
        {
            shape.setPosition(x,y);
            rotation = 45;
        }

        x = m_gameGrid.getMargin();
        y = m_gameGrid.getMargin() + cathetus;
        if (row == 6)
        {
            shape.setPosition(x,y);
            rotation = -45;
        }
    }

    GameSymbols::setShape(shape, sf::Vector2f(crossWidth, crossLineHeight), sf::Color::Red, rotation);
    m_window.draw(shape);
}

void Game::drawState(std::string stateString, sf::Vector2f pos)
{
    sf::RectangleShape shape;
    GameSymbols::setShape(shape, sf::Vector2f(600.f, 600.f), sf::Color(166, 166, 166, 180));
    m_window.draw(shape);

    sf::Font font;
    if (!font.loadFromFile("Big Black Bear Italic.ttf"))
    {
        std::cerr << "Errow loading font\n";
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(70);
    text.setPosition(pos);
    text.setFillColor(sf::Color::White);
    text.setString(stateString);
    m_window.draw(text);

    m_gameGrid.setNotClickable(false);
    m_gameGrid.setDrawState(true);
}

void Game::renewGame()
{
    for (int i{0}; i < 9; ++i)
        m_gameGrid[i].setter = GameGrid::NOT_PLAYED;
    m_gameGrid.setNotClickable(false);
    m_gameGrid.setDrawState(false);
    m_gameState.state = NO_STATE;
    m_countFrame = 0;
}

void Game::setGameState(RowStatus gameState, int row)
{
    m_gameState.state = gameState;
    m_gameState.row = row;
}

void Game::update()
{
    if (m_gameState.state != NO_STATE)
    {
        m_gameGrid.setNotClickable(true);
        ++m_countFrame;
    }

    if(m_gameState.state == COMPUTER_WIN)
    {
        winAndLoss(m_gameState.row);
        if (m_countFrame > 60)
            drawState("Computer Won", sf::Vector2f(22, 250));
    }
    else if (m_gameState.state == PLAYER_WIN)
    {
        winAndLoss(m_gameState.row);
        if (m_countFrame > 60)
            drawState("Player Won", sf::Vector2f(70, 250));
    }
    else if (m_gameState.state == DROW)
    {
        if (m_countFrame > 60)
            drawState("Drow", sf::Vector2f(197, 250));
    }
}
