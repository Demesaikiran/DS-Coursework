#include<stdio.h>
#include<stdlib.h>

/**
 * @brief Adjacency list node structure
 * 
 * @param dest
 *          It is the connected node to the vertex v in Adjacency list
 * @param next
 *          It is the pointer to the next edge of vertex v
 */
typedef struct node NODE;
struct node
{
    int dest;
    NODE * next;
};

/**
 * @brief Adjacency List structure
 * 
 * @param V
 *          Number of vertices in the Graph / List
 * @param vertex
 *          Array of vertices with respective edge nodes linkedlist
 * 
 */
typedef struct adjlist AList;
struct adjlist
{
    int V;
    NODE ** vertex;
};

/**
 * @brief Create a Node object
 * 
 * @param v 
 *          creates a node with vertex point - v
 * @return NODE* 
 */
NODE * createNode(int v)
{
    NODE * newnode = (NODE *)malloc(sizeof(NODE));
    newnode -> dest = v;
    newnode -> next = NULL;
    return newnode;
}

/**
 * @brief Create a Adj List object
 * 
 * @param vertices 
 *          Number of vetices
 * @return AList* 
 */
AList * createAdjList(int vertices)
{
    AList * newList = (AList *) malloc(sizeof(AList));
    newList -> V = vertices;

    newList -> vertex = malloc(vertices * sizeof(NODE *));
    for(int i = 0; i < vertices; ++i)
        newList -> vertex[i] = NULL;

    return newList;
}

/**
 * @brief Create a Array object
 * 
 * @param size 
 *          Array object of size - size
 * @return int* 
 */
int * createArray(int size)
{
    int * newArray = malloc(size * sizeof(int));
    for(int i = 0; i < size; ++i)
        newArray[i] = 0;
    return newArray;
}

/**
 * @brief Adding Edge to the Un-Directed graph 
 *        (Source       -->  Destination)
 *        (Destination  -->  Source)
 * 
 * @param graph 
 *          Adjacency list reference
 * @param source 
 *          Edge - Source vertex information
 * @param destination 
 *          Edge - destination vertex information
 */
void addEdge(AList ** graph, int source, int destination)
{
    NODE * newnode = createNode(destination);
    newnode -> next = (*graph) -> vertex[source];
    (*graph) -> vertex[source] = newnode;

    newnode = createNode(source);
    newnode -> next = (*graph) -> vertex[destination];
    (*graph) -> vertex[destination] = newnode;
}

/**
 * @brief Create a Graph object
 * 
 * @param V 
 *      Number of Vertices
 * @param E 
 *      Number of Edges
 * @return AList* 
 */
AList * createGraph(int V, int E)
{
    AList * newGraph = createAdjList(V);
    int source;
    int destination;
    for(int i = 0; i < E; ++i)
    {
        scanf("%d%d", &source, &destination);
        addEdge(&newGraph, source, destination);
    }

    return newGraph;
}

/**
 * @brief Taking Graph input from the FILE
 * 
 * @param filename 
 *          Filename from the command line arguments
 * @return AList* 
 */
AList * inputGraph(char * filename)
{
    FILE * fp;
    fp = fopen(filename, "r");
    if(!fp)
    {
        printf("\nERROR IN OPENING FILE %s", filename);
        exit(1);
    }

    int nOfEdges;
    int nOfVertices;

    if(fscanf(fp, "%d%d", &(nOfVertices), &(nOfEdges)) != 2)
        exit(1);

    AList * newGraph = createAdjList(nOfVertices);
    int source, destination;

    while(fscanf(fp, "%d%d", &source, &destination) != EOF)
        addEdge(&newGraph, source, destination);

    fclose(fp);
    return newGraph;
}

/**
 * @brief Depth First Search Graph Traversal
 * 
 * @param graph 
 *          Adjacency list object
 * @param visited 
 *          Visited vertices information
 * @param v 
 *          vertex - v
 */
void DFS(AList * graph, int ** visited, int v)
{
    (*visited)[v]    =  1;
    NODE * traverse  =  graph -> vertex[v];

    while(traverse != NULL)
    {
        if((*visited)[traverse -> dest]) 
        {
            traverse = traverse -> next;
            continue;
        }
        DFS(graph, &(*visited), traverse -> dest);
        traverse = traverse -> next;
    }
}

/**
 * @brief Number of connected components in a Graph
 * 
 * @param graph 
 *          Adjacency list object
 * @return int 
 *          Count of number of connected Components
 */
int noOfConnectedComponents(AList * graph)
{
    int count      =  0;
    int V          =  graph -> V;
    int * visited  =  createArray(V+1);

    for(int i = 1; i <= V; ++i)
    {
        if(visited[i]) continue;
        DFS(graph, &(visited), i);
        count++;
    }
    return count;
}

/**
 * @brief Prints the Adjacency list
 * 
 * @param graph 
 *          Adjacency list object
 */
void printGraph(AList * graph)
{
    for(int i = 0; i < graph -> V; i++)
    {
        NODE * temp = graph -> vertex[i];
        printf("\nVertex %d\n", i);
        while(temp)
        {
            printf("%d --> ", temp -> dest);
            temp = temp -> next;
        }
        printf("NULL\n");
    }
}

int main(int argc, char * argv[])
{
    AList * graph = inputGraph(argv[1]);
    //createGraph(nOfVertices, nOfEdges);

    printf("%d", noOfConnectedComponents(graph));
}