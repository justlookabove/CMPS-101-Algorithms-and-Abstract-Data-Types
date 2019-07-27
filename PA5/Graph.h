/**************************************************************************
*                                                                         *
*                   Kiran Gunasekaran, kgunase1@ucsc.edu                  *
*                                                                         *
*                              CMPS 101: PA5                              *
*                                                                         *
*                            December 7, 2017                             *
*                                                                         *
*  _____________________________________________________________________  *
*                                                                         *
*                                 Graph.h                                 *
*                                                                         *
**************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H
#define NIL 0
#define UNDEF -1

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

struct _Graph {
    List *adjacency;
    int *color;
    int *parent;
    int *discoverTime;
    int *finishTime;
    int time;
    int numVertices; // Number of Vertices
    int numEdges; // Number of Edges
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
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/**************************************************************************
*                                                                         *
*                         Manipulation procedures                         *
*                                                                         *
**************************************************************************/

void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

/**************************************************************************
*                                                                         *
*                             Other Operations                            *
*                                                                         *
**************************************************************************/

Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif /* GRAPH_H */
