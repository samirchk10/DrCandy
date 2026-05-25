# Cambios Respecto a la Primera Entrega

## Board.h - Estructura

### Cambio de tipo en m_candyStorage:
Antes teniamos `vector<Candy>` que guardaba objetos por valor. Ahora usamos `vector<Candy*>` que guarda punteros a los caramelos creados con `new`.

### Metodos nuevos añadidos (public):
- `Board(const Board& b)` constructor de copia: Este constructor se llama cuando realizamos `Board b2 = b1;` o `Board b2(b1);`. Delegamos el trabajo a un metodo externo `copyFrom()` que explicaremos mas adelante. 

    Realiza 3 cosas:

        - Copia las dimensiones de b1 (`m_width`, `m_height`).
        - Reserva un array nuevo para b2 (no comparte el de b1).
        - Crea nuevos candies copiados de los de b1, y los pone en su array.