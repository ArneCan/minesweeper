#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "genfield.c"
#include "gamelogic.c"

int main(void)
{
    uint8_t running = 1;
    uint8_t moves;
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
            
        showfield(array, size, &moves);                         //begin eerste move
        firstmove(array, size, dif, &moves);
                                                        // eind eerste move
        while (gamestate == REVEAL || gamestate == FLAG)
        {
            swapped = 0;
            //system("cls");

            result = playeraction(array, size, &moves, modus); //returned getal onder geselecteerde square of 0 bij een vlag
            if (result == 9) //checkt of onthulde vakje een bom is
            {
                gamestate = LOST;
            }
            else if (moves == 0) //check of alle vakjes onthult zijn
            {
                gamestate = WON;
            }

        if (gamestate == LOST)  //herstart en quit logica bij verliezen (alles anders dan r of R is stoppen)
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
            if (restart == 'R')
            {
                gamestate = CONFIG;
            }
            else
            {
                running = 0;
            }
            
        }
        else if (gamestate == WON) //herstart en quit logica bij win (alles anders dan r of R is stoppen)
        {
            printf("proficiat, je bent gewonnen. Druk r om opnieuw te beginnen of s om te stoppen: ");
            scanf(" %c", &restart);
            while (restart != 'r' && restart != 's')
            {
                printf("ongeldige input s = stop, r = restart: ");
                scanf(" %c", &restart);
            }
            if (restart == 'r' || restart == 'R')
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
