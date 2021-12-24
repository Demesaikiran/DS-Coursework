#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct node NODE;
struct node
{
    int vertex;
    NODE * next;
};

typedef struct graph GRAPH;
struct graph
{
    int V;
    NODE ** list;
};

NODE * createNode(int v)
{
    NODE * newnode = malloc(sizeof(NODE));
    newnode -> vertex = v;
    newnode -> next = NULL;
    return newnode;
}

GRAPH * createGraph(int V)
{
    GRAPH * newgraph = malloc(sizeof(GRAPH));
    newgraph -> V = V;
    newgraph -> list = malloc(sizeof(NODE *));

    for(int i = 1; i <= V; i++)
    {
        newgraph -> list[i] = malloc(sizeof(NODE));
        newgraph -> list[i] = NULL;
    }

    return newgraph;
}

void addEdge(GRAPH ** graph, int source, int destination)
{
    NODE * newnode = createNode(destination);
    newnode -> next = (*graph) -> list[source];
    (*graph) -> list[source] = newnode;

    newnode = createNode(source);
    newnode -> next = (*graph) -> list[destination];
    (*graph) -> list[destination] = newnode;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int * createArray(int size)
{
    int * newArray = malloc(sizeof(int) * size);
    return newArray;
}

int DFS(GRAPH * graph, int vertex, int visited[], int parent[], int discovered[], int low[], int * time)
{
    visited[vertex] = discovered[ vertex ] = low[ vertex ] = TRUE;
    (*time) ++;

    NODE * list = graph -> list[vertex];
    NODE * tempnode = list;

    int childCount = 0;

    while(tempnode)
    {
        int v = tempnode -> vertex;

        if(! visited[vertex])
        {
            childCount ++;
            parent[v] = vertex;
            
            if(DFS(graph, v, visited, parent, discovered, low, time)) return FALSE;

            low[vertex] = min(low[vertex], low[v]);

            if(parent[vertex] == -1 && childCount > 1) return FALSE;

            if(parent[vertex] != -1 && low[v] >= discovered[vertex]) return FALSE;

        }

        else if(v != parent[vertex])
            low[vertex] = min(low[vertex], discovered[v]);

        tempnode = tempnode -> next;
    }
    return TRUE;

}


int checkThreeConnecticity(GRAPH * graph)
{
    int V = graph -> V;

    int * visited     =  createArray(V);
    int * parent      =  createArray(V);
    int * discovered  =  createArray(V);
    int * low         =  createArray(V);
    int time = 0;

    for(int i = 1; i <= V; i++)
    {
        parent[i] = -1;
        visited[i] = FALSE;
    }

    for(int i = 1; i <= V; i++)
    {
        if(DFS(graph, i, visited, parent, discovered, low, &time) == TRUE)
            return FALSE;
    }

    for(int i = 1; i <= V; i++)
    {
        if(visited[i] == FALSE) return FALSE;
    }
    return TRUE;
}


int main()
{
    int V, E;
    scanf("%d%d", &V, &E);

    GRAPH * graph = createGraph(V);

    for(int i = 1; i <= E; i++)
    {
        int source, destination;
        scanf("%d%d", &source, &destination);
        addEdge(&(graph), source, destination);
    }
    for(int i = 1; i <= V; i++)
    {
        NODE * newnode = graph -> list[i];
        while(newnode != NULL)
        {
            printf("%d --> ", newnode -> vertex );
            newnode = newnode -> next;
        }
        printf("\n");
    }

    return checkThreeConnecticity ? printf("YES") : printf("NO");
}