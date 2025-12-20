#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "genfield.c"
#include "gamelogic.c"
#include <conio.h>

void innit(uint8_t array[15][15], uint8_t size);
void firstmove(uint8_t array[15][15], uint8_t size, uint8_t dif, uint8_t* bommen);




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
    uint8_t running = 1;
    uint8_t moves, bommen;
    char modus[7] = "onthul";
    while(running)
    {                                               //begin game setup
        uint8_t size, dif, r, c, swapped, result;
        char correct, restart;
        uint8_t array[15][15];

        srand(time(NULL));

        do {
            size = GetSize();
            dif = GetDif();
            innit(array, size);
        } while (gamestate == CONFIG);                  //end game setup
            
        showfield(array, size);                         //begin eerste move
        firstmove(array, size, dif, &bommen);
        moves = (size*size)-bommen-5;
                                                        // eind eerste move
        while (gamestate == REVEAL || gamestate == FLAG)
        {
            swapped = 0;
            //system("cls");

            result = playeraction(array, size, &moves, modus); //returned getal onder geselecteerde square of 0 bij een vlag
            if (result == 9)
            {
                gamestate = LOST;
            }

        if (gamestate == LOST)
        {
            system("cls");
            fflush(stdin);
            printf("BOEM: je bent verloren druk r om opnieuw te beginnen of s om te stoppen: ");
            scanf(" %c", &restart);
            while (restart != 'r' && restart != 's')
            {
                printf("ongeldige input s = stop, r = restart: ");
                scanf(" %c", &restart);
            }
            if (restart == 'r')
            {
                gamestate = CONFIG;
            }
            else
            {
                running = 0;
            }
            
        }
        else if (gamestate == WON)
        {
            printf("proficiat, je bent gewonnen. Druk r om opnieuw te beginnen of s om te stoppen: ");
            scanf(" %c", &restart);
            while (restart != 'r' && restart != 's')
            {
                printf("ongeldige input s = stop, r = restart: ");
                scanf(" %c", &restart);
            }
            if (restart == 'r')
            {
                gamestate = CONFIG;
            }
            else
            {
                running = 0;
            }
        }
    }
    
    }

    return 0;
}

void innit(uint8_t array[15][15], uint8_t size)
{
    char correct;
    for(int i = 0; i<size; i++)
    {
        for(int j = 0; j< size; j++)
        {
            array[i][j] = 10;
        }
    }
    gamestate = REVEAL;
}

void firstmove(uint8_t array[15][15], uint8_t size, uint8_t dif, uint8_t* bommen)
{
    uint8_t r,c;
    do
    {
        printf("kies een coordinaat (r c)");
        scanf("%hhu %hhu", &r, &c);
    } while (r < 0 || r >= size || c < 0 || c >= size );
    do
    {
        innit(array, size);
        *bommen = generate(array, size, dif);
    } while (array[r][c] != 10 );
    reveal(array, size, r, c);
    
}

