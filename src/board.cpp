#include "board.h"
#include <memory>
#include <iostream>

/**
 * Constructor de la classe Board
 * Asigna a m_width i m_height el width i height que es reben. 
 * Crea una matriu amb height files i width columnes, on cada cel·la s'inicialitza amb nullptr (buit)
 * @param width Nombre de columnes del tauler
 * @param height Nombre de files del tauler
 */
Board::Board(int width, int height) 
    : m_width(width), 
      m_height(height),
      m_cells(height, std::vector<Candy*>(width, nullptr)) 
{}


Board::~Board()
{
    // Implement your code here
}


Candy* Board::getCell(int x, int y) const
{
    // Implement your code here
    return nullptr;
}

void Board::setCell(Candy* candy, int x, int y)
{
    // Implement your code here
}


int Board::getWidth() const
{
    return m_width;
}


int Board::getHeight() const
{
    return m_height;
}

bool Board::shouldExplode(int x, int y) const
{
    // Implement your code here
    return false;
}

std::vector<Candy*> Board::explodeAndDrop()
{
    // Implement your code here
    return {};
}

bool Board::dump(const std::string& output_path) const
{
    // Implement your code here
    return false;
}

bool Board::load(const std::string& input_path)
{
    // Implement your code here
    return false;
}
