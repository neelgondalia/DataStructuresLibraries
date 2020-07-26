/**
 * @file heap.h
 * @author Michael Ellis/ Neel Gondalia
 * @date July 2017
 * @brief File containing the function definitions of a heap
 */

#ifndef _HEAP_API_
#define _HEAP_API_

#define MIN_HEAP 0
#define MAX_HEAP 1
#define HEAP_TYPE unsigned char

typedef struct Node
{
   void * data; ///< contains generic data type
   struct Node *left; ///< points to the left child of the node
   struct Node *right; ///< points to the right child of the node
   struct Node *parent; ///< points to the parent of the node
}Node;

typedef struct Heap
{
    Node **heapNodes; ///< contains all of the heap nodes
    HEAP_TYPE type; ///< flag that keeps track of what type of heap it is (min or max)
    size_t size;
    int count; ///< integer that keeps track of the length of the heap
    void (*destroyDataFP)(void *data); ///< function pointer to a function that deletes the data in a node in the heap
    void (*printNodeFP)(void *toBePrinted); ///< function pointer to a function that prints out the data in a node in the heap
    int (*compareFP)(const void *first, const void *second); ///< function pointer to a comparison function for the purpose of inserting and deleting elements depending on heap type
}Heap;

/** Function to heapify the heap from bottom to top
 *@pre Heap must exist and have data allocated to it
 *@param heap Pointer to a heap
**/
void heapifyUp (Heap *heap);

/** Function to heapify the heap from top to bottom
 *@pre Heap must exist and have data allocated to it
 *@param heap Pointer to a heap
**/
void heapifyDown (Heap *heap);

/** Function to swap two nodes of the heap
 *@pre Node a and Node b must exist
 *@param a Node to be swapped with b
 *@param b Node to be swapped with a
**/
void swap (Node *a, Node *b);

/**Function to allocate memory to the heap and point the heap to the appropriate functions. Allocates memory to the heap based on the size given.
 *@return pointer to the heap
 *@param initialSize initial size of the heap
 *@param htype flag to choose whether to start the heap as a min heap or max heap. Takes in values MIN_HEAP and MAX_HEAP
 *@param compareFP function pointer to a function that compares two pieces of data.
 *@param destroyDataFP function pointer to a function to delete a single piece of data from the heap
 *@param printNodeFP function pointer to a function that prints out a data element of the heap
 *@return pointer to the heap
 **/
Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second));

/**Function for creating a node for a heap.
 *@pre Node must be cast to void pointer before being added.
 *@post Node is valid and able to be added to a heap
 *@param data is a generic pointer to any data type that is to be stored in the heap.
 *@return returns a node for a heap
 **/
Node *createHeapNode(void *data);

/**Inserts a Node into the heap. Uses createHeapNode to place the data in a Node structure, and then puts the newly
 *created Node in the heap by adding at the bottom and comparing it to each parent node until it fits the Heap structure.
 *If the heap is a min heap, if the Node is lesser than the parent, it is swapped. The opposite is true for a max heap.
 *@pre Heap must exist and have data allocated to it
 *@param heap Pointer to a heap
 *@param data Pointer to generic data that is to be inserted into the heap
**/
void insertHeapNode(Heap *heap, void *data);

/**Function to remove the maximum or minimum Node of the heap (depending on min heap or max heap).
 *Once the Node has been deleted, the Node at the deepest point in the Heap is placed in the min/max position.
 *Finally, the heap is heapified to maintain heap property.
 *@pre Heap must exist and have memory allocated to it
 *@param heap Pointer to a heap.
 **/
void deleteMinOrMax(Heap *heap);

/**Function to rearrange a heap to maintain heap property. Starting at the min/max, each Node is compared with its
 *two children to determine the smallest/largest of the three. If the parent is smaller/larger than the child,
 *it is swapped. Heapify is then recursively called on the child in order to continue heapifying until it reaches the bottom of the heap.
 *@param heap Pointer to a heap to be heapified
 **/
void *getMinOrMax(Heap *heap);

/**Function to switch the type of heap from min-to-max or max-to-min. This changes the htype flag from MIN_HEAP
 *to MAX_HEAP and vice versa. Once the flag has been changed, heapify is called on the heap to rearrange it to 
 *fit the new heap property.
 *@param heap Pointer to a heap to switch from min-to-max or max-to-min.
 **/
void changeHeapType(Heap *heap);

/**Function delete a heap. This function calls deleteMinOrMax the same amount of times as the size of the
 *heap, which heapifies after each deletion. Finally, it frees the Heap structure.
 *@param heap Pointer of a heap to be deleted.
 **/
void deleteHeap(Heap *heap);

#endif
