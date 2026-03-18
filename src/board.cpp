#include "board.h"
#include <memory>
#include <iostream>


Board::Board(int width, int height) : m_width(width), m_height(height) 
{
    // vector m_cells amb height files y cada fila un vector de width nullptrs de tipus Candy*
    m_cells.resize(height, std::vector<Candy*>(width, nullptr));
}


Board::~Board()
{
    // Con memoria estatica no hace falta implementar nada, los vectores se destruyen solos al salir de su "ambito"
}


Candy* Board::getCell(int x, int y) const
{
    // Si las coordenadas estan fuera del tablero, devolver nullptr
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
    {
        return nullptr;
    }

    // Devuelve Candy* (la dirección de memoria) de las coordenadas dadas
    return m_cells[y][x];
}


void Board::setCell(Candy* candy, int x, int y)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
    {
        return; // Si se cumple el if, se sale de la función inmediatamente
    }

    // candy ya es un puntero, ya que tenemos "Candy* candy" como parametro
    m_cells[y][x] = candy;
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
    if (m_cells[y][x] == nullptr)
    {
        return false;
    }

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
