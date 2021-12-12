#include<stdio.h>
#include<stdlib.h>

#define ROW 12
#define COL 12
#define WALL '#'
#define PATH '.'
#define MAXSIZE 20

/**
 * Functions:
 * 
 * > Reading input from the file and making a matrix of order 12 X 12
 * > Checking the Source point in the column 1 and end point in the column 12
 * > BFS traversal calculates the shortest distance returns -1 if not exists
 * > Queue Data Structure
 * > Saving coordinates and checking validity
 * > 
 * 
 */

/**
 * BFS Traversal Utility Idea:
 * 
 * 0. Make a visited matrix and make all as 0.
 * 1. Starting from the source vertex... Push its neighbours and check VALIDITY 
 * 2. Make visited matrix 1 after VALIDITY checking.
 * 3. Iterate through the neighbours and make a distance varibale incremented by 1.
 * 4. If queue gets empty without return... Then return -1 that no path exists
 * 
 */

/**
 * Validity:
 * 
 * 0. Validity can be two ways one is it is not visited yet and another one is its coordinates 
 *    should lie in bounded matrix coordinates.
 */


/**
 * @brief Location structure node
 * 
 *      It stores the location point [x, y] coordinates that present in matrix
 */
struct location
{
    int x;
    int y;
};
typedef struct location LOC;

/**
 * @brief Create a Location object
 * 
 * @param x 
 * @param y 
 * @return LOC* 
 */
LOC * createLocation(int x, int y)
{
    LOC * newlocation = malloc(sizeof(LOC));
    newlocation -> x = x;
    newlocation -> y = y;
    return newlocation;
}


// .......................... MATRIX UTLITY STARTS ................................

/**
 * @brief Create a Matrix object
 * 
 * @param row 
 * @param col 
 * @return void* 
 */

void * createMatrix(int row, int col)
{
    void ** newmatrix = malloc(row * sizeof(void *));
    for(int i = 0 ; i < col; i++)
    {
        newmatrix[i] = malloc(col * sizeof(void));
    }

    return newmatrix;
}

/**
 * @brief Reads the matrix maze from the file and returns the maze matrix
 * 
 * @param filename 
 * @return char** 
 */
char ** ReadMatrixFromFile(char * filename)
{
    FILE * fp = fopen(filename, "r");

    if(!fp)
    {
        printf("ERROR IN OPENING FILE...");
        exit(1);
    }
    char ** matrix = createMatrix(ROW, COL);

    char * line = malloc(ROW * sizeof(char));
    int i = 0;

    while(fscanf(fp, "%[^\n] ", line) != EOF)
    {
        for(int pointer = 0; pointer < ROW; pointer++)
        {
            matrix[i][pointer] = line[pointer];
        }
        i++;
    }
    return matrix;
}

/**
 * @brief Finds the location in the matrix given with the dimensions provided to the function
 * 
 * @param matrix 
 * @param row 
 * @param col 
 * @param targetcol 
 * 
 *      target column is the parameter where the required PATH object is present
 * @param target 
 *      target is the PATH target object / character
 * @return LOC* 
 */
LOC * findLOC(char ** matrix, int row, int col, int targetcol, char target)
{
    LOC * locate = NULL;
    for(int i = 0; i < row; i++)
    {
        if(matrix[i][targetcol] == target)
        {
            locate = malloc(sizeof(LOC));
            locate -> x = i;
            locate -> y = targetcol;
            return locate;
        }
    }
    return locate;
}

// .......................... MATRIX UTLITY ENDS ................................


// .......................... QUEUE UTILITY STARTS ..............................

/**
 * @brief queuenode structure definition
 * 
 */
typedef struct queuenode QNODE;
struct queuenode
{
    LOC * coordinates;
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
QNODE * createQueueNode(LOC * locate, int dist)
{
    QNODE * qnode = malloc(sizeof(QNODE));
    qnode -> coordinates = malloc(sizeof(LOC));
    qnode -> coordinates = locate;
    qnode -> distance = dist;

    return qnode;
}

/**
 * @brief Create a Queue object
 * 
 * @param size 
 * @return QUEUE* 
 */
QUEUE * createQueue(int size)
{
    QUEUE *qu    = malloc(sizeof(QUEUE));
    qu -> front  =  -1;
    qu -> rear   =  -1;
    qu -> size   =  size;
    qu -> data   =  malloc(sizeof(QNODE *) * size);
    for(int i =0; i < size; i++)
    {
        qu -> data[i] = createQueueNode(NULL, 0);
    }
    return qu;
}

/**
 * @brief Frees the Queue entries
 * 
 * @param gb 
 * @param size 
 */
void freeQueueNode(QNODE ** gb, int size)
{
    for(int i =0; i < size; i++)
    {
        free(gb[i]);
    }
}

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
int isQFull(QUEUE * qu)
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
void enqueue(QUEUE *qu, QNODE * ele)
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
        QNODE ** d    =   qu -> data;
        int size      =   qu -> size;
        qu -> data    =   malloc(sizeof(QNODE *) * 2 * size);
        for(int i = 0; i < 2 * size; i++)
        {
            qu -> data[i] = createQueueNode(NULL, 0);
        }
        qu -> size    =   size * 2;
        
        for(int i = 0; i < size; i++)
        {
            qu -> data[i] = d[(qu -> front + i) % size];
        }
        
        qu -> front             =  0;
        qu -> rear              =  size;
        qu -> data[qu -> rear]  =  ele;
        freeQueueNode(d, size);
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
QNODE* dequeue(QUEUE * qu)
{
    QNODE * ele  =  getFront(qu);
    
    if( qu -> front == qu -> rear)
    {
        qu -> front  =  -1;
        qu -> rear   =  -1;
        return ele;
    }
    
    qu -> front = (qu -> front + 1) % (qu -> size);
    return ele;
}


// .......................... QUEUE UTILITY ENDS  ...............................


// .......................... BFS UTILITY FUNCTION ..............................

int isInMaze(int x, int y)
{
    if((0 <= x && x < ROW) && (0 <= y && y < COL)) return 1;
    return 0;
}

/**
 * @brief Creates integer matrix and returns the reference
 * 
 * @param row 
 * @param col 
 * @return int** 
 */
int ** createintMatrix(int row, int col)
{
    int ** mat = malloc(sizeof(int *) * row);
    for(int i = 0; i < row; i++)
    {
        mat[i] = malloc(sizeof(int) * col);
    }
    return mat;

}

/**
 * @brief BFS utility to go through the maze and returns the shortes path distance
 *      -1 if there is no path from source to destination
 * 
 * @param maze 
 * @param row 
 * @param col 
 * @param source 
 * @param destination 
 * @return int 
 */
int BFS(char ** maze, int row, int col, LOC * source, LOC * destination)
{
    
    if(!source || !destination) return -1;

    // The visited matrix will have the entries as 0's by default.
    int ** visited = createintMatrix(row, col);

    visited[source -> x][source -> y] = 1;

    QUEUE * qu = createQueue(MAXSIZE);

    QNODE * tempnode = createQueueNode(source, 0);
    enqueue(qu, tempnode);


    int rowCheck[] = {0, 1, 0, -1};
    int colCheck[] = {1, 0, -1, 0};

    while(!isQEmpty(qu))
    {

        QNODE * current = getFront(qu); 

        LOC * locate = current -> coordinates; 

        if(locate -> x == destination -> x && locate -> y == destination -> y)
        {
            return current -> distance;
        }

        QNODE * deletednode = dequeue(qu);  

        for(int i = 0; i < 4; i++)
        {
            int x = locate -> x + rowCheck[i];
            int y = locate -> y + colCheck[i];

            if(isInMaze(x,y) && maze[x][y] == PATH && !visited[x][y])
            {
                visited[x][y] = 1;
                QNODE * adjacent = createQueueNode(createLocation(x, y), (current -> distance) + 1);

                enqueue(qu, adjacent);
            }
        }
    }

    freeQueue(qu);
    return -1;
}

int main(int argc, char * argv[])
{
    if(!argv[1])
    {
        printf("No file given as input...");
        exit(0);
    }
    char * filename = argv[1];
    char ** Maze = ReadMatrixFromFile(filename);

    /**
     * @brief Finding first the starting location
     *        Then finding the destination location
     * 
     */
    LOC * source = findLOC(Maze, ROW, COL, 0, PATH);
    LOC * destination = findLOC(Maze, ROW, COL, COL-1, PATH);

    int short_distance = BFS(Maze, ROW, COL, source, destination);

    printf("%d", short_distance);
}