#include <stdio.h>
#include <stdlib.h>
#include "genfield.c"
#include <conio.h>
#include "gamelogic.c"


void innit(uint8_t array[15][15]);
void firstmove(uint8_t array[15][15], uint8_t size, uint8_t dif);


int main()
{
    uint8_t size, dif;
    srand(time(NULL));
    uint8_t array[15][15];
    size = GetSize();
    dif = GetDif();
    innit(array);
    showfield(array, size);
    firstmove(array, size, dif);
    showarr(array, size);
    showfield(array, size);
    getch();
}

void innit(uint8_t array[15][15])
{
    for(int i = 0; i<15; i++)
    {
        for(int j = 0; j< 15; j++)
        {
            array[i][j] = 10;
        }
    }
}

void firstmove(uint8_t array[15][15], uint8_t size, uint8_t dif)
{
    uint8_t r,c;
    do
    {
        printf("kies een coordinaat (r c)");
        scanf("%hhu %hhu", &r, &c);
    } while (r < 0 || r >= size || c < 0 || c >= size );
    do
    {
        innit(array);
        generate(array, size, dif);
    } while (array[r][c] == 19 || (array[r][c-1] == 19 && c-1 >= 0) || (array[r-1][c] == 19 && r-1 >= 0) || (array[r+1][c] == 19 && r+1 <size) || (array[r][c+1] == 19 && c+1 < size));
    array[r][c] -= 10;
    if (r-1 >= 0)
    {
        array[r-1][c] -= 10;
    }
    if (c-1 >= 0)
    {
        array[r][c-1] -= 10;
    }
    if (r+1 < size)
    {
        array[r+1][c] -= 10;
    }
    if (c+1 < size)
    {
        array[r][c+1] -= 10;
    }
    
}