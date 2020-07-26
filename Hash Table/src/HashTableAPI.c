/**
 * @file HashTableAPI.c
 * @author Neel Gondalia
 * @date June 2017
 * @brief File containing the functions of a hash table
 */

#include <stdio.h>
#include <stdlib.h>
#include "HashTableAPI.h"

HTable *createTable(size_t size, int(*hashFunction)(size_t tableSize, int key), void(*destroyData)(void *data), void(*printData)(void *toBePrinted))
{
    HTable *hTable = malloc(sizeof(HTable));

    hTable->size = size;
    hTable->table = malloc(sizeof(Node) * size);
    hTable->destroyData = destroyData;
    hTable->hashFunction = hashFunction;
    hTable->printData = printData;

    return hTable;
}

Node *createNode(int key, void *data)
{
    Node *new = malloc(sizeof(Node));

    new->key = key;
    new->data = data;
    new->next = NULL;

    return new;
}

void destroyTable(HTable *hashTable)
{
    int i = 0;
    Node *new = NULL;
    Node *temp = NULL;

    for (i = 0; i < hashTable->size; i++)
    {
        new = hashTable->table[i];
        
        while (new != NULL)
        {
            temp = new;
            new = new->next;
            free(temp);
        }
    }
}

void insertData(HTable *hashTable, int key, void *data)
{
    Node *new = NULL;
    Node *temp = NULL;

    if (hashTable == NULL)
    {
        return;
    }

    else
    {
        int index = hashTable->hashFunction(hashTable->size, key);

        if (hashTable->table[index] == NULL)
        {
            new = createNode(key, data);
            hashTable->table[index] = new;
        }
        else
        {
            temp = hashTable->table[index];

            while (temp->next != NULL && temp->key != key)
            {
                temp = temp->next;
            }

            if (temp->key == key)
            {
                temp->data = data;
            }
            else
            {
                new = createNode(key, data);
                temp->next = new;
            }
        }
    }
}

void removeData(HTable *hashTable, int key)
{
    Node *new = NULL;

    if (hashTable == NULL)
    {
        return;
    }

    else
    {
        int index = hashTable->hashFunction(hashTable->size, key);

        if (hashTable->table[index] == NULL)
        {
            return;
        }

        else
        {
            new = hashTable->table[index];
            Node *prev = NULL;

            while (new != NULL)
            {
                if (new->key == key)
                {
                    if (prev == NULL)
                    {
                        prev = new;
                        new = new->next;
                        hashTable->destroyData(prev->data);
                        free(prev);
                    }

                    else
                    {
                        prev->next = new->next;
                        hashTable->destroyData(new->data);
                        free(new);
                    }

                    return;
                }

                prev = new;
                new = new->next;
            }
        }
    }
}

void *lookupData(HTable *hashTable, int key)
{
    Node *new = NULL;
    
    if (hashTable == NULL)
    {
        return NULL;
    }

    else
    {
        int index = hashTable->hashFunction(hashTable->size, key);

        if (hashTable->table[index] == NULL)
        {
            return NULL;
        }

        new = hashTable->table[index];

        while (new != NULL)
        {
            if (new->key == key)
            {
                return new->data;
            }

            new = new->next;
        }
    }
    return NULL;
}
