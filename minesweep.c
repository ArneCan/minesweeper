#include <stdio.h>
#include <stdlib.h>
#include "genfield.c"


void innit(int* array);


int main()
{
    srand(time(NULL));
    int array[15][15];
    innit(&array[0][0]);
    generate(array);
    for(int i = 0; i<15; i++)
    {
        for(int j = 0; j<15; j++)
        {
            printf("%d  ", array[i][j]);
        }
        printf("\n");
    }
}

void innit(int* array)
{
    for(int i = 0; i<15*15; i++)
    {
        *array = 0;
        array++;
    }
}