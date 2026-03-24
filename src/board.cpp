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

// Inicializa el tablero con las dimensiones dadas, y a su vez inicializa un vector 2D con height filas y width columnas, rellenado con nullptrs
Board::Board(int width, int height) : m_width(width), m_height(height) , m_cells(height, std::vector<Candy*>(width, nullptr)) {}

// Esto no hace falta implementarlo aun
Board::~Board()
{
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
        return; // Si se cumple el if, se sale de la función
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


bool Board::checkMatchDirection(int x, int y, CandyType initialType, int stepX, int stepY) const
{
    // Contador para los candies que coinciden uno tras otro
    int matchCount = INITIAL_COUNT;

    // En la primera iteracion verificará correspondencias en un sentido, en la segunda, en el sentido contrario
    for (int dir = -1; dir <= 1; dir += 2)
    {    
        bool stop = false;

        // Empieza en i = 1 para empezar un paso adelante del candy principal
        for (int i = 1; !stop; i++)
        {
            // Candy de al lado en la dirección dada a 'i' pasos de distancia
            Candy* nearCandy = getCell(x + i * dir * stepX, y + i * dir * stepY);
            
            if (nearCandy != nullptr && initialType == nearCandy->getType()) // la "->" es lo mismo que hacer (*nearCandy).getType()
            {
                matchCount++;
            }
            else
            {
                stop = true;
            }
        }
    }

    // Devuelve true en caso de que el matchCount sea igual o mayor a 3
    return matchCount >= SHORTEST_EXPLOSION_LINE;
}


bool Board::shouldExplode(int x, int y) const
{
    // Devolver false si las coordenadas dadas son negativas, estan fuera del tablero o son las de una celda vacia nullptr
    if (x < 0 || x >= m_width || y < 0 || y >= m_height || m_cells[y][x] == nullptr)
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
    // Acumula los candies que tienen que explotar
    std::vector<Candy*> explodedCandies;

    bool exploded = true;

    // Mientras exploded sea true
    while (exploded)
    {
        exploded = false;

        // Vectores para separar tanto la coordenada 'x' y la 'y' de los candies a explotar
        std::vector<int> toExplodeX;
        std::vector<int> toExplodeY;

        // Si el candy debe explotar, guardar las coordenadas por separado en los dos vectores toExplodeX y toExplodeY
        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                if (m_cells[y][x] != nullptr && shouldExplode(x, y))
                {
                    toExplodeX.push_back(x);
                    toExplodeY.push_back(y);
                }
            }
        }

        // Este bucle se encarga de añadir al vector explodedCandies los candies que tienen que explotar y posteriormente los convierte en nullptr dentro de m_cells
        for (int i = 0; i < (toExplodeX.size()); i++)
        {
            explodedCandies.push_back(m_cells[toExplodeY[i]][toExplodeX[i]]);
            m_cells[toExplodeY[i]][toExplodeX[i]] = nullptr;

            exploded = true;
        }

        if (exploded)
        {
            // Los caramelos bajan en vertical, primero hay que saber que caramelos bajaran, recogiendolos fila por fila
            for (int x = 0; x < m_width; x++)
            {
                // Recoger caramelos de las diferentes columnas en un vector
                std::vector<Candy*> columnCandies;

                // Se recogen candies de abajo a arriba
                for (int y = m_height - 1; y >= 0; y--)
                {
                    // Todos los que no sean nullptr, se van guardando en el vector columnCandies
                    if (m_cells[y][x] != nullptr)
                    {
                        columnCandies.push_back(m_cells[y][x]);
                    }
                }

                // Bajar caramelos y poner nullptr en las posiciones que queden vacias por encima
                for (int y = m_height - 1; y >= 0; y--)
                {
                    int i = m_height - 1 - y; // Para ir bajando una posicion en la columna en cada iteración

                    // i nunca sera negativo en nuestro programa, pero para q el compilador no nos ponga un warning
                    // lo convertimos a int. El warning es porque columnCandies.size() devuelve un size_t (un tipo)
                    // y este solo puede ser positivo (ya que representa un tamaño)

                    // Mientras i (que representa el valor 0 en height (y) en la primera iteracion, y va incrementando hasta llegar al indice 9)
                    // sea menor que el tamaño del vector que guarda los candies de la columna, modifica m_cells con el valor correspondiente, ya
                    // sea un candy, o un nullptr
                    if (i < columnCandies.size())
                    {
                        m_cells[y][x] = columnCandies[i];
                    }
                    else
                    {
                        m_cells[y][x] = nullptr;
                    }
                }
            }
        }
    }

    // Devuelve el vector  de punteros candy con los candies explotados
    return explodedCandies;
}

// Para dado un tipo de candy, obtener su inicial 
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

// Para dado una inicial de un tipo de candy, obtener el tipo
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
            // Ultimo valor del enum de CandyType, usado como valor invalido (caracter desconocido en este caso), devolveria el numero
            // 6, ya que es el numero de tipos que hay en el enum
            return CandyType::COUNT;
    }
}

// Guarda el estado del tablero
bool Board::dump(const std::string& output_path) const
{
    // Crea un objeto file, que es un fichero de escritura
    std::ofstream file;
    // Lo abre en la ruta dada como parametro
    file.open(output_path);

    // Si no se abre el fichero, devolver false
    if (!file.is_open())
    {
        return false;
    }

    // Apuntar la anchura y la altura del tablero
    file << m_width << " " << m_height << "\n";


    // Escribirá un punto por cada nullptr que encuentre en m_cells, y en caso contrario, escribirá la inicial del
    // tipo de candy que encuentre. En cada iteracion de y, se hace un salto de linea al acabar el for interior de x
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            if (m_cells[y][x] == nullptr)
            {
                file << ". ";
            }
            else
            {
                file << typeToChar(m_cells[y][x]->getType()) << " ";
            }
        }
        file << "\n";
    }
    file.close();

    // Si todo va bien, devuelve true
    return true;
}

// Carga el fichero y reconstruye el tablero. Pasar la referencia del input path es util para no copiar un objeto que puede ser bastante grande
bool Board::load(const std::string& input_path)
{
    // Crea un objeto file (fichero de lectura)
    std::ifstream file;
    // Lo abre en la ruta dada
    file.open(input_path);

    if (!file.is_open())
    {
        return false;
    }

    // Leemos las dimensiones que guardamos en el fichero
    file >> m_width >> m_height;

    // Reiniciamos el tablero convirtiendo todo a nullptr. Como m_cells ya existe como miembro de la clase, hay que reinicializar
    // los valores del vector de vectores con .assign()
    m_cells.assign(m_height, std::vector<Candy*>(m_width, nullptr));
    // Elimina todos los elementos del vector, el tamaño pasa a 0 pero el espacio que ha reservado en memoria sigue ahi
    m_candyStorage.clear();
    // Reserva la memoria necesaria en el heap (en vez del stack) para 100 punteros a candies. Lo hacemos asi para que
    // cuando el vector crezca, no busque otro bloque de memoria en la ram y mueva todo, los punteros de m_cells quedarian
    // apuntando en la direccion antigua que ya no sirve
    // m_cells guarda punteros a candies que estan en candyStorage, que no se muevan es importante
    m_candyStorage.reserve(m_width * m_height);

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            char c;
            // Lee el caracter del fichero en cada iteracion y lo guarda en c
            file >> c;

            if (c == '.')
            {
                m_cells[y][x] = nullptr;
            }
            else
            {
                // Guarda en el vector de storage un objeto candy unico creado con el tipo que este especificado 
                // con la inicial encontrada en el fichero
                m_candyStorage.push_back(Candy(charToType(c)));
                // Guarda un puntero al ultimo candy que se ha añadido en m_candyStorage en las coordenadas que correspondan
                m_cells[y][x] = &m_candyStorage.back();
            }
        }
    }

    file.close();

    return true;
}
