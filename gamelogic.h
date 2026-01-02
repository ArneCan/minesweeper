#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <stdint.h>

// ----------------- gamelogic.c functions -----------------
enum states { CONFIG, REVEAL, FLAG, WON, LOST };
typedef enum states state;
extern state gamestate;

void showfield(uint8_t array[15][15], uint8_t size, uint8_t* move); //speelveld laten zien met coordinaten
uint8_t playeraction(uint8_t array[15][15], uint8_t size, uint8_t* move, char modus[7]); //verwerkt speler inputs
void firstmove(uint8_t array[15][15], uint8_t size, uint8_t dif, uint8_t* totmoves); //eerste move is altijd 0
void innit(uint8_t array[15][15], uint8_t size); //innitialisatie van het veld
void getcords(uint8_t* s, uint8_t* r, uint8_t* c, char modus[7]);
void reveal(uint8_t array[15][15],uint8_t size,uint8_t r, uint8_t c, uint8_t* move);

#endif // GAMELOGIC_H