#include <stdint.h>
#include <stdio.h>

void showfield(uint8_t array[15][15], uint8_t size);
void showarr(uint8_t array[15][15], uint8_t size); //for debugging
uint8_t showsquare(uint8_t array[15][15]);
uint8_t flagsquare(uint8_t array[15][15]);

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
                if (array[i-1][j-1] > 9 && array[i-1][j-1] != 20)
                {
                    printf("%c  ", 219);
                }
                else if (array[i-1][j-1] == 20)
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

uint8_t editsquare(uint8_t array[15][15], uint8_t size, uint8_t state, uint8_t r, uint8_t c)
{
    printf("vul coördinaat in (rij colom)");
    scanf("%hhu %hhu", &r, &c);
    while (array[r][c] -10 < 0 || array[r][c] == 20)
    {
        printf("al zichtbaar \n");
        printf("vul coördinaat in (rij colom)");
        scanf("%hhu %hhu", &r, &c);
    }
    while (r <= size || c <= size)
    {
        printf("out of bounds \n");
        printf("vul coördinaat in (rij colom)");
        scanf("%hhu %hhu", &r, &c);
    }
    if(state == 0)
    {
        array[r][c] -= 10;
        return array[r][c];
    }
    else
    {
        array[r][c] = 20;
        return 0;
    }
}