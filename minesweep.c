#include <stdio.h>
#include <stdlib.h>
#include "genfield.c"
#include <conio.h>
#include "gamelogic.c"

enum states {CONFIG, REVEAL, FLAG, END};
typedef enum states state;

void innit(uint8_t array[15][15]);
void firstmove(uint8_t array[15][15], uint8_t size, uint8_t dif);
uint8_t checkswap(state *gamestate, uint8_t input);



/*int main()
{
    enum state {CONFIG, REVEAL, FLAG, END};
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
}*/

int main(void)
{
    state gamestate = CONFIG;
    uint8_t size, dif, r, c, swapped;
    char correct;
    uint8_t array[15][15];

    srand(time(NULL));

    do {
        size = GetSize();
        dif = GetDif();
        innit(array);
        printf("ben je zeker dat je deze instellingen wilt behouden? (y/n)");
        scanf(" %c", &correct);
        if (correct == 'y')
        {
            gamestate = REVEAL;
        }
    } while (gamestate == CONFIG);
    showfield(array, size);
    firstmove(array, size, dif);
    while (gamestate == REVEAL || gamestate == FLAG)
    {
        swapped = 0;
        system("cls");
        showfield(array, size);

        printf("vul rij en kolom in met spatie in (15 om te vlag te toggelen)");
        scanf("%hhu", &r);
        swapped = checkswap(&gamestate, r);
        if (swapped)
        {
            continue;
        }

        printf("vul colom in (15 om te vlag te toggelen)");
        scanf("%hhu", &c);
        swapped = checkswap(&gamestate, c);
        if (swapped)
        {
            continue;
        }

        editsquare(array, size, gamestate, (uint8_t)r, (uint8_t)c);
    }

    return 0;
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

uint8_t checkswap(state *gamestate, uint8_t input)
{
    if (input == 15)
    {
        if (*gamestate == FLAG)
        {
            *gamestate = REVEAL;
        }
        else
        {
            *gamestate = FLAG;
        }
        return 1;
    }
    return 0;
}