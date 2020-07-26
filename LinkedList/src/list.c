#include <stdio.h>
#include <stdlib.h>

#include "LinkedListAPI.h"

List *initializeList (void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second))
{
    List *new;
    
    new = malloc (sizeof (struct listHead));    

    new->head = NULL;
    new->printData = printFunction;
    new->deleteData = deleteFunction;
    new->compare = compareFunction; 
    
    return new;
}

Node *initializeNode (void *data)
{
    Node *new = malloc (sizeof (Node));
    
    new->data = data;
    new->next = NULL;
    new->previous = NULL;
    
    return new;
}

void insertFront (List *list, void *toBeAdded)
{
    Node *new;

    if (list == NULL)
    {
        return;
    }
    
    if (list->head == NULL && list->tail == NULL) 
    { 
        list->head = initializeNode (toBeAdded);
        list->tail = list->head;
        return;
    }
    
    else 
    {
        new = initializeNode (toBeAdded);
        new->next = list->head;
        list->head->previous = new;
        list->head = new;
    }
}

void insertBack (List *list, void *toBeAdded)
{
    Node *new;
    Node *temp;
    
    if (list == NULL)
    {
        return;
    }
    
    if (list->tail == NULL && list->head == NULL) 
    { 
        list->head = initializeNode (toBeAdded);
        list->tail = list->head;
        return;
    }
    
    temp = list->head;
    
    while (temp->next != NULL) 
    {
        temp = temp->next;
    }
        
    new = initializeNode (toBeAdded);
    list->tail = new;
    temp->next = new;
    new->previous = temp;
} 

void insertSorted (List *list, void *toBeAdded)
{   
    Node *temp;
    Node *add;

    if (list == NULL)
    {
        return;
    }

    if ((list->head == NULL) && (list->tail == NULL))
    {
        list->head = initializeNode(toBeAdded);;
        list->tail = list->head;
        return;
    }
    
    temp = list->head;
    add = initializeNode(toBeAdded);

    /*iteration to find where node goes*/
    while (temp != NULL)
    {
        if (list->compare (temp->data, toBeAdded) <  0)
        {
            if (temp == list->tail)
            {
                list->tail->next = add;
                add->previous = list->tail;
                list->tail = add;
                return;
            }
            temp = temp->next;
        }
        
        /*once place found*/
        else
        {
            if (temp == list->head)
            {
                add->next = list->head;
                list->head->previous = add;
                list->tail = add;
            }
        
            else
            {
                add->previous = temp->previous;
                add->next = temp;
                temp->previous->next = add;
                temp->previous = add;
                return;
            }
        }
    }
}

void *getFromFront (List *list)
{
    if ((list == NULL)||(list->head == NULL))
    {
        return NULL;
    }
    
    return (list->head->data);
}

void *getFromBack (List *list)
{   
    Node *prev;
    Node *curr;

    if ((list == NULL)||(list->head == NULL))
    {
        return NULL;
    }
    
    prev = list->head;
    curr = list->head->next;

    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
    }

    return prev->data;
}

int deleteDataFromList (List *list, void *toBeDeleted)
{
    Node *temp;

    if ((list == NULL)||(list->head == NULL)||(toBeDeleted == NULL))
    {
        return -1;
    }

    temp = list->head;
     
    while (temp != NULL)
    {
        if (temp->data == toBeDeleted)
        {
            if (temp == list->head)
            {
                list->head = temp->next;
                
                if (list->head != NULL)
                {
                    list->head->previous = NULL;
                }
            }
            
            else if (temp == list->tail)
            {
                if (temp->previous != NULL)
                {
                    list->tail->previous->next = NULL;
                }
            }
            
            else
            {
                temp->previous->next = temp->next;
                temp->next->previous = temp->previous;
            }
            
            list->deleteData (temp->data);
            free (temp);
            return EXIT_SUCCESS;
        }
        
        else
        {
            temp = temp->next;
        }   
    } 
    
    return -1;
}

void printForward (List *list)
{
    Node *temp;

    if (list == NULL)
    {
        return;
    }

    temp = list->head;

    while (temp != NULL) 
    {
        list->printData (temp->data);
        temp=temp->next;
    }
}

void printBackwards (List *list)
{
    Node *temp;

    if (list == NULL)
    {
        return;
    }

    temp = list->tail;

    while (temp != NULL) 
    {
        list->printData (temp->data);
        temp=temp->previous;
    }
}

void deleteList (List *list)
{   
    if (list == NULL)
    {
        return;
    }
    
    while (list->head != NULL)
    {
        Node *temp = list->head;
        list->head = list->head->next;
        
        temp->next = NULL;
        temp->previous = NULL;

        list->deleteData (temp->data);
        free (temp);
    }
    
    free (list);
}
  
