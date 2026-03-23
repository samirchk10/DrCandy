/**
 * FITXER board.h
 * AUTORS Alan Tchertchessov i Samir Channagui
 * DATA 24/03/2026
 * VERSIO 1.0
 * Declaración de la clase Board. Define la estructura del tablero de
 * punteros Candy, las constantes (dimensiones, direcciones,
 * minimo de explosion) y la interfaz publica para acceder, modificar,
 * detectar explosiones y guardar/cargar el estado del tablero
 */

#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <unordered_map>
#include <vector>

#include "candy.h"

/// Dimensiones por defecto de Board
const int DEFAULT_BOARD_WIDTH = 10;
const int DEFAULT_BOARD_HEIGHT = 10;

/// Numero de candies del mismot ipo que se necesitan para explotar en horizontal, vertical o diagonal
const int SHORTEST_EXPLOSION_LINE = 3;

/// Estado inicial del contador de tipos de Candy correspondientes
const int INITIAL_COUNT = 1;

// Dirreciones en las que realizar la busqueda de Candys de mismo tipo: stepX, stepY
const int HORIZONTAL[2] = {1, 0};
const int VERTICAL[2] = {0, 1};
const int DIAGONAL_L[2] = {1, -1};
const int DIAGONAL_R[2] = {1, 1};

/**
 * CLASS Board
 * Clase que representa el tablero del juego. Gestiona un tablero 2D de punteros Candy.
 * Contiene metodos para acceder y modificar celdas, detectar y explotar lineas de 3 o
 * mas candies del mismo tipo, hacer caer los candies restantes tras cada explosion y
 * guardar/cargar el estado del tablero
 */
class Board
{
public:
    /// Inicializa un tablero con las dimensiones dadas
    Board(int width = DEFAULT_BOARD_WIDTH, int height = DEFAULT_BOARD_HEIGHT);

    /// Libera todos los recursos manejados por Board
    ~Board();

    /**
    * Determina si el candy en las coordenadas dadas debe explotar
    * dado el estado actual del tablero, es decir, forma parte de una línea
    * (horizontal/vertical/diagonal) de SHORTEST_EXPLOSION_LINE o más candies
    * del mismo tipo.
    * @param x coordenada x de la celda, indice 0, de izquierda a derecha
    * @param y coordenada y de la celda, indice 0, de arriba a abajo
    * @return true si el candy debe explotar, false en caso contrario
    */
    bool shouldExplode(int x, int y) const;

    /**
    * Explota todos los candies que deben explotar (líneas de candies)
    * y despues hace caer los candies de arriba para llenar los huecos.
    * Despues de la caída, repite el proceso hasta que no haya más candies que explotar.
    * @return vector (potencialmente vacio) con todos los candies explotados
    */
    std::vector<Candy*> explodeAndDrop();

    /**
    * Guarda una representacion serializada del tablero en un fichero,
    * que puede ser cargada posteriormente con Board::load.
    * @param output_path ruta del fichero de salida donde se guardará la representación
    * @return true si se ha guardado, false en caso contrario
    */
    bool dump(const std::string& output_path) const;

    /**
    * Carga una representacion serializada del tablero desde un fichero guardado previamente.
    * Cualquier estado existente del tablero es descartado.
    * @param input_path ruta del fichero de entrada desde el que se cargará la representacion
    * @return true si se ha cargado, false en caso contrario
    */
    bool load(const std::string& input_path);

    /**
     * Obtiene una referencia al candy en las coordenadas dadas, si existe.
     * 
     * @param x indice 0, de izquierda a derecha, coordenada x de la celda
     * @param y indice 0, de arriba a abajo, coordenada y de la celda
     * @return puntero al candy en las coordenadas dadas si las coordenadas
     * son validas y la celda no está vacia, nullptr si no es así
     */
    Candy* getCell(int x, int y) const;

    /**
     * Establece la celda en las coordenadas dadas con el candy dado.
     * @param candy puntero al candy a colocar en la celda
     * @param x indice 0, de izquierda a derecha, coordenada x de la celda
     * @param y indice 0, de arriba a abajo, coordenada y de la celda
     */
    void setCell(Candy* candy, int x, int y);

    /**
     * Convierte un CandyType a un caracter
     * @param type: tipo de candy
     * @return caracter correspondiente al tipo
     */
    char typeToChar(CandyType type) const;

    /**
     * Convierte un caracter a un CandyType
     * @param c: caracter a convertir
     * @return CandyType correspondiente al caracter
     */
    CandyType charToType(char c) const;

    /// Obtener el ancho del tablero
    int getWidth() const;

    /// Obtener la altura del tablero
    int getHeight() const;

    /**
     * Comprueba si hay bastantes correspondencias en una direccion para explotar
     * @param x: coordenada x del candy inicial
     * @param y: coordenada y del candy inicial
     * @param initialType: tipo de candy inicial
     * @param stepX: paso en x de la dirección
     * @param stepY: paso en y de la dirección
     @return true si hay 3 o mas coincidencias, falso si no es así
    
     */
    bool checkMatchDirection(int x, int y, CandyType typeInicial, int stepX, int stepY) const;


private:
    /// Guarda el ancho del tablero
    int m_width;
    /// Guarda la altura del tablero
    int m_height;
    
    // Vector 2D de punteros de Candy
    std::vector<std::vector<Candy*>> m_cells;

    // Vector para almacenar candies
    std::vector<Candy> m_candyStorage;
};

#endif
