/**
 * FITXER test.cpp
 * AUTORS Alan Tchertchessov y Samir Channagui
 * DATA 24/03/2026
 * Tests de la clase Board. Comprueba el correcto funcionamiento
 * de las funciones getCell, setCell, shouldExplode (conjuntamente con checkMatchDirection), explodeAndDrop,
 * typeToChar, charToType, dump y load.
 */

#include "board.h"
#include "candy.h"
#include "controller.h"
#include "game.h"
#include "util.h"
#include <filesystem>

bool test()
{
    // Test board 2D container
    Candy c(CandyType::TYPE_ORANGE);
    Board b(10, 10);
    b.setCell(&c, 0, 0);
    if (b.getCell(0, 0) != &c)
    {
        return false;
    }

    // Test dimensiones por defecto
    {
        Board b;
        
        if (b.getWidth() != DEFAULT_BOARD_WIDTH || b.getHeight() != DEFAULT_BOARD_HEIGHT)
        {
            std::cout << "Dimensiones por defecto cargadas incorrectamente, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Dimensiones por defecto cargadas correctamente, TEST CORRECTO" << std::endl;
    }

    // Test dimensiones personalizadas
    {
        Board b(5, 7);

        if (b.getWidth() != 5 || b.getHeight() != 7)
        {
            std::cout << "Dimensiones personalizadas no cargadas, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Dimensiones personalizadas cargadas correctamente, TEST CORRECTO" << std::endl;
    }

    // Test para ver si una celda nullptr no explota
    {
        Board b(10, 10);

        if (b.shouldExplode(0, 0) != false)
        {
            std::cout << "Celda nula explota, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Celda nula no explota, TEST CORRECTO" << std::endl;
    }

    // Test para ver que un solo caramelo no explota
    {
        Board b(10, 10);

        Candy candy(CandyType::TYPE_RED);
        b.setCell(&candy, 5, 5);

        if (b.shouldExplode(5, 5) != false)
        {
            std::cout << "Candy solo explota, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Candy solo no explota, TEST CORRECTO" << std::endl;
    }




    // TESTS PARA shouldExplode




    // Test para ver si tres candies del mismo tipo explotan en horizontal
    {
        Board b(10, 10);

        Candy candy1(CandyType::TYPE_RED);
        Candy candy2(CandyType::TYPE_RED);
        Candy candy3(CandyType::TYPE_RED);

        b.setCell(&candy1, 0, 0);
        b.setCell(&candy2, 1, 0);
        b.setCell(&candy3, 2, 0);

        if (b.shouldExplode(1, 0) != true)
        {
            std::cout << "Los 3 candies en HORIZONTAL no explotan, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Los 3 candies en HORIZONTAL explotan, TEST CORRECTO" << std::endl;
    }

    // Test para ver si 4 candies del mismo tipo explotan en horizontal
    {
        Board b(10, 10);

        Candy candy1(CandyType::TYPE_RED);
        Candy candy2(CandyType::TYPE_RED);
        Candy candy3(CandyType::TYPE_RED);
        Candy candy4(CandyType::TYPE_RED);

        b.setCell(&candy1, 0, 0);
        b.setCell(&candy2, 1, 0);
        b.setCell(&candy3, 2, 0);
        b.setCell(&candy4, 3, 0);

        if (b.shouldExplode(1, 0) != true)
        {
            std::cout << "Los 4 candies en HORIZONTAL no explotan, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Los 4 candies en HORIZONTAL explotan, TEST CORRECTO" << std::endl;
    }

    // Test para ver si tres candies del mismo tipo explotan en vertical
    {
        Board b(10, 10);

        Candy candy1(CandyType::TYPE_GREEN);
        Candy candy2(CandyType::TYPE_GREEN);
        Candy candy3(CandyType::TYPE_GREEN);

        b.setCell(&candy1, 0, 0);
        b.setCell(&candy2, 0, 1);
        b.setCell(&candy3, 0, 2);

        if (b.shouldExplode(0, 1) != true)
        {
            std::cout << "Los 3 candies en VERTICAL explotan, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Los 3 candies en VERTICAL explotan, TEST CORRECTO" << std::endl;
    }

    // Test para ver si 4 candies del mismo tipo explotan en vertical
    {
        Board b(10, 10);

        Candy candy1(CandyType::TYPE_GREEN);
        Candy candy2(CandyType::TYPE_GREEN);
        Candy candy3(CandyType::TYPE_GREEN);
        Candy candy4(CandyType::TYPE_GREEN);

        b.setCell(&candy1, 0, 0);
        b.setCell(&candy2, 0, 1);
        b.setCell(&candy3, 0, 2);
        b.setCell(&candy4, 0, 3);

        if (b.shouldExplode(0, 1) != true)
        {
            std::cout << "Los 4 candies en VERTICAL no explotan, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Los 4 candies en VERTICAL explotan, TEST CORRECTO" << std::endl;
    }

    // Test para ver si tres candies del mismo tipo explotan en diagonal /
    {
        Board b(10, 10);

        Candy candy1(CandyType::TYPE_BLUE);
        Candy candy2(CandyType::TYPE_BLUE);
        Candy candy3(CandyType::TYPE_BLUE);

        b.setCell(&candy1, 3, 1);
        b.setCell(&candy2, 2, 2);
        b.setCell(&candy3, 1, 3);

        if (b.shouldExplode(2, 2) != true)
        {
            std::cout << "Los 3 candies en DIAGONAL / no explotan, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Los 3 candies en DIAGONAL / explotan, TEST CORRECTO" << std::endl;
    }

    // Test para ver si 4 candies del mismo tipo explotan en diagonal /
    {
        Board b(10, 10);

        Candy candy1(CandyType::TYPE_BLUE);
        Candy candy2(CandyType::TYPE_BLUE);
        Candy candy3(CandyType::TYPE_BLUE);
        Candy candy4(CandyType::TYPE_BLUE);

        b.setCell(&candy1, 3, 1);
        b.setCell(&candy2, 2, 2);
        b.setCell(&candy3, 1, 3);
        b.setCell(&candy4, 0, 4);

        if (b.shouldExplode(2, 2) != true)
        {
            std::cout << "Los 4 candies en DIAGONAL / no explotan, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Los 4 candies en DIAGONAL / explotan, TEST CORRECTO" << std::endl;
    }

    // Test para ver si tres candies del mismo tipo explotan en diagonal inversa
    {
        Board b(10, 10);

        Candy candy1(CandyType::TYPE_ORANGE);
        Candy candy2(CandyType::TYPE_ORANGE);
        Candy candy3(CandyType::TYPE_ORANGE);

        b.setCell(&candy1, 1, 1);
        b.setCell(&candy2, 2, 2);
        b.setCell(&candy3, 3, 3);

        if (b.shouldExplode(2, 2) != true)
        {
            std::cout << "Los 3 candies en DIAGONAL inversa no explotan, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Los 3 candies en DIAGONAL inversa explotan, TEST CORRECTO" << std::endl;
    }

    // Test para ver si 4 candies del mismo tipo explotan en diagonal inversa
    {
        Board b(10, 10);

        Candy candy1(CandyType::TYPE_ORANGE);
        Candy candy2(CandyType::TYPE_ORANGE);
        Candy candy3(CandyType::TYPE_ORANGE);
        Candy candy4(CandyType::TYPE_ORANGE);

        b.setCell(&candy1, 1, 1);
        b.setCell(&candy2, 2, 2);
        b.setCell(&candy3, 3, 3);
        b.setCell(&candy4, 4, 4);

        if (b.shouldExplode(2, 2) != true)
        {
            std::cout << "Los 4 candies en DIAGONAL inversa no explotan, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Los 4 candies en DIAGONAL inversa explotan, TEST CORRECTO" << std::endl;
    }
    
    // Test para ver si 3 candies, donde uno no es del mismo tipo, no explotan en diagonal inversa
    {
        Board b(10, 10);

        Candy candy1(CandyType::TYPE_ORANGE);
        Candy candy2(CandyType::TYPE_ORANGE);
        Candy candy3(CandyType::TYPE_RED);

        b.setCell(&candy1, 1, 1);
        b.setCell(&candy2, 2, 2);
        b.setCell(&candy3, 3, 3);

        if (b.shouldExplode(2, 2) != false)
        {
            std::cout << "Los 4 candies (con uno diferente) en DIAGONAL inversa explotan, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Los 4 candies (con uno diferente) en DIAGONAL inversa no explotan, TEST CORRECTO" << std::endl;
    }




    // TESTS PARA ExplodeAndDrop




    // Test para comprobar si devuelve un vector (con el numero que lo identifica en el enum) de los candies explotados
    // Tambien comprueba si detecta una diagonal inversa de 3 candies del mismo tipo y los explota, a su vez,
    // indica que los candies explotados son los correctos
    {
        Board b(10, 10);
        
        Candy candy1(CandyType::TYPE_ORANGE);
        Candy candy2(CandyType::TYPE_ORANGE);
        Candy candy3(CandyType::TYPE_ORANGE);

        // En diagonal inversa a /
        b.setCell(&candy1, 1, 1);
        b.setCell(&candy2, 2, 2);
        b.setCell(&candy3, 3, 3);

        std::vector<Candy*> exploded = b.explodeAndDrop();

        if (static_cast<int>(exploded.size()) != 3)
        {
            std::cout << "El tamaño del vector no es igual a 3, TEST FALLIDO" << std::endl;
            return false;
        }

        for (int i = 0; i < static_cast<int>(exploded.size()); i++)
        {
            std::cout << static_cast<int>(exploded[i]->getType()) << " ";
        }

        if (exploded.empty())
        {
            std::cout << "Devuelve un vector vacio, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << " -> Devuelve un vector con candies explotados, TEST CORRECTO" << std::endl;
    }


    // Test que comprueba que se devuelva un vector vacio cuando no explota ninguna linea
    {
        Board b(10, 10);
        Candy candy1(CandyType::TYPE_RED);
        Candy candy2(CandyType::TYPE_YELLOW);

        b.setCell(&candy1, 0, 0);
        b.setCell(&candy2, 1, 0);

        std::vector<Candy*> exploded = b.explodeAndDrop();

        if (!exploded.empty())
        {
            std::cout << "Deberia devolver un vector vacio, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Devuelve un vector vacio, TEST CORRECTO" << std::endl;
    }


    // Test para comprobar que si 3 candies en linea coinciden en tipo, las celdas quedan nullptr despues de explotar
    {
        Board b(10, 10);
        Candy candy1(CandyType::TYPE_RED);
        Candy candy2(CandyType::TYPE_RED);
        Candy candy3(CandyType::TYPE_RED);

        b.setCell(&candy1, 0, 9);
        b.setCell(&candy2, 1, 9);
        b.setCell(&candy3, 2, 9);

        std::vector<Candy*> exploded = b.explodeAndDrop();

        if (static_cast<int>(exploded.size()) != 3)
        {
            std::cout << "Deberia devolver 3 candies, TEST FALLIDO" << std::endl;
            return false;
        }

        if (b.getCell(0,9) != nullptr || b.getCell(1,9) != nullptr || b.getCell(2,9) != nullptr)
        {
            std::cout << "Las celdas deberian quedar nullptr, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "La linea de 3 candies iguales explota y las celdas quedan nullptr, TEST CORRECTO" << std::endl;
    }


    // Test para comprobar que un candy encima de una linea de candies que explota, cae abajo
    {
        Board b(10, 10);
        Candy candy1(CandyType::TYPE_RED);
        Candy candy2(CandyType::TYPE_RED);
        Candy candy3(CandyType::TYPE_RED);
        Candy candy4(CandyType::TYPE_YELLOW);

        b.setCell(&candy1, 0, 9);
        b.setCell(&candy2, 1, 9);
        b.setCell(&candy3, 2, 9);
        b.setCell(&candy4, 0, 8);

        b.explodeAndDrop();

        if (b.getCell(0, 9)->getType() != CandyType::TYPE_YELLOW)
        {
            std::cout << "El candy amarillo no ha caido abajo despues de la explosion, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "El candy amarillo ha caido abajo despues de la explosion, TEST CORRECTO" << std::endl;
    }


    // Test de reaccion en cadena, comprobacion de que han quedado nullptr y un candy diferente a los explotados ha caido abajo
    {
        Board b(10, 10);
        Candy candy1(CandyType::TYPE_RED);
        Candy candy2(CandyType::TYPE_RED);
        Candy candy3(CandyType::TYPE_RED);
        
        Candy candy4(CandyType::TYPE_YELLOW);
        Candy candy5(CandyType::TYPE_YELLOW);
        Candy candy6(CandyType::TYPE_YELLOW);

        Candy candyExtra(CandyType::TYPE_BLUE);

        b.setCell(&candy1, 0, 9);
        b.setCell(&candy2, 1, 9);
        b.setCell(&candy3, 2, 9);
        b.setCell(&candy4, 0, 6);
        b.setCell(&candy5, 0, 7);
        b.setCell(&candy6, 0, 8);
        
        //Deberia caer a (0, 9)
        b.setCell(&candyExtra, 0, 5);

        std::vector<Candy*> exploded = b.explodeAndDrop();

        if (static_cast<int>(exploded.size()) != 6)
        {
            std::cout << "Deberia devolver 6 candies, TEST FALLIDO" << std::endl;
            return false;
        }

        // Comprobar que han quedado nullptr las celdas que estaban ocupadas, menos la (0, 9), donde deberia caer el candy blue 
        // y la (0, 5) que se comprueba despues
        if (b.getCell(1, 9) != nullptr || b.getCell(2, 9) != nullptr || b.getCell(0, 6) != nullptr
            || b.getCell(0, 7) != nullptr || b.getCell(0, 8) != nullptr)
        {
            std::cout << "Las celdas deberian quedar nullptr, TEST FALLIDO" << std::endl;
            return false;
        }

        if (b.getCell(0, 9) == nullptr || b.getCell(0, 9)->getType() != CandyType::TYPE_BLUE)
        {
            std::cout << "El candy blue no ha caido correctament, TEST FALLIDO" << std::endl;
            return false;
        }

        //Comprobamos que la celda donde estaba antes el candyExtra, es nullptr
        if (b.getCell(0, 5) != nullptr)
        {
            std::cout << "La celda donde estaba antes el candy blue, no ha quedado vacia, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Reaccion en cadena y caida correcta, TEST CORRECTO" << std::endl;
    }
    



    // TESTS PARA typeToChar




    // Test que comprueba la correspondencia de tipo de candy a la letra inicial que respresenta el tipo
    {
        Board b(10, 10);

        if (b.typeToChar(CandyType::TYPE_RED) != 'R')
        {
            std::cout << "typeToChar TYPE_RED falla, TEST FALLIDO" << std::endl;
            return false;
        }

        if (b.typeToChar(CandyType::TYPE_BLUE) != 'B')
        {
            std::cout << "typeToChar TYPE_BLUE falla, TEST FALLIDO" << std::endl;
            return false;
        }

        if (b.typeToChar(CandyType::TYPE_GREEN) != 'G')
        {
            std::cout << "typeToChar TYPE_GREEN falla, TEST FALLIDO" << std::endl;
            return false;
        }

        if (b.typeToChar(CandyType::TYPE_YELLOW) != 'Y')
        {
            std::cout << "typeToChar TYPE_YELLOW falla, TEST FALLIDO" << std::endl;
            return false;
        }

        if (b.typeToChar(CandyType::TYPE_PURPLE) != 'P')
        {
            std::cout << "typeToChar TYPE_PURPLE falla, TEST FALLIDO" << std::endl;
            return false;
        }

        if (b.typeToChar(CandyType::TYPE_ORANGE) != 'O')
        {
            std::cout << "typeToChar TYPE_ORANGE falla, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Todas las comprobaciones de typeToChar son correctas, TEST CORRECTO" << std::endl;
    }




    // TESTS PARA charToType




    {
        Board b(10, 10);

        if (b.charToType('R') != CandyType::TYPE_RED)
        {
            std::cout << "charToType (R) falla, TEST FALLIDO" << std::endl;
            return false;
        }

        if (b.charToType('B') != CandyType::TYPE_BLUE)
        {
            std::cout << "charToType (B) falla, TEST FALLIDO" << std::endl;
            return false;
        }

        if (b.charToType('G') != CandyType::TYPE_GREEN)
        {
            std::cout << "charToType (G) falla, TEST FALLIDO" << std::endl;
            return false;
        }

        if (b.charToType('Y') != CandyType::TYPE_YELLOW)
        {
            std::cout << "charToType (Y) falla, TEST FALLIDO" << std::endl;
            return false;
        }

        if (b.charToType('P') != CandyType::TYPE_PURPLE)
        {
            std::cout << "charToType (P) falla, TEST FALLIDO" << std::endl;
            return false;
        }

        if (b.charToType('O') != CandyType::TYPE_ORANGE)
        {
            std::cout << "charToType (O) falla, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Todas las comprobaciones de charToType son correctas, TEST CORRECTO" << std::endl;
    }




    // TESTS PARA dump and load




    // Dump and load board
    {
        Board b2(10, 10);
        if (!b.dump(getDataDirPath() + "dump_board.txt"))
        {
            return false;
        }
        if (!b2.load(getDataDirPath() + "dump_board.txt"))
        {
            return false;
        }
        if (b2.getCell(0, 0)->getType() != c.getType())
        {
            return false;
        }
        std::filesystem::remove(getDataDirPath() + "dump_board.txt");

        std::cout << "Dump and load, correcto" << std::endl;
    }

    // Test de load de un fichero que no existe
    {
        Board b(10, 10);

        if (b.load("ficheroNoExiste.txt") != false)
        {
            std::cout << "Deberia devolver false ya que no existe el fichero, TEST FALLIDO" << std::endl;
            return false;
        }

        std::cout << "Load devuelve false, el fichero no existe, TEST CORRECTO" << std::endl;
    }



    // Test constructor copia Deep Copy
    {
        Board original(10, 10);
        Candy candy(CandyType::TYPE_RED);
        original.setCell(&candy, 0, 0);

        Board copia = original;

        Candy* a = original.getCell(0, 0);
        Candy* b = copia.getCell(0, 0);

        if (b == nullptr || b->getType() != CandyType::TYPE_RED)
        {
            return false;
        }
   
        if (a == b)
        {
            return false;
        }
        
        std::cout << "Constructor deep copy correcto" << std::endl;
    }

    // Test operadro asignacion
    {
        Board original(10, 10);
        Candy candy(CandyType::TYPE_GREEN);
        original.setCell(&candy, 2, 3);

        Board asignada(10, 10);
        asignada = original;

        Candy* b = asignada.getCell(2, 3);
        if (b == nullptr || b->getType() != CandyType::TYPE_GREEN)
        {
            return false;
        }

        std::cout << "Operador de asignacion correcto" << std::endl;
    }

    // Dump and load game
    {
        Game g;
        Controller cont;
        g.update(cont);
        if (!g.dump(getDataDirPath() + "dump_game.txt"))
        {
            return false;
        }
        Game g2;
        if (!g2.load(getDataDirPath() + "dump_game.txt"))
        {g
            return false;
        }
        if (g != g2)
        {
            return false;
        }
        std::filesystem::remove(getDataDirPath() + "dump_game.txt");
    }

    return true;
}
