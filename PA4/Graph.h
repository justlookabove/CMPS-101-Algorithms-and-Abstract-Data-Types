/**************************************************************************
*                                                                         *
*                   Kiran Gunasekaran, kgunase@ucsc.edu                   *
*                                                                         *
*                              CMPS 101: PA4                              *
*                                                                         *
*                            November 19, 2017                            *
*                                                                         *
*  _____________________________________________________________________  *
*                                                                         *
*                                 Graph.h                                 *
*                                                                         *
**************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H
#define NIL 0
#define INF -1

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

struct _Graph {
    List *adjacency;
    int *color;
    int *parent;
    int *distance;
    int numVertices; // Number of Vertices (Order)
    int numEdges; // Number of Edges (Size)
    int source; //Source Vertex
};

typedef struct _Graph *Graph;

/**************************************************************************
*                                                                         *
*                        Constructors - Destructors                       *
*                                                                         *
**************************************************************************/

Graph newGraph(int n); 
void freeGraph(Graph* pG);  

/**************************************************************************
*                                                                         *
*                            Access functions                             *
*                                                                         *
**************************************************************************/

int getOrder(Graph G); 
int getSize(Graph G); 
int getSource(Graph G); 
int getParent(Graph G, int u); 
int getDist(Graph G, int u); 
void getPath(List L, Graph G, int u); 

/**************************************************************************
*                                                                         *
*                         Manipulation procedures                         *
*                                                                         *
**************************************************************************/

void makeNull(Graph G); 
void addEdge(Graph G, int u, int v); 
void addArc(Graph G, int u, int v); 
void BFS(Graph G, int s); 

/**************************************************************************
*                                                                         *
*                             Other Operations                            *
*                                                                         *
**************************************************************************/

void printGraph(FILE* out, Graph G); 

#endif /* GRAPH_H */
