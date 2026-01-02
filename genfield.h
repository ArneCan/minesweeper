#ifndef GENFIELD_H
#define GENFIELD_H

#include <stdint.h>

// ----------------- genfield.c functions -----------------
uint8_t GetSize();
uint8_t GetDif();
uint8_t generate(uint8_t array[15][15], uint8_t size, uint8_t dif); //telt het aantal bommen rondom een vakje

#endif // GENFIELD_H
