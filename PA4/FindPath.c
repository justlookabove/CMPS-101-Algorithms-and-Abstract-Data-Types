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
*                               FindPath.c                                *
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

    int op1, op2;
    fscanf(in, "%d", &op1);
    Graph G = newGraph(op1);

    fscanf(in, "%d %d", &op1, &op2);
    while (op1 != 0) {
        addEdge(G, op1, op2);
        fscanf(in, "%d %d", &op1, &op2);
    }
    printGraph(out, G);

    fscanf(in, "%d %d", &op1, &op2);
    while (op1 != 0) {
        BFS(G, op1);
        int d = getDist(G, op2);
        if (d != INF) {
            fprintf(out, "The distance from %d to %d is %d\n", op1, op2, d);
            fprintf(out, "A shortest %d-%d path is: ", op1, op2);
            List p = newList();
            getPath(p, G, op2);
            printList(out, p);
            fprintf(out, "\n");
        } else {
            fprintf(out, "The distance from %d to %d is infinity\nNo %d-%d path exists\n", op1, op2, op1, op2);
        }
        fscanf(in, "%d %d", &op1, &op2);
    }

    freeGraph(&G);
    /* close files */
    fclose(in);
    fclose(out);

    return (0);
}
