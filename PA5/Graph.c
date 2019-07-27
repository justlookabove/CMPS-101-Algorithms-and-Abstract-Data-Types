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
*                                 Graph.c                                 *
*                                                                         *
**************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2

#include "Graph.h"

/**************************************************************************
*                                                                         *
*                        Constructors - Destructors                       *
*                                                                         *
**************************************************************************/

// Returns a Graph pointing to a newly created GraphObj representing 
// a graph having n vertices and no edges. 

Graph newGraph(int n) {
    Graph graph = (Graph) malloc(sizeof (struct _Graph));
    graph->adjacency = (List*) calloc(n + 1, sizeof (struct _List));
    graph->color = (int*) calloc(n + 1, sizeof (int));
    graph->parent = (int*) calloc(n + 1, sizeof (int));
    graph->discoverTime = (int*) calloc(n + 1, sizeof (int));
    graph->finishTime = (int*) calloc(n + 1, sizeof (int));
    graph->time = 0;
    graph->numVertices = n;
    graph->numEdges = 0;
    for (int i = 1; i < (n + 1); i++) {
        graph->adjacency[i] = newList();
        graph->color[i] = WHITE;
        graph->parent[i] = NIL;
        graph->discoverTime[i] = UNDEF;
        graph->finishTime[i] = UNDEF;
    }
    return graph;
}

// Frees all dynamic memory associated with the Graph *pG, then 
// sets the handle *pG to NULL.

void freeGraph(Graph* pG) {
    if (pG == NULL || *pG == NULL) {
        return;
    }
    Graph G = *pG;
    for (int i = 1; i <= getOrder(G); i++) {
        freeList(G->adjacency + i);
    }
    free(G->adjacency);
    free(G->color);
    free(G->parent);
    free(G->discoverTime);
    free(G->finishTime);
    free(*pG);
    *pG = NULL;
}

/**************************************************************************
*                                                                         *
*                            Access functions                             *
*                                                                         *
**************************************************************************/

// Returns the number of Vertices.

int getOrder(Graph G) {
    if (G == NULL) {
        return 0;
    }
    return G->numVertices;
}

// Returns the number of Edges 

int getSize(Graph G) {
    if (G == NULL) {
        return 0;
    }
    return G->numEdges;
}

// Return the parent of vertex u in the Breadth-First tree created 
// by BFS(), or NIL if BFS() has not yet been called. 

int getParent(Graph G, int u) {
    if (G == NULL || u < 1 || u > getOrder(G)) {
        return 0;
    }
    return G->parent[u];
}

// Returns the discover time of the vertex

int getDiscover(Graph G, int u) {
    if (G == NULL || u < 1 || u > getOrder(G)) {
        return 0;
    }
    return G->discoverTime[u];
}

// Returns the finish time of the vertex

int getFinish(Graph G, int u) {
    if (G == NULL || u < 1 || u > getOrder(G)) {
        return 0;
    }
    return G->finishTime[u];
}

/**************************************************************************
*                                                                         *
*                         Manipulation procedures                         *
*                                                                         *
**************************************************************************/

// Inserts a new directed edge from u to v, i.e. v is added to the 
// adjacency List of u (but not u to the adjacency List of v).  

void addArc(Graph G, int u, int v) {
    List list = G->adjacency[u];
    if (contains(list, v)) {
        return;
    }
    G->numEdges++;
    moveFront(list);
    while (list->cursor != NULL) {
        if (v < list->cursor->value) {
            insertBefore(list, v);
            return;
        }
        moveNext(list);
    }
    append(list, v);
}

// Inserts a new edge joining u to v, i.e. u is added to the 
// adjacency List of v, and v to the adjacency List of u.

void addEdge(Graph G, int u, int v) {
    if (u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)) {
        return;
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->numEdges--;
}

// Private helper function for DFS, the recursive portion of DFS
// which goes through all the vertices of the adjacency list.

void DFS_Visit(Graph G, int u) {
    G->time++;
    G->discoverTime[u] = G->time;
    G->color[u] = GRAY;
    List adj = G->adjacency[u];
    moveFront(adj);
    while (adj->cursor != NULL) {
        int v = get(adj);
        if (G->color[v] == WHITE) {
            G->parent[v] = u;
            DFS_Visit(G, v);
        }
        moveNext(adj);
    }
    G->color[u] = BLACK;
    G->time++;
    G->finishTime[u] = G->time;
}

// Performs the Depth First Search with the vertices in List S order

void DFS(Graph G, List S) {
    if (length(S) != getOrder(G)) {
        return;
    }
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    G->time = 0;
    moveFront(S);
    while (S->cursor != NULL) {
        int v = get(S);
        if (G->color[v] == WHITE) {
            DFS_Visit(G, v);
        }
        moveNext(S);
    }
    int vertices[length(S)];
    int size = length(S);
    for (int i = 0; i < size; i++) {
        moveFront(S);
        vertices[i] = get(S);
        deleteFront(S);
    }
    for (int i = 1; i < size; i++) {
        int key = vertices[i];
        int finishTime = G->finishTime[key];
        int j = i - 1;
        while (j >= 0 && G->finishTime[vertices[j]] < finishTime) {
            vertices[j + 1] = vertices[j];
            j = j - 1;
        }
        vertices[j + 1] = key;
    }
    for (int i = 0; i < size; i++) {
        append(S, vertices[i]);
    }
}

/**************************************************************************
*                                                                         *
*                             Other Operations                            *
*                                                                         *
**************************************************************************/

// Used to get the transpose of a Graph

Graph transpose(Graph G) {
    Graph flip = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        moveFront(G->adjacency[i]);
        while (index(G->adjacency[i]) >= 0) {
            addArc(flip, get(G->adjacency[i]), i);
            moveNext(G->adjacency[i]);
        }
    }
    return flip;
}

// Used to create a copy of a Graph.

Graph copyGraph(Graph G) {
    Graph copy = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        moveFront(G->adjacency[i]);
        while (index(G->adjacency[i]) >= 0) {
            addArc(copy, i, get(G->adjacency[i]));
            moveNext(G->adjacency[i]);
        }
    }
    return copy;
}

// Prints the adjacency list representation of G to the
// file pointed to by out.

void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjacency[i]);
        fprintf(out, "\n");
    }
}
