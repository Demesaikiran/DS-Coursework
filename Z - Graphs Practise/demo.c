#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

// a function to find minimum among 2 values
int min(int a, int b){
    if(a<=b) return a;
    else return b;
}
// a linked list node with two fields
typedef struct node {
  int vertex;
  struct node* next;
}node;
struct node* createNode(int);

// graph structure contains vertices and node 
typedef struct Graph {
  int numVertices;
  struct node** adjLists;
}Graph;

// Create a node
struct node* createNode(int v) {
  //dynamically alllocating memory
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Create a graph
struct Graph* createGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));

  int i;
  //assigning for all the vertices 
  for (i = 1; i <= vertices; i++)
    graph->adjLists[i] = NULL;

  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int s, int d) {
  // Add edge from s to d
  struct node* newNode = createNode(d);
  newNode->next = graph->adjLists[s];
  graph->adjLists[s] = newNode;

  // Add edge from d to s
  newNode = createNode(s);
  newNode->next = graph->adjLists[d];
  graph->adjLists[d] = newNode;
}


//--------------------------------------------------------
/*
u --> The vertex to be visited next
visited[] --> keeps track of visited vertices
disc[] --> Stores discovery times of visited vertices
parent[] --> Stores parent vertices in DFS tree
child --> count the child in DFS tree
*/
int time = 0;
// this  recursive function returns true for an articulation point
bool dfs(Graph *g, int u, bool visited[],int disc[], int low[], int parent[]){

  int child = 0;//count no of children

  visited[u] = true;// current node is visited

  time++;

  disc[u] = low[u] = time; // assign low and disc time

  node *adjlist = g->adjLists[u];
  node *temp = adjlist;
  // go through all vertices adjacent to this
  while(temp){
    int v = temp->vertex;

    if(!visited[v]){
      child++;
      parent[v] = u;
      // dfs call subgraph
      if(dfs(g,v,visited,disc,low,parent)) return true;
      // ancester find
      low[u] = min(low[u],low[v]);
      //root with > 2 child or not
      if(parent[u] == -1 && child > 1) return true;
      //not root 
      if(parent[u] != -1 && low[v]>= disc[u]) return true;
    }

    else if(v != parent[u])
      low[u] = min(low[u],disc[v]);

    temp = temp->next;
  }
  return false;
}


/*
v --> no of vertices 
vis[] --> visited[] --> keeps track of visited vertices
disc[] --> Stores discovery times of visited vertices
par[] --> parent[] --> Stores parent vertices in DFS tree
child --> count the child in DFS tree
*/
int isTc(Graph *g, int v){
  // initializing the vis 
  bool *vis = malloc(sizeof(bool)*v);
  int *disc = malloc(sizeof(int)*v);
  int *low = malloc(sizeof(int)*v);
  int *par = malloc(sizeof(int)*v);

 //Initialize parent and visited arrays

  for(int i = 1; i <= v; i++){
    par[i] = -1;
    vis[i] = false;
  }
  // iterate for all vertices 
  for(int i = 1; i <= v; i++)
    if(dfs(g,i,vis,disc,low, par) == true) 
      return false;
// check connected or not
  for(int i = 1; i <= v; i++){
    if(vis[i] == false) return false;
  }
  return true;
}

int main() {
 Graph* graph = createGraph(3);
  // addEdge(graph, 1, 2);
  // addEdge(graph, 1, 3 );
  // addEdge(graph, 1, 4);
  // addEdge(graph, 2, 3);
  // addEdge(graph, 2, 4);
  addEdge(graph, 1, 2);
  addEdge(graph, 1, 3);
  addEdge(graph, 2, 3);

  if(isTc(graph,3)){
     printf("yes");
   }
   else printf("no");
  // addEdge(graph, 0, 1);
  // addEdge(graph, 0, 2);
  // addEdge(graph, 0, 3);
  // addEdge(graph, 1, 2);

  //printGraph(graph);

  return 0;
}