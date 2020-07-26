/**
 * @file functions.c
 * @author Neel Gondalia
 * @date July 2017
 * @brief File containing all the functions required for priority queue
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h> 
#include "functions.h"

void heapifyUp (Heap *heap)
{
    int i = heap->count/2;

    while (i >= 1)
    {
        if (((2*i) + 1) <= heap->count)
        {
            Node *parent = heap->heapNodes[i];
            Node *left = heap->heapNodes[2*i];
            Node *right = heap->heapNodes[(2*i) + 1];
        
            if (heap->type == MIN_HEAP)
            {
                if (heap->compareFP (left->data, parent->data) < 0)
                {
                    swap (heap->heapNodes[2*i], heap->heapNodes[i]);
                }
                if (heap->compareFP (right->data, parent->data) < 0)
                {
                    swap (heap->heapNodes[(2*i) + 1], heap->heapNodes[i]);
                }
                if (heap->compareFP (right->data, left->data) < 0)
                {
                    swap (heap->heapNodes[(2*i) + 1], heap->heapNodes[2*i]);
                }
            }

            if (heap->type == MAX_HEAP)
            {
                if (heap->compareFP (left->data, parent->data) > 0)
                {
                    swap (heap->heapNodes[2*i], heap->heapNodes[i]);
                }
                if (heap->compareFP (right->data, parent->data) > 0)
                {
                    swap (heap->heapNodes[(2*i) + 1], heap->heapNodes[i]);
                }
                if (heap->compareFP (right->data, left->data) > 0)
                {
                    swap (heap->heapNodes[(2*i) + 1], heap->heapNodes[2*i]);
                }
            }
        }
        else
        {
            Node *parent = heap->heapNodes[i];
            Node *left = heap->heapNodes[2*i];
            
            if (heap->type == MIN_HEAP && heap->compareFP (left->data, parent->data) < 0)
            {
                swap (heap->heapNodes[2*i], heap->heapNodes[i]);
            }

            if (heap->type == MAX_HEAP && heap->compareFP (left->data, parent->data) > 0)
            {
                swap (heap->heapNodes[2*i], heap->heapNodes[i]);
            }
        }
        i--;
    }
}

void heapifyDown (Heap *heap)
{
    int i = 1;

    while (i <= (heap->count/2))
    {
        if (((2*i) + 1) <= heap->count)
        {
            Node *parent = heap->heapNodes[i];
            Node *left = heap->heapNodes[2*i];
            Node *right = heap->heapNodes[(2*i) + 1];
        
            if (heap->type == MIN_HEAP)
            {
                if (heap->compareFP (left->data, parent->data) < 0)
                {
                    swap (heap->heapNodes[2*i], heap->heapNodes[i]);
                }
                if (heap->compareFP (right->data, parent->data) < 0)
                {
                    swap (heap->heapNodes[(2*i) + 1], heap->heapNodes[i]);
                }
                if (heap->compareFP (right->data, left->data) < 0)
                {
                    swap (heap->heapNodes[(2*i) + 1], heap->heapNodes[2*i]);
                }
            }

            if (heap->type == MAX_HEAP)
            {
                if (heap->compareFP (left->data, parent->data) > 0)
                {
                    swap (heap->heapNodes[2*i], heap->heapNodes[i]);
                }
                if (heap->compareFP (right->data, parent->data) > 0)
                {
                    swap (heap->heapNodes[(2*i) + 1], heap->heapNodes[i]);
                }
                if (heap->compareFP (right->data, left->data) > 0)
                {
                    swap (heap->heapNodes[(2*i) + 1], heap->heapNodes[2*i]);
                }
            }
        }
        else
        {
            Node *parent = heap->heapNodes[i];
            Node *left = heap->heapNodes[2*i];
            
            if (heap->type == MIN_HEAP && heap->compareFP (left->data, parent->data) < 0)
            {
                swap (heap->heapNodes[2*i], heap->heapNodes[i]);
            }

            if (heap->type == MAX_HEAP && heap->compareFP (left->data, parent->data) > 0)
            {
                swap (heap->heapNodes[2*i], heap->heapNodes[i]);
            }
        }
        i++;
    }
}

void swap (Node *a, Node *b)
{
    Node *temp = a->left;
    a->left = b->left;
    b->left = temp;

    temp = a->right;
    a->right = b->right;
    b->right = temp;

    temp = a->parent;
    a->parent = b->parent;
    b->parent = temp;

    temp = a->data;
    a->data = b->data;
    b->data = temp;
}

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{
    Heap *h = malloc (sizeof(Heap)); 

    h->heapNodes = malloc (sizeof (Node) * initialSize);
    h->type = htype;
    h->count = 0;
    h->size = initialSize;
    h->printNodeFP = printNodeFP;
    h->destroyDataFP = destroyDataFP;
    h->compareFP = compareFP;

    return h;
}

Node *createHeapNode(void *data)
{
    Node *new = malloc (sizeof(Node));

    new->parent = NULL;
    new->left = NULL;
    new->right = NULL;
    new->data = data;

    return new;
}

void insertHeapNode(Heap *heap, void *data)
{
    if (heap == NULL || data == NULL)
    {
        return;
    }
    
    Node *new = createHeapNode (data);
    int index = heap->count + 1;
    int parent = index/2;
    int LorR = index % 2;    //0 means left and 1 means right

    heap->heapNodes[0] = NULL;

    if (index == 1)
    {
        heap->heapNodes[1] = new;
        heap->count++;
        return;
    }

    if (LorR == 0)
    {
        heap->heapNodes[index] = new;
        heap->heapNodes[index]->parent = heap->heapNodes[parent];
        heap->heapNodes[index]->left = NULL;
        heap->heapNodes[index]->right = NULL;
        heap->heapNodes[parent]->left = heap->heapNodes[index];
        heap->heapNodes[parent]->right = NULL;
        heap->count++;
    }
    else if (LorR == 1)
    {
        heap->heapNodes[index] = new;
        heap->heapNodes[index]->parent = heap->heapNodes[parent];
        heap->heapNodes[index]->left = NULL;
        heap->heapNodes[index]->right = NULL;
        heap->heapNodes[parent]->right = heap->heapNodes[index];
        heap->heapNodes[parent]->left = heap->heapNodes[index-1];
        heap->count++;
    }

    heapifyUp (heap);
    return;
}

void deleteMinOrMax(Heap *heap)
{
    if (heap == NULL || heap->count == 0)
    {
        return;
    }

    int index = heap->count;
    if (index == 1)
    {
        free (heap->heapNodes[1]);
        heap->count--;
        return;
    }
        
    swap (heap->heapNodes[1], heap->heapNodes[index]); //first node swapped with last
    heap->destroyDataFP (heap->heapNodes[index]->data);
    free (heap->heapNodes[index]);
    heap->count--;

    heapifyDown (heap);
    return;
}

void *getMinOrMax(Heap *heap)
{
    if (heap != NULL && heap->heapNodes[1] != NULL)
    {
        heapifyUp (heap);
        return heap->heapNodes[1]->data;
    }
    return NULL;
}

void changeHeapType(Heap *heap)
{
    if (heap == NULL)
    {
        return;
    }
    
    if (heap->type == MIN_HEAP)
    {
        heap->type = MAX_HEAP;
    }
    else if (heap->type == MAX_HEAP)
    {
        heap->type = MIN_HEAP;
    }

    heapifyDown (heap);
    return;
}

void deleteHeap(Heap *heap)
{
    int i = 1;
    
    if (heap == NULL)
    {
        return;
    }
    
    for (i=1; i<heap->count; i++)
    {
        deleteMinOrMax (heap);
    }
    free (heap);
    return;
}
