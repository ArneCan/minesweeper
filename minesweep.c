#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "gamelogic.h"
#include "genfield.h"

int main(void)
{
    uint8_t running = 1;
    uint8_t moves;
    char modus[7] = "onthul";
    char ch;
    while(running)
    {   
        //game setup
        //aanmaken variabelen
        uint8_t size, dif, r, c, swapped, result;
        char correct, restart;
        uint8_t array[15][15];

        srand(time(NULL));

        //scherm leegmaken voor als er opnieuw begonnen wordt
        system("cls");
        //spelinstellingen
        gamestate = CONFIG;
        size = GetSize();
        dif = GetDif();

        //spel starten
        innit(array, size);
        showfield(array, size);                         
        firstmove(array, size, dif, &moves);

        //game loop
        while (gamestate == REVEAL || gamestate == FLAG)
        {
            swapped = 0;

            //getal onder vakje opslagen en nakijken
            result = playeraction(array, size, &moves, modus); 
            if (result == 9) 
            {
                //bom = verloren
                gamestate = LOST;
            }
            else if (moves == 0)
            {
                //alle vakjes zonder bom onthuld = gewonnen
                gamestate = WON;
            }

            //herstarten of stoppen na verlies
            if (gamestate == LOST)
            {
                system("cls");
                //buffer leegmaken
                while ((ch = getchar()) != '\n' && ch != EOF) {}

                printf("\nBOEM: je bent verloren druk r om opnieuw te beginnen of s om te stoppen: ");
                scanf(" %c", &restart);
                //input controle
                while (restart != 'r' && restart !='R' && restart != 's' && restart !='S')
                {
                    printf("\nongeldige input s = stop, r = restart: ");
                    scanf(" %c", &restart);
                }
                if (restart == 'R' || restart == 'r')
                {
                    gamestate = CONFIG;
                }
                else
                {
                    running = 0;
                }
                
            }
            //herstarten of stoppen na winst
            else if (gamestate == WON)
            {
                //buffer leegmaken
                while ((ch = getchar()) != '\n' && ch != EOF) {}
                printf("\nproficiat, je bent gewonnen. Druk r om opnieuw te beginnen of s om te stoppen: ");
                scanf(" %c", &restart);
                //input controle
                while (restart != 'r' && restart!='R' && restart != 's' && restart != 'S')
                {
                    printf("\nongeldige input s = stop, r = restart: ");
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
