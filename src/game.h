/**
 * FICHERO game.h
 * AUTORES Alan Tchertchessov, Samir Channagui
 * FECHA 24/03/2026
 * Declaracion de la clase Game: logica y renderizado del juego
 */

#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "graphics.h"
#include "controller.h"

const int BLOCK_SIZE = 3;
const int NUM_CANDY_TYPES = 6;
const int FRAMES_PER_DROP = 60;
const int INITIAL_BLOCK_X = 5;
const int INITIAL_BLOCK_Y = -1;

/**
 * Main game class: keep track of the game state it. 
 * When run_graphic_game() is called, the game loop will call
 * update() and render() every frame, in that order.
 */
class Game
{
    public:
        /// Constructor por defecto: inicializa el estado y crea el primer bloque
        Game();

        /// Destructor: libera todos los candies creados por Game
        ~Game();

        /// Run the game loop
        void run();

        /**
        * Update the game state. Called every frame when run().
        * This part is not expected to do any rendering.
        * 
        * @param controller the Controller to use for input handling.
        */
        void update(const Controller& controller);

        /**
        * Draw the next frame. Called once per frame, after update().
        * 
        * @param graphics the GraphicManager to use for rendering.
        */
        void render(GraphicManager& graphics);

        /**
        * Serialize and write the current game state (board and falling block) to a file.
        * @param output_path path where to save the game state.
        * @return true if the dump was successful, false otherwise.
        */
        bool dump(const std::string& output_path) const;

        /**
        * Load a serialized game state (board and falling block) from a file created with dump().
        * @param input_path path from which to load the game state.
        * @return true if the load was successful, false otherwise.
        */
        bool load(const std::string& input_path);

        /// @return true if this game is equal to the other game (same board state and falling block)
        bool operator==(const Game& other) const;

    private:
        Board m_board;
        int m_frameCounter;
        int m_score;
        bool m_gameOver;

        Candy* m_fallingBlock[BLOCK_SIZE];
        int m_blockX;
        int m_blockY;

        std::vector<Candy*> m_candies;

        /// Crea un nuevo bloque de candies aleatorios en la posicion inicial
        void spawnBlock();

        /// @return true si el bloque puede bajar una posicion mas
        bool canFall() const;

        /// Aterriza el bloque en el tablero, explota lineas y crea uno nuevo
        void landBlock();

        /// @param newX columna destino. @return true si el bloque cabe ahi
        bool canMoveTo(int newX) const;

        /// Rota el orden de los candies del bloque
        void rotateBlock();

};
#endif
