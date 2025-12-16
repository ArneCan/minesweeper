#include <stdint.h>
#include <stdio.h>

enum states {CONFIG, REVEAL, FLAG, WON, LOST};
typedef enum states state;
state gamestate = CONFIG;

void showfield(uint8_t array[15][15], uint8_t size); //speelveld voor user
void showarr(uint8_t array[15][15], uint8_t size); //for debugging
uint8_t editsquare(uint8_t array[15][15], uint8_t size); //laat veld zien of plaatst vlag
uint8_t checkwin(uint8_t array[15][15], uint8_t size);
uint8_t checkswap(state *gamestate, uint8_t input);

void showfield(uint8_t array[15][15], uint8_t size)
{
    for (uint8_t i = 0; i<=size; i++)
    {
        for(uint8_t j = 0; j<=size; j++)
        {
            if(i == 0 && j == 0)
            {
                printf("   ");
                continue;
            }
            else if (i == 0)
            {
                if (j<= 10)
                {
                    printf("%d  ", j-1);
                    continue;
                }
                else
                {
                    printf("%d ", j-1);
                    continue;
                }
            }
            else if (j == 0)
            {
                if (i <= 10)
                {
                    printf(" %d ", i-1);
                    continue;
                }
                else
                {
                    printf("%d ", i-1);
                    continue;
                }
                
            }
            else if (i >0 && j>0)
            {
                if (array[i-1][j-1] > 9 && array[i-1][j-1] < 20)
                {
                    printf("%c  ", 219);
                }
                else if (array[i-1][j-1] > 19)
                {
                    printf("F  ");
                }
                
                else
                {
                    printf("%u  ", array[i-1][j-1]);
                }
            }
            else
            {
                printf("error");
            }
        }
        printf("\n");
    }
}

void showarr(uint8_t array[15][15], uint8_t size)
{
    for(int i = 0; i<size;i++)
    {
        for(int j = 0; j<size; j++)
        {
            if(array[i][j]>9)
            {
                printf("%hhu ", array[i][j]);
            }
            else
            {
                printf("%hhu  ", array[i][j]);
            }
        }
        printf("\n");
    }
}

uint8_t editsquare(uint8_t array[15][15], uint8_t size)
{
    printf("gamestate: %d", gamestate);
    uint8_t swapped, r, c;
    do //check out of bounds en of vakje al vlag is of al gerevealed is
    {
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
        system("cls");
    } while (array[r][c] -10 < 0 || array[r][c] > 29 || r >= size || c >= size);

    if(gamestate == REVEAL)
    {
        printf("revealing");
        if (array[r][c] > 19)
        {
            printf("hier staat al een vlag");
            return 0;
        }
        else
        {
            array[r][c] -= 10;
            return array[r][c];
        }
    }

    else if (gamestate == FLAG)
    {
        printf("flagging");
        if (array[r][c] > 19)
        {
            array[r][c] -= 10;
            return 0;
        }
        else
        {
            array[r][c] += 10;
            return 0;
        }
    }

    else
    {
        printf("something went wrong");
    }
}

uint8_t checkwin(uint8_t array[15][15], uint8_t size)
{
    for(uint8_t i = 0; i< size; i++)
    {
        for(uint8_t j = 0; j<size; j++)
        {
            if (array[i][j] >9 && array[i][j] != 20 && array[i][j] <20)
            {
                return 0;
            }
        }
    }
    return 1;
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
        printf("gamestate %d", *gamestate);
        return 1;
    }
    return 0;
}
