#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

void bombs(uint8_t*array, uint8_t amount, uint8_t dimention);
uint8_t checkdouble(uint8_t* array, uint8_t amount); 
uint8_t checkbombs(uint8_t array[][15], uint8_t size, uint8_t RowIndex, uint8_t ColIndex); 

/*
*   vraagt speler om grootte van het spel te kiezen
*   @returns de lengte van 1 zijde van het speelveld
*
*               5 -> 5x5 veld (small)
*
*               8 -> 8x8 veld (medium)
*
*               15 -> 15x15 veld (large)
*/
uint8_t GetSize()
{
    uint8_t sizes[] = {5,8,15};
    //alle gedefineerde opties
    char options[3][5][7] = {{"SMALL", "small", "Small", "s", "S"}, 
                        {"MEDIUM", "Medium", "medium", "M", "m"},
                        {"LARGE", "Large", "large", "L", "l"}};
    int8_t found = -1;
    char selection[7];
    //input controle
    do                                                      
    {
        printf("select size, SMALL, MEDIUM, LARGE: ");
        scanf("%7s", selection);
        //checkt of input een van de opties is
        for(uint8_t i = 0; i<3; i++) 
        {
            for(uint8_t j = 0; j<5; j++)
            {
                if(strcmp(selection, options[i][j]) ==0)
                {
                    //juiste grootte opslaan
                    found = i; 
                    break;
                }
            }
            //loop stoppen wanneer optie gevonden is
            if (found != -1) 
            {
                break;
            }
        }
    } while (found == -1);
    return sizes[found];    
}

/*
*   vraagt speler om moeilijkheid van het spel te kiezen
*   @returns getal van 0-2 dat later gebruikt wordt om aantal bommen te bepalen 
*/
uint8_t GetDif()
{
    //alle gedefineerde opties
    char options[3][5][7] = {{"EASY", "Easy", "easy", "e", "E"}, 
                        {"MEDIUM", "Medium", "medium", "m", "M"},
                        {"HARD", "Hard", "hard", "h", "H"}};
    int8_t found = -1;
    char selection[7];
    //input vragen met controle
    do                                                      
    {
        printf("select difficulty, EASY, MEDIUM, HARD: ");
        scanf("%7s", selection);
        //checkt of input een van de opties is
        for(uint8_t i = 0; i<3; i++) 
        {
            for(uint8_t j = 0; j<5; j++)
            {
                if(strcmp(selection, options[i][j]) ==0)
                {
                    //moilijkheid opslaan
                    found = i; 
                    break;
                }
            }
            //loop stoppen wanneer optie gevonden is
            if (found != -1) 
            {
                break; 
            }
        }
    } while (found == -1);
    return found;
}

/*
*   helperfunctie van generate
*
*   plaatst bommen in het veld
*
*   controlleert dat er geen 2 bommen op dezelfde plaats staan
*
*   plaatst de nummer van vakje waar bom moet komen in een array
*   @param *array pointer naar array die bomlocaties bevat. De waarde stelt de lineare index in het speelveld voor
*   @param amount het aantal bommen dat in het speelveld geplaatst worden
*   @param dimention grootte van het speelveld
*/
void bombs(uint8_t*array, uint8_t amount, uint8_t dimention) {
    uint8_t *start = array;
    uint8_t dupindex;

    //bommen genereren op random locatie
    for(uint8_t i = 0; i< amount; i++)  
    {
        *array = rand() % (dimention*dimention);
        array +=1;
    }

    //controleren dat er geen bommen met dezelfde locatie zijn
    dupindex = checkdouble(start,amount);
    while(dupindex)
    {
        array = start;
        *(array+dupindex-1) = rand() % (dimention*dimention);
        dupindex = checkdouble(start,amount);
    }

}

/*
*   helperfunctie van bombs
*
*   controlleert of bommen op dezelfde locatie liggen
*   @param *array pointer die de start van de bom array bevat
*   @param amount het aantal bommen in het veld
*   @returns de index van de 1ste dubbele bom
*   
*   0 wanneer er geen dubbele bommen zijn 
*/
uint8_t checkdouble(uint8_t *array, uint8_t amount){
    //over bommen loopen
    for(uint8_t i = 0; i<amount; i++ ) 
    {
        for(uint8_t j = i+1; j <amount; j++)
        {
            if(*(array+i) == *(array+j))
            {
                //index returnen wanneer dubbele bom gevonden
                return i+1; 
            }
        }
    }
    //geen dubbele bommen
    return 0;
}

/*
*   helperfunctie van generate
*
*   telt het aantal bommen rondom een vakje
*
*   @param array het speelveld
*   @param size grootte van het veld
*   @param RowIndex rij waarop het vakje staat
*   @param ColIndex kolom waarop het vakje staat
*   @returns het aantal bommen rondom het vakje +10 of 19 als het een bom is (vakjes vanaf 10 tot en met 19 zijn niet onthult)
*/
uint8_t checkbombs(uint8_t array[][15], uint8_t size, uint8_t RowIndex, uint8_t ColIndex)
{
    uint8_t count = 0; 
    //controlleren dat vakje geen bom is
    if(array[RowIndex][ColIndex] !=9 && array[RowIndex][ColIndex] !=19) 
    {
        for (int8_t row = -1; row<=1; row++)
        {
            for(int8_t col = -1; col<=1; col++)
            {
                //eigen vakjes overslaan
                if(row == 0 && col == 0) 
                {
                    continue;
                }
                //controlleren of vakje binnen het veld ligt
                if(row + RowIndex >= 0 && row+RowIndex<size && col+ColIndex>= 0 && col+ColIndex< size) 
                {
                    //controlleert of vakje een bom is
                    if(array[RowIndex+row][ColIndex+col] == 9 || array[RowIndex+row][ColIndex+col] == 19) 
                    {
                        count+=1;
                    }
                }
            }
        }
        //aantal bommen returnen +10 om te verstoppen
        return count+10; 
    }
    else
    {
        //bom ontzichtbaar maken
        return 19; 
    }
        
}

/*
*   genereert het speelveld
*   @param array het ongegenereerde speelveld
*   @param size grootte van het veld
*   @param selecdif geselecteerde moeilijkheid
*   @returns het aantal bommen in het veld
*/
uint8_t generate(uint8_t array[15][15], uint8_t size, uint8_t selecdif)
{
    uint8_t amount, row, column;
    int8_t dif, dificulty[] = {-1, 0, 1}; 
    uint8_t bomb[61];
    
    //aantal bommen bepalen en de bommen genereren
    dif = dificulty[selecdif];
    amount = ((size*size)/4) + (dif*size/3); 
    bombs(bomb, amount, size);

    //bommen in het veld plaatsen
    for(uint8_t i = 0; i<amount; i++) 
    {
        row = bomb[i]/size;
        column = bomb[i]%size;
        array[row][column] = 9;
    }
    //andere vakjes invullen
    for(uint8_t i = 0; i<size; i++)
    {
        for(uint8_t j = 0; j<size; j++)
        {
            array[i][j] = checkbombs(array, size, i, j);
        }
    }
    return amount;
}