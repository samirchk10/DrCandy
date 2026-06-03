/**
 * FITXER board.cpp
 * AUTORS Alan Tchertchessov y Samir Channagui
 * DATA 24/03/2026
 * Implementación de la clase Board
 */

#include "board.h"
#include <memory>
#include <iostream>
#include <fstream>

Board::Board(int width, int height) : m_width(width), m_height(height) 
{ 
    init(); 
}

Board::Board(const Board& b)
{
    copyFrom(b);
}

Board::~Board()
{
    clear();
}

Board& Board::operator=(const Board& b)
{
    if (this != &b)
    {
        clear();
        copyFrom(b);
    }

    return *this;
}

void Board::init()
{
    m_board = new Candy*[m_width * m_height];

    for (int i = 0; i < m_width * m_height; i++)
    {
        m_board[i] = nullptr;
    }
}

void Board::clear()
{
    for (Candy* candy : m_candyStorage)
    {
        delete candy;
    }

    m_candyStorage.clear();
    delete[] m_board;
}

void Board::copyFrom(const Board& b)
{
    m_width = b.m_width;
    m_height = b.m_height;
    init();

    for (int i = 0; i < m_width * m_height; i++)
    {
        if (b.m_board[i] != nullptr)
        {
            Candy* newCandy = new Candy(*b.m_board[i]);
            m_board[i] = newCandy;
            m_candyStorage.push_back(newCandy);
        }
    }
}

Candy* Board::getCell(int x, int y) const
{
    Candy* candy = nullptr;

    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
        candy = m_board[y * m_width + x];
    }

    return candy;
}


void Board::setCell(Candy* candy, int x, int y)
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
        m_board[y * m_width + x] = candy;
    }
}

int Board::getWidth() const
{
    return m_width;
}


int Board::getHeight() const
{
    return m_height;
}


bool Board::checkMatchDirection(int x, int y, CandyType initialType, int stepX, int stepY) const
{
    int matchCount = INITIAL_COUNT;

    for (int dir = -1; dir <= 1; dir += 2)
    {    
        bool stop = false;

        for (int i = 1; !stop; i++)
        {
            Candy* nearCandy = getCell(x + i * dir * stepX, y + i * dir * stepY);
            
            if (nearCandy != nullptr && initialType == nearCandy->getType())
            {
                matchCount++;
            }
            else
            {
                stop = true;
            }
        }
    }

    return matchCount >= SHORTEST_EXPLOSION_LINE;
}


bool Board::shouldExplode(int x, int y) const
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height || m_board[y * m_width + x] == nullptr)
    {
        return false;
    }

    Candy* initialCandy = getCell(x, y);
    CandyType initialType = initialCandy->getType();

    if (checkMatchDirection(x, y, initialType, HORIZONTAL[0], HORIZONTAL[1])) 
    {
        return true;
    }

    if (checkMatchDirection(x, y, initialType, VERTICAL[0], VERTICAL[1])) 
    {
        return true;
    }

    if (checkMatchDirection(x, y, initialType, DIAGONAL_R[0], DIAGONAL_R[1])) 
    {
        return true;
    }

    if (checkMatchDirection(x, y, initialType, DIAGONAL_L[0], DIAGONAL_L[1])) 
    {
        return true; 
    }

    return false;
}


std::vector<Candy*> Board::explodeAndDrop()
{
    std::vector<Candy*> explodedCandies;

    bool exploded = true;

    while (exploded)
    {
        exploded = false;

        std::vector<int> toExplodeX;
        std::vector<int> toExplodeY;

        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                if (m_board[y * m_width + x] != nullptr && shouldExplode(x, y))
                {
                    toExplodeX.push_back(x);
                    toExplodeY.push_back(y);
                }
            }
        }

        for (int i = 0; i < static_cast<int>(toExplodeX.size()); i++)
        {
            explodedCandies.push_back(m_board[toExplodeY[i] * m_width + toExplodeX[i]]);
            m_board[toExplodeY[i] * m_width + toExplodeX[i]] = nullptr;

            exploded = true;
        }

        if (exploded)
        {
            for (int x = 0; x < m_width; x++)
            {
                std::vector<Candy*> columnCandies;

                for (int y = m_height - 1; y >= 0; y--)
                {
                    if (m_board[y * m_width + x] != nullptr)
                    {
                        columnCandies.push_back(m_board[y * m_width + x]);
                    }
                }

                for (int y = m_height - 1; y >= 0; y--)
                {
                    int i = m_height - 1 - y; 

                    if (i < static_cast<int>(columnCandies.size()))
                    {
                        m_board[y * m_width + x] = columnCandies[i];
                    }
                    else
                    {
                        m_board[y * m_width + x] = nullptr;
                    }
                }
            }
        }
    }

    return explodedCandies;
}

char Board::typeToChar(CandyType type) const
{   
    switch (type)
    {
        case CandyType::TYPE_RED :
            return 'R';
        case CandyType::TYPE_BLUE :
            return 'B';
        case CandyType::TYPE_GREEN :
            return 'G';
        case CandyType::TYPE_YELLOW :
            return 'Y';
        case CandyType::TYPE_PURPLE :
            return 'P';
        case CandyType::TYPE_ORANGE :
            return 'O';
        default :
            return '.';
    }
}

CandyType Board::charToType(char c) const
{
    switch (c)
    {
        case 'R' :
            return CandyType::TYPE_RED;
        case 'B' : 
            return CandyType::TYPE_BLUE;
        case 'G' :
            return CandyType::TYPE_GREEN;
        case 'Y' :
            return CandyType::TYPE_YELLOW;
        case 'P' :
            return CandyType::TYPE_PURPLE;
        case 'O' :
            return CandyType::TYPE_ORANGE;
        default :
            return CandyType::COUNT;
    }
}

bool Board::dump(const std::string& output_path) const
{
    std::ofstream file;
    file.open(output_path);

    if (!file.is_open())
    {
        return false;
    }

    file << m_width << " " << m_height << "\n";

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            if (m_board[y * m_width + x] == nullptr)
            {
                file << ". ";
            }
            else
            {
                file << typeToChar(m_board[y * m_width + x]->getType()) << " ";
            }
        }
        file << "\n";
    }
    file.close();

    return true;
}

bool Board::load(const std::string& input_path)
{
    std::ifstream file;
    file.open(input_path);

    if (!file.is_open())
    {
        return false;
    }
    
    clear();

    file >> m_width >> m_height;
    init();

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            char c;
            file >> c;

            if (c != '.')
            {
                Candy* newCandy = new Candy(charToType(c));
                m_board[y * m_width + x] = newCandy;
                m_candyStorage.push_back(newCandy);
            }
        }
    }

    file.close();

    return true;
}
