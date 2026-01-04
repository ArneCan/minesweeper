#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamelogic.h"
#include "genfield.h"
#include <string.h>

state gamestate;

/*
*    laat het veld zien voor de speler
*    @param array 2d array voor het speelveld
*    @param size lengte van 1 zijde van het speelveld
*/
void showfield(uint8_t array[15][15], uint8_t size)
{   
    //geneste for loop om over array te loopen
    for (uint8_t i = 0; i<=size; i++)
    {
        for(uint8_t j = 0; j<=size; j++)
        {   
            // eerste vakje skippen (geen coördinaat hier)
            if(i == 0 && j == 0)
            {
                printf("   ");
                continue;
            }
            // coordinaten op eerste rij in het groen printen
            else if (i == 0) 
            {
                //juiste ofset bij 2 diget getallen
                if (j<= 10) 
                {
                    printf("\033[92m%d  \033[0m", j-1); 
                    continue;
                }
                else
                {
                    printf("\033[92m%d \033[0m", j-1);
                    continue;
                }
            }
            // coordinaten op eerste kolom in het groen printen
            else if (j == 0)
            {
                if (i <= 10)
                {
                    printf("\033[92m %d \033[0m", i-1);
                    continue;
                }
                else
                {
                    printf("\033[92m%d \033[0m", i-1);
                    continue;
                }  
            }
            //rest van de array printen
            else
            {
                // blok printen indien niet zichtbaar
                if (array[i-1][j-1] > 9 && array[i-1][j-1] < 20) 
                {
                    printf("%c  ", 219);
                }
                //rode F printen wanneer het een vlag is
                else if (array[i-1][j-1] > 19) 
                {
                    printf("\033[31mF  \033[0m");
                }
                // getal printen
                else 
                {
                    //0 ontzichtbaar maken om veld minder druk te maken
                    if(array[i-1][j-1] == 0)
                    {
                        printf("   ");
                    }
                    //getal printen
                    else
                    {
                        printf("%u  ", array[i-1][j-1]);
                    }
                }
            }
        }
        // volgende rij printen
        printf("\n");
    }
}

/*
*   vraagt inputs van speler, en verwerkt ze in het speelveld
*   @param array speelveld van de speler
*   @param size lengte van 1 zijde van het speelveld
*   @param move het aantal vakjes dat de speler moet onthullen om te winnen
*   @param modus vakje onthullen of vlag plaatsen?
*   @return de waarde onder het onthulde vakje of 0 bij het plaatsen van een vlag
*/
uint8_t playeraction(uint8_t array[15][15], uint8_t size, uint8_t* move, char modus[7])
{
    uint8_t swapped, r, c;
    //veld laten zien aan speler
    system("cls");
    showfield(array, size);
    //check out of bounds en of vakje al vlag is of al gerevealed is
    do
    {
        getcords(&swapped, &r, &c, modus);
    } while (array[r][c] -10 < 0 || array[r][c] > 29 || r >= size || c >= size);

    //vakje zichtbaar maken
    if(gamestate == REVEAL) 
    {
        //vlag laten staan
        if (array[r][c] > 19) 
        {
            printf("hier staat al een vlag");
            return 0;
        }
        //vakje zichtbaar maken
        else    
        {
            reveal(array, size, r, c, move);
            return array[r][c];
        }
    }

    //vlag plaatsen
    else
    {
        //vlag weghalen wanneer er al een vlag staat
        if (array[r][c] > 19) 
        {
            array[r][c] -= 10;
            return 0;
        }
        //vlag plaatsen
        else 
        {
            array[r][c] += 10;
            return 0;
        }
    }
}

/*
*   helperfunctie van getcords
*
*   controleert of de speler wilt wisselen tussen vlag plaatsen en vakje onthullen
*   @param *gamestate pointer naar de gamestate die bepaald de speler doet
*   @param input het getal dat de speler heeft ingegeven 15 = wisselen
*   @param modus vakje onthullen of vlag plaatsen?
*   @returns 1 bij verandering 0 bij geen verandering
*/
uint8_t checkswap(state *gamestate, uint8_t input, char modus[7])
{
    if (input == 15) 
    {
        if (*gamestate == FLAG)
        {
            strcpy(modus, "onthul");
            *gamestate = REVEAL;
        }
        else
        {
            strcpy(modus, "vlag");
            *gamestate = FLAG;
        }
        return 1;
    }
    return 0;
}

/*
*   helperfunctie van playeraction  
* 
*   vraagt coördinaten aan de speler
*   @param *s pointer die aangeeft of de speler wil wisselen tussen vlag of onthullen
*   @param *r de rij die de speler selecteert
*   @param *c de colom die de speler selecteert
*   @param modus onthullen of vlag plaatsen?
*/
void getcords(uint8_t* s, uint8_t* r, uint8_t* c, char modus[7])
{
    uint8_t checkinput, ch;
    
    //input van speler vragen en controlleren
    printf("mode: %s\nvul rij en kolom in met spatie in (15 om te vlag te toggelen)", modus);
    checkinput = scanf("%hhu", r);
    //controle of input juiste type is
    while (checkinput != 1)
    {
        printf("ongeldige input\n");
        //input buffer leeg maken
        while ((ch = getchar()) != '\n' && ch != EOF) {} 
        printf("mode: %s\nvul rij en kolom in met spatie in (15 om te vlag te toggelen)", modus);
        checkinput = scanf("%hhu", r);
        printf("\n");
    }
    //mode wisselen indien nodig
    *s = checkswap(&gamestate, *r, modus);
    if (*s)
    {
        return;
    }

    //enkel zichtbaar wanneer speler enkel kolom ingeeft
    printf("vul colom in (15 om te vlag te toggelen)"); 
    checkinput = scanf("%hhu", c);
    //input type controlleren
    while (checkinput != 1)
    {
        printf("ongeldige input\n");
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        printf("mode: %s\nvul rij en kolom in met spatie in (15 om te vlag te toggelen)", modus); //vraagt rij en kolom en checkt voor wisselen
        checkinput = scanf("%hhu", c);
        printf("\n");
    }
    printf("\n");
    //mode wisselen indien nodig
    *s = checkswap(&gamestate, *c, modus);
    if (*s)
    {
        return;
    }
}

/*
*   helperfunctie van playeraction
*
*   maakt geselecteerde vakje zichtbaar
*
*   controlleert of het vakje een nul is
*
*   controlleert of er nog andere nullen rond zitten
*   @param array speelveld van de speler
*   @param size lengte van 1 zijde van het speelveld
*   @param r de rij waarop het vakje staat dat zichtbaar gemaakt wordt
*   @param c de colom waarop het vakje staat dat zichtbaar gemaakt wordt
*   @param *move het aantal vakjes dat de speler moet onthullen om te winnen
*/
void reveal(uint8_t array[15][15],uint8_t size,uint8_t r, uint8_t c, uint8_t* move)
{
    //vakje zichtbaar maken = 1 move minder
    array[r][c] -= 10; 
    *move -= 1;

    //maakt alle vakjes rondom zichtbaar als het vakje 0 bevat
    if (array[r][c] == 0)
    {
        //rond het vakje loopen
        for(int8_t i = -1; i<2; i++)
        {
            for(int8_t j = -1; j<2; j++)
            {
                //vakjes buiten het veld overslaan
                if(r+i >= size || r+i < 0 || c+j >= size || c+j < 0) 
                {
                    continue;
                }
                //eigen vakje overslaan
                if (j == 0 && i == 0)
                {
                    continue;
                }
                //checken of vakje nog niet zichtbaar is
                if(array[r+i][c+j] <20 && array[r+i][c+j] > 9) 
                {
                    //vakje zichtbaar maken
                    reveal(array, size, r+i, c+j, move);
                }
            }
        }
    }
}

/*
*   eerste move heeft andere logica
*
*   vraagt eerste coörinaat aan speler
*
*   genereert veld tot geselecteerde vakje een 0 is
*
*   @param array speelveld van de speler
*   @param size lengte van zijde van het speelveld
*   @param dif moeilijkheid van het spel (0-2)
*   @param *totmoves het totaal aantal vakjes waar geen bommen op staan
*/
void firstmove(uint8_t array[15][15], uint8_t size, uint8_t dif, uint8_t* totmoves)
{
    uint8_t r,c, bommen, checkinput, ch;

    //input krijgen van user en controleren
    do
    {
        printf("kies een begin coordinaat (r c)");
        checkinput = scanf("%hhu %hhu", &r, &c);
        while (checkinput != 2)
        {
            printf("ongeldige input\n");
            //buffer leeg maken
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("kies een begin coordinaat (r c)");
            checkinput = scanf("%hhu %hhu", &r, &c);
        }
    } while (r < 0 || r >= size || c < 0 || c >= size );

    //veld blijven genereren tot geselecteerde vakje een 0 is
    do 
    {
        innit(array, size);
        bommen = generate(array, size, dif);
        *totmoves = (size*size)-bommen;
    } while (array[r][c] != 10 );
    //vakjes zichtbaar maken
    reveal(array, size, r, c, totmoves); 
}

/*
*   initialiseerd het veld
*   @param array het speelveld
*   @size grootte dat geinitialiseerd moet worden
*/
void innit(uint8_t array[15][15], uint8_t size)
{
    char correct;
    //elk vakje in de array een waarde geven
    for(uint8_t i = 0; i<size; i++) 
    {
        for(uint8_t j = 0; j< size; j++)
        {
            array[i][j] = 10;
        }
    }
    //spel starten
    gamestate = REVEAL; 
}