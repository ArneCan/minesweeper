#include <stdint.h>
#include <stdio.h>

enum states {CONFIG, REVEAL, FLAG, WON, LOST};
typedef enum states state;
state gamestate = CONFIG;

void showfield(uint8_t array[15][15], uint8_t size); //speelveld voor user
void showarr(uint8_t array[15][15], uint8_t size); //for debugging
uint8_t playeraction(uint8_t array[15][15], uint8_t size, uint8_t* move, char modus[7]); //laat veld zien of plaatst vlag
void getcords(uint8_t* s, uint8_t* r, uint8_t* c, char modus[7]);
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

uint8_t playeraction(uint8_t array[15][15], uint8_t size, uint8_t* move, char modus[7])
{
    uint8_t swapped, r, c;
    do //check out of bounds en of vakje al vlag is of al gerevealed is
    {
        showfield(array, size);
        getcords(&swapped, &r, &c, modus);
        system("cls");
    } while (array[r][c] -10 < 0 || array[r][c] > 29 || r >= size || c >= size);


    if(gamestate == REVEAL)
    {
        if (array[r][c] > 19)
        {
            printf("hier staat al een vlag");
            return 0;
        }
        else
        {
            array[r][c] -= 10;
            *move-=1;
            if (*move == 0)
            {
                gamestate = WON;
            }
            return array[r][c];
        }
    }

    else if (gamestate == FLAG)
    {
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
        return 0;
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

void getcords(uint8_t* s, uint8_t* r, uint8_t* c, char modus[7])
{
    printf("mode: %s\n vul rij en kolom in met spatie in (15 om te vlag te toggelen)", modus);
        scanf("%hhu", r);
        *s = checkswap(&gamestate, *r);
        if (*s)
        {
            return;
        }

        printf("vul colom in (15 om te vlag te toggelen)");
        scanf("%hhu", c);
        *s = checkswap(&gamestate, *c);
        if (*s)
        {
            return;
        }
}
