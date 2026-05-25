# Cambios Respecto a la Primera Entrega

## Board.h - Estructura

### Cambio de tipo en m_candyStorage:
Antes teniamos `vector<Candy>` que guardaba objetos por valor. Ahora usamos `vector<Candy*>` que guarda punteros a los caramelos creados con `new`.

### Metodos nuevos añadidos (public):
- `Board(const Board& b)` **constructor de copia**: Este constructor se llama cuando realizamos `Board b2 = b1;` o `Board b2(b1);`. Delegamos el trabajo a un metodo externo `copyFrom()` que realiza 3 cosas:

    - Copia las dimensiones de b1 (`m_width`, `m_height`).
    - Reserva un array nuevo para b2 (no comparte el de b1).
    - Crea nuevos candies copiados de los de b1, y los pone en su array.

    El resultado es que b2 tendrá exactamente los mismos datos que b1, pero en memoria separada. Si borramos b1, b2 sigue funcionando. Si modificamos b2, b1 no cambia.

- `Board& operator=(const Board& b)` **operador de asignación**: hace lo mismo que el constructor de copia, pero para un Board que ya existia con su propia memoria. Se llama cuando hacemos ```cpp
Board b1, b2;
b2 = b1;
```