/**
 * @file shortest_u_v_path.c
 * @author Deme Sai Kiran (21MCMT19)
 * @brief Finding the shortest path b/w two given nodes in an unweighted graph 
 *        using forward star representation
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

/**
 * Functions:
 * 
 * > Creating and using the data structure = Forward Star
 * > BFS traversal which returns the shortest distance if exits else prints INVALID
 * > A test function which takes input [vertices, numbre of edges, sequence of edges
 *                                      followed by source and destination vertices from stdin]
 */



/**
 * @brief Forward star representation of a graph
 * 
 * > V [ Number of vertices in the graph ]
 * > E [ Number of edges in the graph ]
 * > info_pointer array [ Stores the index of edges of each node ]
 * > neighbours array [ Stores the neighbours of the nodes of info_pointer ]
 */
struct Forward_Star
{
    int V;
    int E;
    int *info_pointer;
    int * neighbour;
};
typedef struct Forward_Star FStar;

/**
 * @brief Prints the info and neighbour arrays of Forward star.
 * 
 * @param graph <Forward start object>
 */
void printFstar(FStar * graph)
{
    for(int i = 0; i <= graph -> V; i++)
        printf("%d ", graph -> info_pointer[i]);
    
    for(int i = 0; i < 2 * graph -> E; i++)
        printf("*%d", graph -> neighbour[i]);
}


// .......................... QUEUE UTILITY STARTS ..............................

/**
 * @brief queuenode structure definition
 * 
 */
typedef struct queuenode QNODE;
struct queuenode
{
    int vertex;
    int distance;
};

/**
 * @brief QUEUE that stores the queuenode objects
 * 
 */
typedef struct queue QUEUE;
struct queue
{
    int front;
    int rear;
    int size;
    QNODE ** data;
};


/**
 * @brief Create a Queue Node object
 * 
 * @param locate 
 * @param dist 
 * @return QNODE* 
 */
QNODE * createQueueNode(int vertex, int distance)
{
    QNODE * newnode      =  malloc(sizeof(QNODE));
    newnode -> vertex    =  vertex;
    newnode -> distance  =  distance;

    return newnode;
}

/**
 * @brief Create a Queue object
 * 
 * @param size 
 * @return QUEUE* 
 */
QUEUE * createQueue(int size)
{
    QUEUE * qu  =  malloc(sizeof(QUEUE));
    qu -> front =  -1;
    qu -> rear  =  -1;
    qu -> size  =  size;
    qu -> data  =  malloc(sizeof(QNODE *) * size);

    for(int i = 0; i < size; i++)  
        qu -> data[i] = createQueueNode(-1, 0);
    
    return qu;
}


/**
 * @brief Frees heap memory allocated @runtime
 * 
 * @param gb <Garbage queue object>
 */
void freeQueue(QUEUE * gb)
{
    int size = gb -> size;

    for(int i = 0; i < size; i++)
    {
        free(gb -> data[i]);
    }
}


/*
*   Function: isQEmpty
*   ------------------
*   isQEmpty function demonstrates us either the queue is empty or not and
*   returns 1 if the queue is empty where rear becomes -1 else returns 0
*   
*   qu: It is the pointer to the type 
*/
int isQEmpty(QUEUE * qu)
{
    return qu -> rear == -1 ? 1 : 0;
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
int isQFull(QUEUE * qu)
{
    if ( (( qu -> front == 0) && (qu -> rear == (qu -> size) - 1)) ||
            ((qu -> front) == (qu -> rear) + 1))
            return 1;
    return 0;
}

/*
*   Function: getFront
*   ------------------
*   getFront returns the element at the front, element will not be removed
*   front the queue.
*
*/
QNODE * getFront(QUEUE * qu)
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
void enqueue(QUEUE * qu, QNODE * ele)
{
    if(isQEmpty(qu))
    {
        qu -> front    =  0;
        qu -> rear     =  0;
        qu -> data[0]  =  ele;
        return;
    }

    qu -> rear               =  qu -> rear + 1;
    qu -> data[qu -> rear]   =  ele;

}

/*
*   Function: deQueue
*   -----------------
*   Dequeue function demonstrates how the elements gets removed from the 
*   Queue in FIFO Manner.
*
*/
QNODE * dequeue(QUEUE * qu)
{
    QNODE * ele = getFront(qu);
    
    if( qu -> front == qu -> rear )
    {
        qu -> front = -1;
        qu -> rear  = -1;
        return ele;
    }

    qu -> front = (qu -> front + 1);
    return ele;
}
// .......................... QUEUE UTILITY ENDS  ...............................


// .......................... BFS UTILITY FUNCTION ..............................

/**
 * @brief BFS traversal to find the shortes path between 
 *        the source node and destination node
 * 
 * @param graph <In termsof FSTAR representation>
 * @param source 
 * @param destination 
 * @return int <Shortes distance>
 */
int BFS(FStar * graph, int source, int destination)
{
    if(source == destination) return -1;

    int V = graph -> V;
    int E = graph -> E;


    int * visited = malloc(sizeof(int) * graph -> V + 1);

    visited[source] = 1;

    QUEUE * qu = createQueue(MAXSIZE);
    QNODE * tempnode = createQueueNode(source, 0);

    enqueue(qu, tempnode);
    int infoindex = source;


    while(!isQEmpty(qu))
    {
        QNODE * current = getFront(qu);

        int vertex = current -> vertex;
        infoindex = vertex;

        if(current->vertex == destination)
            return current -> distance;
        
        QNODE * deletenode = dequeue(qu);


        for (int i = graph -> info_pointer[infoindex]; i < graph -> info_pointer[infoindex+1]; i++)
        {
            QNODE * adjacent = createQueueNode(graph -> neighbour[i], current -> distance + 1);
            if(!visited[adjacent -> vertex])
            {
                visited[adjacent -> vertex] = 1;
                enqueue(qu, adjacent);
            }
        }
    }

    freeQueue(qu);
    free(visited);
    return -1;
}



/**
 * @brief Takes input from the user and creates graph in the form of 
 *          forward star and source, destination using stdin.
 * 
 * Also checks the input based on limits and negative inputs...
 * 
 * @param graph <Forward star reference>
 * @param source 
 * @param destination 
 */
int input_assert(FStar ** graph, int * source, int * destination)
{
    scanf("%d%d", &((*graph) -> V), &((*graph) -> E));
    if((*graph) -> E <= 0 || (*graph) -> V <= 0) return 0;

    int nEdges = (*graph) -> E;
    int nVertices = (*graph) -> V;

    (*graph) -> info_pointer = malloc(sizeof(int) * (nVertices + 1));
    (*graph) -> neighbour = malloc(sizeof(int) * 2 * nEdges);

    int infopointer = 0, flag = 0;
    int index = 0;
    for(int i = 0; i < 2 * nEdges; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if(a < 0 || b < 0) return 0;

        if(infopointer == a)
        {
            if(flag == 0)
            {
                flag = 1;
                (*graph) -> info_pointer[infopointer] = index;
            }
        }
        else
        {
            infopointer = a;
            flag = 1;
            (*graph) -> info_pointer[infopointer] = index;
        }

        (*graph) -> neighbour[index++] = b;
    }
    (*graph) -> info_pointer[++infopointer]= index;

    scanf("%d%d", source, destination);
    if (*source < 0 || *source > nVertices || *destination < 0 || *destination > nVertices) return 0;
    return 1;
}


int main(int argc, char const *argv[])
{

    int source, destination;
    FStar * graph = malloc(sizeof(FStar));
    int checkInput = input_assert(&graph, & source, & destination);
    if(!checkInput)
    {
        printf("INVALID INPUT");
        return 0;
    }
    // printFstar(graph);

    int shortDistance = BFS(graph, source, destination);

    shortDistance == -1 ? printf("INVALID INPUT") : printf("%d", shortDistance);

    free(graph -> info_pointer);
    free(graph -> neighbour);
    return 0;
}