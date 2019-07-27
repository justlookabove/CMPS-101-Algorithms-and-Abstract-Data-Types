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
    graph->distance = (int*) calloc(n + 1, sizeof (int));
    graph->numVertices = n;
    graph->numEdges = 0;
    graph->source = NIL;
    for (int i = 1; i < (n + 1); i++) {
        graph->adjacency[i] = newList();
        graph->color[i] = WHITE;
        graph->parent[i] = NIL;
        graph->distance[i] = INF;
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
    free(G->distance);
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

// Returns the Source
int getSource(Graph G) {
    if (G == NULL) {
        return 0;
    }
    return G->source;
}

// Return the parent of vertex u in the Breadth-First tree created 
// by BFS(), or NIL if BFS() has not yet been called. 
int getParent(Graph G, int u) {
    if (G == NULL || u < 1 || u > getOrder(G)) {
        return 0;
    }
    return G->parent[u];
}

int getDist(Graph G, int u) {
    if (u < 1 || u > getOrder(G)) {
        return 0;
    }
    if (getSource(G) == NIL) {
        return INF;
    }
    return G->distance[u];
}

// Appends to the List L the vertices of a shortest path in G from 
// source to u, or appends to L the value NIL if no such path exists.
void getPath(List L, Graph G, int u) {
    if (getSource(G) == NIL) {
        return;
    }
    List temp = newList();
    int currentNode = u;
    int parent = G->parent[currentNode];
    if (parent == NIL) {
        if (G->source == currentNode)
            append(L, currentNode);
        else
            append(L, NIL);
        freeList(&temp);
        return;
    }
    while (currentNode != NIL) {
        prepend(temp, currentNode);
        currentNode = G->parent[currentNode];
    }
    if (length(temp) == 0) {
        append(L, u);
        freeList(&temp);
        return;
    }
    moveFront(temp);
    while (temp->cursor != NULL) {
        append(L, get(temp));
        moveNext(temp);
    }
    freeList(&temp);
}

/**************************************************************************
*                                                                         *
*                         Manipulation procedures                         *
*                                                                         *
**************************************************************************/

// Function makeNull() deletes all edges of G, restoring 
// it to its original (no edge) state.  
void makeNull(Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        clear(G->adjacency[i]);
    }
    G->numEdges = 0;
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

// Runs the BFS algorithm on the Graph G with source s, setting the 
// color, distance, parent, and source fields of G accordingly.  
void BFS(Graph G, int s) {
    G->source = s;
    for (int i = 1; i < s; i++) {
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    for (int i = s + 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    append(Q, s);
    while (length(Q) > 0) {
        moveFront(Q);
        int currentNode = get(Q);
        delete(Q);
        List adj = G->adjacency[currentNode];
        moveFront(adj);
        while (adj->cursor != NULL) {
            int neighborNode = get(adj);
            if (G->color[neighborNode] == WHITE) {
                G->color[neighborNode] = GRAY;
                G->distance[neighborNode] = G->distance[currentNode] + 1;
                G->parent[neighborNode] = currentNode;
                append(Q, neighborNode);
            }
            moveNext(adj);
        }
        G->color[currentNode] = BLACK;
    }
    freeList(&Q);
}

/**************************************************************************
*                                                                         *
*                             Other Operations                            *
*                                                                         *
**************************************************************************/

// printGraph() prints the adjacency list representation of G to 
// the file pointed to by out.
void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjacency[i]);
        fprintf(out, "\n");
    }
}
