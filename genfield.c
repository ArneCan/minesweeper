#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

uint8_t GetSize(); //vraagt grootte aan user met verschillende opties
uint8_t GetDif(); //zelfde nut als GetSize maar dan voor moeilijkheid
void bombs(uint8_t*array, uint8_t amount, uint8_t dimention);//genereert de bommen in het veld en checkt dat er geen 2 bommen op hetzelfde vakje liggen
uint8_t checkdouble(uint8_t* array, uint8_t amount); // returned index van de eerst gevonden dubbele bom
uint8_t generate(uint8_t array[15][15], uint8_t size, uint8_t dif); //telt het aantal bommen rondom een vakje
uint8_t checkbombs(uint8_t array[][15], uint8_t size, uint8_t RowIndex, uint8_t ColIndex); //genereert elk vakje op het veld en returned het aantal bommen op het veld

uint8_t GetSize()
{
    uint8_t sizes[] = {5,8,15};
    char options[3][5][7] = {{"SMALL", "small", "Small", "s", "S"}, //alle gedefineerde opties
                        {"MEDIUM", "Medium", "medium", "M", "m"},
                        {"LARGE", "Large", "large", "L", "l"}};
    int8_t found = -1;
    char selection[7];
    do                                                      //blijft input vragen tot juiste input
    {
        printf("select size, SMALL, MEDIUM, LARGE: ");
        scanf("%7s", selection);
        for(uint8_t i = 0; i<3; i++) //checkt of input een van de opties is
        {
            for(uint8_t j = 0; j<5; j++)
            {
                if(strcmp(selection, options[i][j]) ==0)
                {
                    found = i; //found wordt gelijkgesteld aan moeilijkheid (1 = easy, 2 = medium, 3 = hard)
                    break;
                }
            }
            if (found != -1) //loop stoppen wanneer optie gevonden is
            {
                break;
            }
        }
    } while (found == -1);
    return sizes[found];    
}
uint8_t GetDif()
{
    char options[3][5][7] = {{"EASY", "Easy", "easy", "e", "E"}, //alle gedefineerde opties
                        {"MEDIUM", "Medium", "medium", "m", "M"},
                        {"HARD", "Hard", "hard", "h", "H"}};
    int8_t found = -1;
    char selection[7];
    do                                                      //blijft input vragen tot juiste input
    {
        printf("select difficulty, EASY, MEDIUM, HARD: ");
        scanf("%7s", selection);
        for(uint8_t i = 0; i<3; i++) //checkt of input een van de opties is
        {
            for(uint8_t j = 0; j<5; j++)
            {
                if(strcmp(selection, options[i][j]) ==0)
                {
                    found = i; //found wordt gelijkgesteld aan moeilijkheid (1 = easy, 2 = medium, 3 = hard)
                    break;
                }
            }
        if (found != -1) //loop stoppen wanneer optie gevonden is
        {
            break; 
        }
        }
    } while (found == -1);
    return found;
}
void bombs(uint8_t*array, uint8_t amount, uint8_t dimention) {
    uint8_t *start = array;
    uint8_t dupindex;
    for(uint8_t i = 0; i< amount; i++)  //genereert bommen op random locatie
    {
        *array = rand() % (dimention*dimention);
        array +=1;
    }
    dupindex = checkdouble(start,amount); //checkt welke bom in de array er 2 keer is en returned de index van de eerste dubbel gevonden bom
    while(dupindex) //nieuwe bom genereren waar een dubbele was
    {
        array = start;
        *(array+dupindex-1) = rand() % (dimention*dimention);
        dupindex = checkdouble(start,amount); //checkt of er nog dubbele bommen zijn
    }

}
uint8_t checkdouble(uint8_t *array, uint8_t amount){
    for(uint8_t i = 0; i<amount; i++ ) //neemt eerste bom en vergelijkt met alle andere, daarne 2e bom enz...
    {
        for(uint8_t j = i+1; j <amount; j++)
        {
            if(*(array+i) == *(array+j))
            {
                return i+1; //index returnen wanneer dubbele bom gevonden
            }
        }
    }
    return 0; //0 wanneer geen bom
}
uint8_t checkbombs(uint8_t array[][15], uint8_t size, uint8_t RowIndex, uint8_t ColIndex)
{
    uint8_t count = 0; //wordt geincrement bij elk vakje met een bom
    if(array[RowIndex][ColIndex] !=9 && array[RowIndex][ColIndex] !=19) //checkt of vakje een bom is
    {
        for (int8_t row = -1; row<=1; row++)
        {
            for(int8_t col = -1; col<=1; col++)
            {
                if(row == 0 && col == 0) //eigen vakjes overslaan
                {
                    continue;
                }
                if(row + RowIndex >= 0 && row+RowIndex<size && col+ColIndex>= 0 && col+ColIndex< size) //checken of vakje binnen veld ligt
                {
                    if(array[RowIndex+row][ColIndex+col] == 9 || array[RowIndex+row][ColIndex+col] == 19) //checkt voor een bom
                    {
                        count+=1;
                    }
                }
            }
        }
        return count+10; //count = aantal bommen (0-8 + 10 ==> 10-19 = verstopt)
    }
    else
    {
        return 19; //bom ontzichtbaar maken
    }
        
}
uint8_t generate(uint8_t array[15][15], uint8_t size, uint8_t selecdif)
{
    uint8_t amount, dif, row, column;
    int8_t dificulty[] = {-1, 0, 1}; 
    uint8_t bomb[61];
    dif = dificulty[selecdif];
    amount = ((size*size)/4) + (dif*size/3); //hoeveelheid bommen gebaseerd op moeilijkheid en grootte van veld
    bombs(bomb, amount, size); //genereert bommen en aantal op basis van groote en moeilijkheid van spel
    for(uint8_t i = 0; i<amount; i++) //plaatst bommen op juiste plaats in het veld
    {
        row = bomb[i]/size;
        column = bomb[i]%size;
        array[row][column] = 9;
    }
    for(uint8_t i = 0; i<size; i++) //rest van het veld invullen
    {
        for(uint8_t j = 0; j<size; j++)
        {
            array[i][j] = checkbombs(array, size, i, j); //juiste getal aan vakje linken
        }
    }
    return amount;
}