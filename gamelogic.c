#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "gamelogic.h"
#include "genfield.h"
#include <string.h>

state gamestate;

void showfield(uint8_t array[15][15], uint8_t size, uint8_t* move)
{
    for (uint8_t i = 0; i<=size; i++)//geneste for loop om over array te loopen
    {
        for(uint8_t j = 0; j<=size; j++)
        {
            if(i == 0 && j == 0)// eerste vakje skippen (geen coordinaat hier)
            {
                printf("   ");
                continue;
            }
            else if (i == 0) // coordinaten op eerste rij printen
            {
                if (j<= 10) //juiste ofset bij 2 diget getallen
                {
                    printf("\033[92m%d  \033[0m", j-1); //coordinaten groen maken
                    continue;
                }
                else
                {
                    printf("\033[92m%d \033[0m", j-1); //groen maken
                    continue;
                }
            }
            else if (j == 0) // coordinaten op eerste collom printen
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
            else //rest van de array printen
            {
                if (array[i-1][j-1] > 9 && array[i-1][j-1] < 20) // blok printen indien niet zichtbaar
                {
                    printf("%c  ", 219);
                }
                else if (array[i-1][j-1] > 19) //rode F printen wanneer het een vlag is
                {
                    printf("\033[31mF  \033[0m");
                }
                
                else // getal printen
                {
                    if(array[i-1][j-1] == 0) //spatie voor 0 om veld minder druk te maken
                    {
                        printf("   ");
                    }
                    else //getal printen
                    {
                        printf("%u  ", array[i-1][j-1]);
                    }
                }
            }
        }
        printf("\n"); // volgende rij printen
    }
}

uint8_t playeraction(uint8_t array[15][15], uint8_t size, uint8_t* move, char modus[7])
{
    uint8_t swapped, r, c;
    do //check out of bounds en of vakje al vlag is of al gerevealed is
    {
        showfield(array, size, move);
        getcords(&swapped, &r, &c, modus);
        system("cls");
    } while (array[r][c] -10 < 0 || array[r][c] > 29 || r >= size || c >= size);


    if(gamestate == REVEAL) //vakje zichtbaar maken
    {
        if (array[r][c] > 19) //checken voor vlag
        {
            printf("hier staat al een vlag");
            return 0;
        }
        else    //vakje zichtbaar maken
        {
            reveal(array, size, r, c, move);
            return array[r][c]; //Waarde van zichtbare vakje returnen
        }
    }

    else//vlag plaatsen
    {
        if (array[r][c] > 19) //vlag weghalen wanneer er al een vlag staat
        {
            array[r][c] -= 10;
            return 0;
        }
        else //vlag plaatsen
        {
            array[r][c] += 10;
            return 0;
        }
    }
}

uint8_t checkswap(state *gamestate, uint8_t input, char modus[7])
{
    if (input == 15) // 15 = mode wisselen
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

void getcords(uint8_t* s, uint8_t* r, uint8_t* c, char modus[7])
{
    uint8_t checkinput, ch;
    printf("mode: %s\nvul rij en kolom in met spatie in (15 om te vlag te toggelen)", modus); //vraagt rij en kolom en checkt voor wisselen
    checkinput = scanf("%hhu", r); //checkt eerste getal
    while (checkinput != 1)
    {
        printf("ongeldige input\n");
        while ((ch = getchar()) != '\n' && ch != EOF) {} //input buffer leeg maken
        printf("mode: %s\nvul rij en kolom in met spatie in (15 om te vlag te toggelen)", modus); //vraagt rij en kolom en checkt voor wisselen
        checkinput = scanf("%hhu", r);
    }
    *s = checkswap(&gamestate, *r, modus);
    if (*s)
    {
        return;
    }

    printf("vul colom in (15 om te vlag te toggelen)"); //enkel zichtbaar wanneer speler maar 1 getal ingeeft
    checkinput = scanf("%hhu", c); //checkt tweede getal
    while (checkinput != 1)
    {
        printf("ongeldige input\n");
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        printf("mode: %s\nvul rij en kolom in met spatie in (15 om te vlag te toggelen)", modus); //vraagt rij en kolom en checkt voor wisselen
        checkinput = scanf("%hhu", c);
    }
    *s = checkswap(&gamestate, *c, modus);
    if (*s)
    {
        return;
    }
}

void reveal(uint8_t array[15][15],uint8_t size,uint8_t r, uint8_t c, uint8_t* move)
{
    array[r][c] -= 10; //vakje zichtbaar maken
    *move -= 1;        //elke keer dat een vakje zichtbaar gemaakt wordt moet de speler een move minder doen (*move = aantal vakjes dat geen bom is)
    if (array[r][c] == 0) //checkt of zichtbaar gemaakte vakje gelijk is aan 0
    {
        for(int8_t i = -1; i<2; i++) //alle vakjes die not niet zichtbaar zijn rond de 0 zichtbaar maken
        {
            for(int8_t j = -1; j<2; j++)
            {
                if(r+i >= size || r+i < 0 || c+j >= size || c+j < 0) //vakjes buiten het veld overslaan
                {
                    continue;
                }
                if (j == 0 && i == 0) //eigen vakje overslaan om infinte loop te voorkomen
                {
                    continue;
                }
                if(array[r+i][c+j] <20 && array[r+i][c+j] > 9) //checken of vakje nog niet zichtbaar is
                {
                    reveal(array, size, r+i, c+j, move); //vakje zichtbaar maken en checken of het een 0 is
                }
            }
        }
    }
}

void firstmove(uint8_t array[15][15], uint8_t size, uint8_t dif, uint8_t* totmoves)
{
    uint8_t r,c, bommen, checkinput, ch;
    do //input krijgen van user met controle
    {
        printf("kies een begin coordinaat (r c)");
        checkinput = scanf("%hhu %hhu", &r, &c);
        while (checkinput != 2)
        {
            printf("ongeldige input\n");
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("kies een begin coordinaat (r c)"); //vraagt rij en kolom en checkt voor wisselen
            checkinput = scanf("%hhu %hhu", &r, &c);
        }
    } while (r < 0 || r >= size || c < 0 || c >= size );
    do //veld blijven genereren tot geselecteerde vakje een 0 is
    {
        innit(array, size);
        bommen = generate(array, size, dif);
        *totmoves = (size*size)-bommen;
    } while (array[r][c] != 10 );
    reveal(array, size, r, c, totmoves);
    
}

void innit(uint8_t array[15][15], uint8_t size)
{
    char correct;
    for(uint8_t i = 0; i<size; i++) //elk vakje in de array een waarde geven
    {
        for(uint8_t j = 0; j< size; j++)
        {
            array[i][j] = 10;
        }
    }
    gamestate = REVEAL; //spel starten
}