#include <stdio.h>
#include <stdlib.h>
#include "genfield.c"
#include "gamelogic.c"
#include <conio.h>

void innit(uint8_t array[15][15]);
void firstmove(uint8_t array[15][15], uint8_t size, uint8_t dif);




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
    while(running)
    {
        uint8_t size, dif, r, c, swapped, result;
        char correct, restart;
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
            
            result = editsquare(array, size);
            if (result == 9)
            {
                gamestate = LOST;
            }

        if (gamestate == LOST)
        {
            system("cls");
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
    }
    
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

