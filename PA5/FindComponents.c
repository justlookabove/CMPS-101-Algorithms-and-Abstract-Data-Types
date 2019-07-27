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
*                            FindComponenets.c                            *
*                                                                         *
**************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

#define MAX_LEN 300

int main(int argc, char * argv[]) {

    // check command line for correct number of arguments
    if (argc != 3) {
        printf("FilePath: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Creates FILE in and out and initalizes them for read and 
    // write respectivelty.
    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[1]);
        exit(1);
    }

    // Reading from the inupt files
    // op1 reads and stores the first line
    int op1, op2;
    fscanf(in, "%d", &op1);

    // New Graph, checks that op1 does not equal 0 (not an empty list)
    // else, reads the rest of the rest of the file
    Graph G = newGraph(op1);
    fscanf(in, "%d %d", &op1, &op2);
    while (op1 != 0) {
        addArc(G, op1, op2);
        fscanf(in, "%d %d", &op1, &op2);
    }

    // New List and printing the Adjacenty list representation
    // of G using DFS
    List L = newList();
    for (int i = 1; i <= getOrder(G); i++) {
        append(L, i);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    // Performs DFS on graph G
    DFS(G, L);

    // Performs DFS on transpose of graph G
    Graph T = transpose(G);
    DFS(T, L);
    moveFront(L);

    // Initalizing componetCount (used to find number of Strongly
    // Connected Components
    int componentCount = 0;
    for (int i = 1; i <= getOrder(G); i++) {
        if (getParent(T, i) == NIL) {
            componentCount++;
        }
    }
    fprintf(out, "G contains %d strongly connected components:\n", componentCount);

    // Initalizes an array of Lists to store the scc values	
    List scc[componentCount];
    for (int i = 0; i < componentCount; i++) {
        scc[i] = newList();
    }

    // Finding number of Strongly Connected Coponents
    moveFront(L);
    for (int i = 1, c = componentCount; i <= getOrder(G); i++) {
        int v = get(L);
        int greatAncestor = v, parent = T->parent[v];
        while (parent != 0) {
            greatAncestor = parent;
            parent = T->parent[parent];
        }
        if (v == greatAncestor){
            c--;
        }
        append(scc[c], v);
        moveNext(L);
    }

    // Printing the number of Strongly Connected Coponents
    for (int componentNum = 0; componentNum < componentCount; componentNum++) {
        fprintf(out, "Component %d: ", componentNum + 1);
        printList(out, scc[componentNum]);
        fprintf(out, "\n");
        freeList(&scc[componentNum]);
    }

    // Freeing all memory ( can't have those pesky memory leaks now! )
    freeGraph(&G);
    freeGraph(&T);
    freeList(&L);

    // Close files
    fclose(in);
    fclose(out);
    return (0);
}

