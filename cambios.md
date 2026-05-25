# Cambios Respecto a la Primera Entrega

## Board.h - Estructura

### Cambio de tipo en m_candyStorage:
Antes teniamos `vector<Candy>` que guardaba objetos por valor. Ahora usamos `vector<Candy*>` que guarda punteros a los caramelos creados con `new`.