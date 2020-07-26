/**
* @file HashTableAPI.c
* @author Neel Gondalia
* @date June 2017
* @brief File to test the functions of a hash table
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableAPI.h"

typedef struct players
{
    int number;
    char * name;
    char * position;
}players;

int hashFunction(size_t tableSize, int key);
void destroyData(void *data);
void printData(void *toBePrinted);

int main()
{

    HTable * ht = NULL;
    players *starters = NULL;
    

    printf ("\n**************************************************\n");
    printf (" Testing Hash table with basketball team starters\n");
    printf ("**************************************************\n\n");

    printf ("creating table of size 7...\n");
    ht =createTable(5,&hashFunction,&destroyData,&printData);
    printf ("successful.\n\n");

    printf ("adding starters: number 11, 23, 27, 30, 35...\n");

    starters = malloc (sizeof (players));
    starters->number = 11;
    starters->name = malloc(sizeof(char)*(strlen("Klay Thompson")+1));
    strcpy(starters->name, "Klay Thompson");
    starters->position = malloc(sizeof(char)*(strlen("SG")+1));
    strcpy(starters->position, "SG");
    insertData(ht, starters->number, (void *)starters);
    
    starters = malloc (sizeof (players));
    starters->number = 23;
    starters->name = malloc(sizeof(char)*(strlen("Draymond Green")+1));
    strcpy(starters->name, "Draymond Green");
    starters->position = malloc(sizeof(char)*(strlen("PF")+1));
    strcpy(starters->position, "PF");
    insertData(ht, starters->number, (void *)starters);

    starters = malloc (sizeof (players));
    starters->number = 27;
    starters->name = malloc(sizeof(char)*(strlen("Zaza Pachulia")+1));
    strcpy(starters->name, "Zaza Pachulia");
    starters->position = malloc(sizeof(char)*(strlen("C")+1));
    strcpy(starters->position, "C");
    insertData(ht, starters->number, (void *)starters);

    starters = malloc (sizeof (players));
    starters->number = 30;
    starters->name = malloc(sizeof(char)*(strlen("Stephen Curry")+1));
    strcpy(starters->name, "Stephen Curry");
    starters->position = malloc(sizeof(char)*(strlen("PG")+1));
    strcpy(starters->position, "PG");
    insertData(ht, starters->number, (void *)starters);

    starters = malloc (sizeof (players));
    starters->number = 35;
    starters->name = malloc(sizeof(char)*(strlen("Kevin Durant")+1));
    strcpy(starters->name, "Kevin Durant");
    starters->position = malloc(sizeof(char)*(strlen("SF")+1));
    strcpy(starters->position, "SF");
    insertData(ht, starters->number, (void *)starters);

    printf ("successful.\n\n");

    printf ("Looking up starters...\n");

    starters = (players *) lookupData(ht, 30);
    ht->printData((void*)starters);

    starters = (players *) lookupData(ht, 35);
    ht->printData((void*)starters);

    starters = (players *) lookupData(ht, 23);
    ht->printData((void*)starters);

    starters = (players *) lookupData(ht, 11);
    ht->printData((void*)starters);

    starters = (players *) lookupData(ht, 27);
    ht->printData((void*)starters);

    printf ("\nsuccessful.\n\n");

    printf ("Substitution: remove number 11 from starting lineup...\n");
    removeData (ht, 11);
    printf ("successful.\n\n");

    printf ("Substitution: adding number 9 to starting lineup...\n");

    starters = malloc (sizeof (players));
    starters->number = 9;
    starters->name = malloc(sizeof(char)*(strlen("Andre Igoudala")+1));
    strcpy(starters->name, "Andre Igoudala");
    starters->position = malloc(sizeof(char)*(strlen("SG")+1));
    strcpy(starters->position, "SG");
    insertData(ht, starters->number, (void *)starters);

    printf ("successful.\n\n");

    printf ("Looking up starters...\n");

    starters = (players *) lookupData(ht, 30);
    ht->printData((void*)starters);

    starters = (players *) lookupData(ht, 35);
    ht->printData((void*)starters);

    starters = (players *) lookupData(ht, 23);
    ht->printData((void*)starters);

    starters = (players *) lookupData(ht, 9);
    ht->printData((void*)starters);

    starters = (players *) lookupData(ht, 27);
    ht->printData((void*)starters);

    printf ("\nsuccessful.\n\n");

    printf ("GAME OVER. DESTROYING TABLE...");
    destroyTable (ht);
    printf ("\nsuccessful.\n\nTESTING DONE...\n\n");

    return 0;
}

//method of use for collision is random probing; table size needs to be a prime number for this to work
int hashFunction(size_t tableSize, int key)
{
    return (key+2) % tableSize;
}

void destroyData(void *data)
{
    free (((players *) data)->name);
    free (((players *) data)->position);
    free ((players *) data);
}

void printData(void *toBePrinted)
{
    players *info;
    
    info = (players *)toBePrinted;
    printf("\n***Number: %d\nName: %s\nPosition: %s\n", info->number, info->name, info->position);
}
