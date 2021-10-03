/*
*   CircularQueue.c
*   A program that demonstrates how circular queue works using dynamic storage
*   Deme Sai Kiran 2021
*/

#include<stdio.h>
#include<stdlib.h>

struct queue
{
    int front;
    int rear;
    int size;
    int * data;
};
typedef struct queue CQUEUE;

/*
*   Function: createcQueue
*   ---------------------
*   This function demonstrates us how the queue with given size creates and 
*   returns the queue to the called function
*
*   size: It is the size of the queue that is first started with
*/
CQUEUE * createCQueue(int size)
{
    CQUEUE *qu = malloc(sizeof(CQUEUE));
    qu -> front  =  -1;
    qu -> rear   =  -1;
    qu -> size   =  size;
    qu -> data   =  malloc(sizeof(int) * size);
    return qu;
}


/*
*   Function: isQEmpty
*   ------------------
*   isQEmpty function demonstrates us either the queue is empty or not and
*   returns 1 if the queue is empty where rear becomes -1 else returns 0
*   
*   qu: It is the pointer to the type CQUEUE
*/
int isQEmpty(CQUEUE * qu)
{
    if(qu -> rear == -1)
        return 1;
    return 0;
}

/*
*   Funciton: isQFull
*   -----------------
*   isQFull demonstrates us the fullness of Queue where there will be two cases
*   to become Qfull, where the first condition is when the front points to 0
*   and rear points to size - 1 element, second one is front overlaps by one
*   to the rear.
*
*/
int isQFull(CQUEUE * qu)
{
    if(((qu -> front == 0) && (qu -> rear  == (qu -> size) -1)) ||
        ((qu -> front) == (qu -> rear) +1))
    {
        return 1;
    }
    return 0;
}

/*
*   Function: getFront
*   ------------------
*   getFront returns the element at the front, element will not be removed
*   front the queue.
*
*/
int getFront(CQUEUE * qu)
{
    return qu -> data[qu -> front];
}

/* 
*   Function: enqueue
*   -----------------
*   Enqueue function demonstrates us How the elements gets inserted into the 
*   Queue and also demonstrates us how the storage is being managed dynamically
*   
*   ele: element that will enqueue into the queue
*/
void enqueue(CQUEUE *qu, int ele)
{
    if(isQEmpty(qu))
    {
        qu -> front    =  0;
        qu -> rear     =  0;
        qu -> data[0]  =  ele;
        return;
    }
    
    if(isQFull(qu))
    {
        printf("QF QSD ");
        int *d      =  qu -> data;
        int size    =  qu -> size;
        qu -> data  =  malloc(sizeof(int) * 2 * size);
        qu -> size  =  size * 2;
        
        for(int i = 0; i < size; i++)
        {
            qu -> data[i] = d[(qu -> front + i) % size];
        }
        
        qu -> front             =  0;
        qu -> rear              =  size;
        qu -> data[qu -> rear]  =  ele;
        free(d);
        return;
        
    }
        qu -> rear              =  (qu -> rear + 1) % (qu -> size);
        qu -> data[qu -> rear]  =  ele;
        return;
    
}

/*
*   Function: deQueue
*   -----------------
*   Dequeue function demonstrates how the elements gets removed from the 
*   Queue in FIFO Manner.
*
*/
int dequeue(CQUEUE * qu)
{
    int ele  =  getFront(qu);
    
    if( qu -> front == qu -> rear)
    {
        qu -> front  =  -1;
        qu -> rear   =  -1;
        return ele;
    }
    
    qu -> front = (qu -> front + 1) % (qu -> size);
    return ele;
}

int main()
{
    CQUEUE * cqu = createCQueue(4);
    
    int choice;
    
    scanf("%d", &choice);
    
    while(choice != -1)
    {
        int ele;
        switch(choice)
        {
            case 1:
            {
                scanf("%d", &ele);
                enqueue(cqu, ele);
                break;
            }
            case 2:
            {
                if(isQEmpty(cqu))
                {
                    printf("QE ");
                    break;
                }
                ele = dequeue(cqu);
                printf("%d ", ele);
                break;
            }
            case 3:
            {
                if(isQEmpty(cqu))
                {
                    printf("QE ");
                    break;
                }
                ele = getFront(cqu);
                printf("%d ", ele);
                break;
            }
            default:
                break;
        }
        
        scanf("%d", &choice);
    }
    
    return 0;
}
