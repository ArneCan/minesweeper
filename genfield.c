#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

int GetSize();
int GetDif();
void bombs(int*array, int amount, int dimention);
uint8_t checkdouble(int *array, int amount);
void generate(int* array);

int GetSize()
{
    char options[3][5][7] = {{"SMALL", "small", "Small", "s", "S"},
                        {"MEDIUM", "Medium", "medium", "M", "m"},
                        {"LARGE", "Large", "large", "L", "l"}};
    uint8_t found = 0;
    char selection[7];
    do
    {
        printf("select size, SMALL, MEDIUM, LARGE: ");
        scanf("%s", selection);
        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<5; j++)
            {
                if(strcmp(selection, options[i][j]) ==0)
                {
                    return i;
                    found = 1;
                    break;
                }
            }
        }
    } while (~found);
    
}
int GetDif()
{
    char options[3][3][7] = {{"EASY", "Easy", "easy"},
                        {"MEDIUM", "Medium", "medium"},
                        {"HARD", "Hard", "hard"}};
    uint8_t found = 0;
    char selection[7];
    do
    {
        printf("select difficulty, EASY, MEDIUM, HARD: ");
        scanf("%s", selection);
        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<5; j++)
            {
                if(strcmp(selection, options[i][j]) ==0)
                {
                    return i;
                    found = 1;
                    break;
                }
            }
        }
    } while (~found);
}

void bombs(int*array, int amount, int dimention)
{
    int *start = array;
    uint8_t dupindex;
    for(int i = 0; i< amount; i++)
    {
        *array = rand() % (dimention*dimention);
        array +=1;
    }
    dupindex = checkdouble(start,amount);
    while(dupindex)
    {
        array = start;
        *(array+dupindex-1) = rand() % (dimention*dimention);
        dupindex = checkdouble(start,amount);
    }

}

uint8_t checkdouble(int *array, int amount) // returns index of first element that has a double in the same array
{
    for(int i = 0; i<amount; i++ )
    {
        for(int j = i+1; j <amount; j++)
        {
            if(*(array+i) == *(array+j))
            {
                return i+1;
            }
        }
    }
    return 0;
}

void generate(int* array)
{
    int bombs[56];
    int size = GetSize();
    int dif = GetDif();

}