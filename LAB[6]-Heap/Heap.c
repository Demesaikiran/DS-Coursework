#include<stdio.h>
#include<stdlib.h>

/**
 * Creates the dynamic array of size parameter of type int
 * 
 * @param size
 *          The size of the dynamic array
 * @returns the created dynamic array reference
 */
int * createArray(int size)
{
    int * newArray = malloc(sizeof(int) * size);
    return newArray;
}

/**
 * Returns the left child index of current node
 * 
 * @param index
 *          Where the current node is located
 * @return left child index(Position)
 */
int LEFT(int index) { return 2 * index + 1;}

/**
 * Returns the right child index of current node
 * 
 * @param index
 *          Where the current node is located
 * @return right child index(position)
 */
int RIGHT(int index) { return 2 * index + 2;}

/**
 * Swaps the elements which gets reflected in caller function
 * 
 * @param a
 *          Reference of first object
 * @param b
 *          Reference of second object
 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Map-Heapify except for indexed node, Max-Heapify function arranges
 * node i and it's subtrees such that it satisfies the Heap property
 * 
 * @param heap
 *          Heap one dimensional array
 * @param heapsize
 *          Is the size of the heap(array)
 * @param index
 *          Current node index for which we are doing Max-Heap
 */
void MAXHeap(int * heap, int heapSize, int index)
{
    int Lindex = LEFT(index);
    int Rindex = RIGHT(index);
    int largeindex = index;
    int size = heapSize;

    if( (Lindex < size) && (heap[Lindex] > heap[largeindex]))
        largeindex = Lindex;
    if((Rindex < size) && (heap[Rindex] > heap[largeindex]))
        largeindex = Rindex;

    if(largeindex != index)
    {
        swap(& heap[index], & heap[largeindex]);
        MAXHeap(heap, size, largeindex);
    }
}

/**
 * The Max-Heapify alone can't adjust the whole heap to Maintain at a time
 * It maintians a particular node till the root node.
 * This need to be maintained for each node at each step. BuildHeap makes that
 * 
 * @param heap
 *          Heap one dimensional array
 * @param heapsize
 *          Is the size of the heap(array)
 */
void Build_MaxHeap(int * heap, int heapsize)
{
    int index = heapsize / 2 -1;
    for(int i = index; i >= 0  ; i--)
    {
        MAXHeap(heap, heapsize, i);
    }
} 

/**
 * After creating the Max-Heap, we swap the root with last node of heap
 * and remove it from the heap
 * Next we need to rebuild the heap by calling Max-Heap
 * This process need to be repeated till we remain with two nodes.
 * 
 * @param heap
 *          Heap one dimensional array
 * @param heapsize
 *          Is the size of the heap(array)
 */ 
void Heap_Sort(int * heap, int heapsize)
{
    int size = heapsize;
    for(int i = size - 1; i > 0; i--)
    {
        swap(&heap[0], &heap[i]);
        MAXHeap(heap, i, 0);
    }
}


int Extract_Max(int * heap, int *heapsize)
{
    Build_MaxHeap(heap, *heapsize);
    int element = heap[0];
    swap(&heap[0], &heap[*heapsize-1]);
    MAXHeap(heap, *heapsize, 0);
    *heapsize -= 1;

    return element;
}

int Heap_Maximum(int * heap)
{
    return heap[0];
}

void AdjustHeap(int * heap, int heapsize, int index)
{
    int parent = index / 2;

    while(parent != 0)
    {
        if(heap[index] > heap[parent])
        {
            swap(&(heap[index]), &(heap[parent]));
            index = parent;
            parent /= 2;
        }
    }
}
void Heap_Increase_Key(int * heap, int heapsize, int index, int value)
{
    heap[index] += value;

    AdjustHeap(heap, heapsize, index);

    MAXHeap(heap, heapsize, index);
}
/**
 * Prints the array of size given in parameters
 * 
 * @param arr
 *          It's the array reference
 * @param size
 *          size of the array
 */
void print(int *arr, int size)
{
    for(int i =0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}


int main()
{
    int n;

    scanf("%d", &n);
    if(n <= 0)
    {
        printf("INVALID INPUT");
        return 0;
    }

    int *arr = createArray(n);
    for(int i = 0; i < n; i++)
        scanf("%d", & arr[i]);

    Build_MaxHeap(arr, n);
    //Heap_Sort(arr, n);
    Heap_Increase_Key(arr, n, 5, 100);
    print(arr, n);

    //printf("%d", Extract_Max(arr, &n));
    free(arr);

}