#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

struct edge
{
    int u, v, weight;
};
typedef struct edge EDGE;

struct Graph
{
    int V;
    int E;
    EDGE * edges;
};
typedef struct Graph GRAPH;

struct subset
{
    int parent;
    int rank;
};
typedef struct subset SUBSET;

struct tree
{
    EDGE * edges;
    int weight;
};
typedef struct tree TREE;

/**
 * @brief GRAPH UTILITY FUNCTIONS
 */

/**
 * @brief Swaps the edge pointers
 * 
 * @param a edge object 
 * @param b edge object
 */
void swapEdges(EDGE * a, EDGE * b)
{
    EDGE  temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Sorts the graph edges based on weights
 * 
 * @param graph 
 *          Graph object
 */
void sortGraph(GRAPH ** graph)
{
    for(int i = 0; i < (*graph) -> E ; i++)
    {
        for(int j = 0 ; j < (*graph) -> E - i - 1; j++)
        {
            if((*graph) -> edges[j].weight > (*graph) -> edges[j+1].weight)
            {
                swapEdges(&(*graph) -> edges[j], &(*graph) -> edges[j+1]);
            }
        }
    }
}

/**
 * @brief prints the graph
 * 
 * @param graph 
 */
void printGraph(GRAPH * graph)
{
    for(int i = 0; i < graph -> E; i++)
    {
        printf("%d %d %d\n", graph -> edges[i].u, graph -> edges[i].v, graph -> edges[i].weight);
    }
}

/**
 * @brief FILE UTILITY // Reads the graph from the file
 * 
 * @param filename 
 * @return GRAPH* 
 *          Returns the graph object reference
 */
GRAPH * readGraphFromFile(char * filename)
{
    FILE * fp;
    fp = fopen(filename, "r");

    if(!fp)
    {
        printf("Error in openening file %s", filename);
        exit(1);
    }

    // Reading the number of vertices and no of edges fro mthe first line
    GRAPH * newGraph = (GRAPH *)malloc(sizeof(GRAPH));
    int a, b;
    if(fscanf(fp, "%d %d", &(newGraph -> V), &(newGraph -> E)) != 2)
        exit(1);
    
    // Creating the heap storage for the Edge list.
    newGraph -> edges = malloc((newGraph -> E) * sizeof(EDGE));

    // Iterator i
    int i = 0;
    while(fscanf(fp, "%d%d%d", &newGraph -> edges[i].u, &newGraph -> edges[i].v, &newGraph -> edges[i].weight) != EOF)
        i++;

    fclose(fp);
    return newGraph;
}

/**
 * @brief Creates the set with the parent as itself and rank as 0 for every node
 * 
 * @param size 
 * @return SUBSET* 
 */
SUBSET * makeset(int size)
{
    SUBSET * subsets = malloc(sizeof(SUBSET) * size);

    for(int i = 0; i < size; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    return subsets;
}

/**
 * @brief Returns the parent of the node i
 * 
 * @param subsets 
 * @param i 
 * @return int 
 */
int find(SUBSET * subsets, int i)
{
    if(subsets[i]. parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

/**
 * @brief Unites the two sets based on the conditions assumed in if-else
 *          based on rank.
 * 
 * @param subsets 
 * @param xroot 
 * @param yroot 
 */
void Union(SUBSET ** subsets, int xroot, int yroot)
{
    SUBSET * tempsubset = (*subsets);
    if(tempsubset[xroot].rank < tempsubset[yroot].rank)
        tempsubset[xroot].parent = yroot;
    else if(tempsubset[xroot]. rank > tempsubset[yroot].rank)
        tempsubset[yroot].parent = xroot;

    else
    {
        tempsubset[yroot].parent = xroot;
        tempsubset[xroot].rank++;
    }
}

/**
 * @brief Kruskals algorithm where it returns the tree Data structure
 * 
 * @param graph 
 * @return TREE* 
 */
TREE * kruskals(GRAPH * graph)
{
    sortGraph(&graph);

    SUBSET * subsets = makeset(graph -> V + 1);

    TREE * resultMST = malloc(sizeof(TREE));
    EDGE * result = malloc(sizeof(EDGE) * graph -> V);
    int iterator = 0;
    resultMST -> weight = 0;
    int edgeCount = 0;


    for(int i = 0; i < graph -> E && edgeCount < graph -> V - 1; i++)
    {
        int u = graph -> edges[i].u;
        int v = graph -> edges[i].v;
        int w = graph -> edges[i].weight;

        if(find(subsets, u) != find(subsets, v))
        {
            edgeCount++;
            // printf("%d %d %d\n", graph -> edges[i].u, graph -> edges[i].v, graph -> edges[i].weight);
            Union(&subsets, u, v);
            result[iterator].u = u;
            result[iterator].v = v;
            result[iterator++].weight = w;
            resultMST -> weight += w;
        }
    }
    resultMST -> edges = result;
    return resultMST;
}



int main(int argc, char *argv[])
{

    char * filename = argv[1];
    GRAPH * mygraph = readGraphFromFile(filename);


    TREE * mst = kruskals(mygraph);
    EDGE * mstedges = mst -> edges;
    printf("Edges of MST: {");
    for(int i = 0; i < mygraph -> V - 1; i++)
    {
        printf("(%d, %d)", mstedges[i].u, mstedges[i].v);
    }
    printf("}\nWeight of MST: %d", mst->weight);

    return 0;
}