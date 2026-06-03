#include "game.h"
#include <random>
#include "graphics.h"
#include "candy.h"
#include <fstream>

Game::Game() : m_frameCounter(0), m_score(0), m_gameOver(false)
{
    for (int i = 0; i < 3; i++)
    {
        m_fallingBlock[i] = nullptr;
    }

    spawnBlock();
}

Game::~Game()
{
    for (Candy* candy : m_candies)
    {
        delete candy;
    }
}

void Game::spawnBlock()
{
    // Donde inicia el bloque 
    m_blockX = 5;
    m_blockY = -1;

    // Creamos 3 candies aleatorios y registramos en m_candies que esos candies han estado creados por Game
    for (int i = 0; i < 3; i++)
    {
        m_fallingBlock[i] = new Candy(static_cast<CandyType>(rand() % 6));
        m_candies.push_back(m_fallingBlock[i]);
    }


    // Si la celda por donde entra el bloque (columan 5 fila 0) esta ocupada, es gameover, el bloque no puede bajar.
    if (m_board.getCell(m_blockX, 0) != nullptr)
    {
        m_gameOver = true;
    }
}

bool Game::canFall() const
{
    bool canMove = true;
    int nextY = m_blockY + 1;

    if (nextY >= m_board.getHeight())
    {
        canMove = false;
    }
    else if (nextY >= 0 && m_board.getCell(m_blockX, nextY) != nullptr)
    {
        canMove = false;
    }

    return canMove;
}

void Game::landBlock()
{
    for (int i = 0; i < 3; i++)
    {
        int candyY = m_blockY - i;

        if (candyY >= 0)
        {
            m_board.setCell(m_fallingBlock[i], m_blockX, candyY);
        }
    }

    std::vector<Candy*> exploded = m_board.explodeAndDrop();
    m_score += static_cast<int>(exploded.size());

    spawnBlock();
}

bool Game::canMoveTo(int newX) const
{
    bool canMove = true;

    if (newX < 0 || newX >= m_board.getWidth())
    {
        canMove = false;
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            int candyY = m_blockY - i;

            if (candyY >= 0 && m_board.getCell(newX, candyY) != nullptr)
            {
                canMove = false;
            }
        }
    }

    return canMove;
}

void Game::rotateBlock()
{
    Candy* first = m_fallingBlock[0];
    m_fallingBlock[0] = m_fallingBlock[1];
    m_fallingBlock[1] = m_fallingBlock[2];
    m_fallingBlock[2] = first;
}

void Game::update(const Controller& controller)
{
    if (!m_gameOver)
    {
        if (controller.isLeftPressed() && canMoveTo(m_blockX - 1))
        {
            m_blockX--;
        }
        if (controller.isRightPressed() && canMoveTo(m_blockX + 1))
        {
            m_blockX++;
        }
        if (controller.isDownPressed() && canFall())
        {
            m_blockY++;
        }
        if (controller.isKey1Pressed())
        {
            rotateBlock();
        }

        if (m_frameCounter % 60 == 0)
        {
            if (canFall())
            {
                m_blockY++;
            }
            else
            {
                landBlock();
            }
        }

        m_frameCounter++;
    }
}

void Game::render(GraphicManager& graphics)
{
    const int board_padding = 3;
    graphics.drawRectangle(
        CANDY_IMAGE_WIDTH * board_padding, CANDY_IMAGE_HEIGHT * board_padding,
        CANDY_IMAGE_WIDTH * m_board.getWidth(),
        CANDY_IMAGE_HEIGHT * m_board.getHeight(),
        5, 150, 150, 150);

    for (int y = 0; y < m_board.getHeight(); y++)
    {
        for (int x = 0; x < m_board.getWidth(); x++)
        {
            Candy* candy = m_board.getCell(x, y);

            if (candy != nullptr)
            {
                graphics.drawImage(candy->getResourceName(),
                    CANDY_IMAGE_WIDTH * (board_padding + x),
                    CANDY_IMAGE_HEIGHT * (board_padding + y));
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        int candyY = m_blockY - i;

        if (candyY >= 0)
        {
            graphics.drawImage(m_fallingBlock[i]->getResourceName(),
                CANDY_IMAGE_WIDTH * (board_padding + m_blockX),
                CANDY_IMAGE_HEIGHT * (board_padding + candyY));
        }
    }

    // Title [draw images]
    graphics.drawImage("img/logo_small.png", 10, 10);
    // Score and footer [draw text]
    graphics.drawText("Movement: [Up] [Down] [Left] [Right]  --  "
                      "Buttons: [Q] [W] [E]  --  Exit [ESC]",
                      25, 700, 20, 100, 100, 100);
    graphics.drawText("Score: " + std::to_string(m_score), 450, 10, 70, 125, 200, 125);
}

void Game::run()
{
    const int screen_width = 750;
    const int screen_height = 750;
    const int bg_red = 255;
    const int bg_green = 255;
    const int bg_blue = 255;
    runGraphicGame(*this, screen_width, screen_height, bg_red, bg_green, bg_blue);
}

bool Game::dump(const std::string& output_path) const
{
    if (!m_board.dump(output_path)) 
    {
        return false;
    }
    std::ofstream file(output_path);
    if (!file.is_open()) 
    {
        return false;
    }
    file << m_score << " " << m_frameCounter << " " << m_gameOver << "\n";
    file << m_blockX << " " << m_blockY << "\n";
    for (int i = 0; i < 3; i++) 
    {
        if (m_fallingBlock[i] == nullptr) 
        {
            file << ". ";
        }
        else 
        {
            file << m_board.typeToChar(m_fallingBlock[i]->getType()) << " ";
        }
    }
    file << "\n";
    file.close();
    return true;
}

bool Game::load(const std::string& input_path)
{
    if (!m_board.load(input_path)) 
    {
        return false;
    }
    std::ifstream file(input_path);
    if (!file.is_open()) 
    {
        return false;
    }
    int width, height;
    file >> m_score >> m_frameCounter >> m_gameOver;
    file >> m_blockX >> m_blockY;
    for (int i = 0; i < 3; i++) 
    {
        if (m_fallingBlock[i] != nullptr) 
        {
            delete m_fallingBlock[i];
            m_fallingBlock[i] = nullptr;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        char c;
        file >> c;
        if (c == '.') 
        {
            m_fallingBlock[i] = nullptr;
        }
        else 
        {
            m_fallingBlock[i] = new Candy(m_board.charToType(c));
        }
    }
    file.close();
    return true;
}

bool Game::operator==(const Game& other) const
{
    bool equal = ( m_frameCounter == other.m_frameCounter &&
                m_score == other.m_score && m_gameOver == other.m_gameOver);

    for (int x = 0; x < m_board.getWidth() && equal; x++)
    {
        for (int y = 0; y < m_board.getHeight() && equal; y++) 
        {
            Candy* a = m_board.getCell(x, y);
            Candy* b = other.m_board.getCell(x, y);

            bool same = (a == nullptr && b== nullptr) || (a != nullptr && b != nullptr && 
                        a->getType() == b->getType());
            
            if (!same)
            {
                equal = false;
            }
        }
    }

    return equal;
}