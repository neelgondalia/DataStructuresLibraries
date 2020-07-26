#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "LinkedListAPI.h"

void printData (void *tobePrinted);
void deleteData (void *tobeDeleted);
int compare (const void *first, const void *second);

int main()
{
    List *test;
    int initEntries[5] = {10,20,30,40,25};
	void *entry;
	
    
    printf("Test 1: initialize a list\n");
    test = initializeList (&printData, &deleteData, &compare);
    if (test-> head == NULL && test == NULL && test->tail == NULL)
    {
        printf ("list struct is null: Success\n");
		printf ("list head struct is null: Success\n");
		printf ("list tail is null: Success\n");
    }
    printf("\ninitializing list: successful!\n\n");

	
	printf("Test 2: Add Node %d to front\n\n", initEntries[1]);
	entry = &initEntries[1];
	insertFront(test, entry);
	
	printf("Test 3: Add Node %d to front\n\n", initEntries[0]);
	entry = &initEntries[0];
	insertFront(test, entry);
	
	printf("Test 4: Add Node %d to back\n\n", initEntries[2]);
	entry = &initEntries[2];
	insertBack(test, entry);
	
	printf("expected output of list so far: 10 20 30\n");
	printf("print forward: ");
	printForward (test);
	printf("\nprint backwards: ");
	printBackwards (test);
	
	printf("\n\nTest 5: Add Node %d to sorted list\n\n", initEntries[4]);
	entry = &initEntries[4];
	insertSorted(test, entry);
	
	printf("expected output of list so far: 10 20 25 30\n");
	printf("print forward: ");
	printForward (test);
	printf("\nprint backwards: ");
	printBackwards (test);
	
	
	printf("\n\nTest 6: Getting node from front\n");
	printf("front node: %d\n", *((int*)getFromFront(test)));
	printf("Successful!\n\n");

	printf("Test 7: getting node from back\n");
	printf("back node: %d\n", *((int*)getFromBack(test)));
	printf("successful!\n\n");

	entry = &initEntries[2];
	printf("Test 8: removing node %d\n", initEntries[2]);
	deleteDataFromList(test, entry);
	
	printf("\nexpected output of list so far: 10 20 25\n");
	printf("obtained output: ");
	printForward (test);
	printf("\nTesting Done!\n");
        
    return 0;
    
}

void printData (void *tobePrinted)
{
    printf ("%d ", *(int *) tobePrinted);
}

//no memory is allocated in my unit test therefore no freeing of memory required
void deleteData (void *tobeDeleted)
{
    return;
}

int compare (const void *first, const void *second)
{
    if (*((int*)first) - *((int*)second) < 0)
    {
        return -1;
    }
    else if (*((int*)first) - *((int*)second) > 0)
    {
        return 1;
    }
    return 0;
}
