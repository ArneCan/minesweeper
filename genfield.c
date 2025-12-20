#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

uint8_t GetSize();
uint8_t GetDif();
void bombs(int*array, int amount, int dimention);
uint8_t checkdouble(int *array, int amount);
uint8_t generate(uint8_t array[15][15], uint8_t size, uint8_t dif);
uint8_t checkbombs(uint8_t array[][15], uint8_t size, int RowIndex, int ColIndex);

uint8_t GetSize()
{
    int sizes[] = {5,8,15};
    char options[3][5][7] = {{"SMALL", "small", "Small", "s", "S"},
                        {"MEDIUM", "Medium", "medium", "M", "m"},
                        {"LARGE", "Large", "large", "L", "l"}};
    int8_t found = -1;
    char selection[7];
    do
    {
        printf("select size, SMALL, MEDIUM, LARGE: ");
        scanf("%7s", selection);
        for(uint8_t i = 0; i<3; i++)
        {
            for(int j = 0; j<5; j++)
            {
                if(strcmp(selection, options[i][j]) ==0)
                {
                    found = i;
                    break;
                }
            }
            if (found != -1)
            {
                break;
            }
        }
    } while (found == -1);
    return sizes[found];    
}
uint8_t GetDif()
{
    char options[3][3][7] = {{"EASY", "Easy", "easy"},
                        {"MEDIUM", "Medium", "medium"},
                        {"HARD", "Hard", "hard"}};
    int8_t found = -1;
    char selection[7];
    do
    {
        printf("select difficulty, EASY, MEDIUM, HARD: ");
        scanf("%7s", selection);
        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<3; j++)
            {
                if(strcmp(selection, options[i][j]) ==0)
                {
                    found = i;
                    break;
                }
            }
        if (found != -1)
        {
            break;
        }
        }
    } while (found == -1);
    return found;
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

uint8_t checkbombs(uint8_t array[][15], uint8_t size, int RowIndex, int ColIndex)
{
    uint8_t count = 0;
    if(array[RowIndex][ColIndex] !=9 && array[RowIndex][ColIndex] !=19)
    {
        for (int row = -1; row<=1; row++)
        {
            for(int col = -1; col<=1; col++)
            {
                if(row == 0 && col == 0)
                {
                    continue;
                }
                if(row + RowIndex >= 0 && row+RowIndex<size && col+ColIndex>= 0 && col+ColIndex< size)
                {
                    if(array[RowIndex+row][ColIndex+col] == 9 || array[RowIndex+row][ColIndex+col] == 19)
                    {
                        count+=1;
                    }
                }
            }
        }
        return count+10;
    }
    else
    {
        return 19;
    }
        
}

uint8_t generate(uint8_t array[15][15], uint8_t size, uint8_t selecdif)
{
    int amount, dif;
    int TSquares[8];
    int row, column;
    int dificulty[] = {-1, 0, 1}; 
    int bomb[61];
    dif = dificulty[selecdif];
    amount = ((size*size)/4) + (dif*size/3);
    bombs(bomb, amount, size); //genereert bommen en aantal op basis van groote en moeilijkheid van spel
    for(int i = 0; i<amount; i++) //assigns bombs to their respectiv spot in the field
    {
        row = bomb[i]/size;
        column = bomb[i]%size;
        array[row][column] = 9;
    }
    for(int i = 0; i<size; i++)
    {
        for(int j = 0; j<size; j++)
        {
            array[i][j] = checkbombs(array, size, i, j);
        }
    }
    return amount;
}