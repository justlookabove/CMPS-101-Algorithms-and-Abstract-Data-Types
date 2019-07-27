/**************************************************************************
*                                                                         *
*                   Kiran Gunasekaran, kgunase@ucsc.edu                   *
*                                                                         *
*                              CMPS 101: PA2                              *
*                                                                         *
*                             October 16, 2017                            *
*                                                                         *
*  _____________________________________________________________________  *
*                                                                         *
*                                   Lex.c                                 *
*                                                                         *
**************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return 0;
    }
    
    // Creates FILE in and out and initalizes them for read and write respectivelty.
    FILE *in = fopen(argv[1], "r");
    
    if( in == NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    FILE *out = fopen(argv[2], "w");
    if (out == NULL){
        printf("Unable to open file %s for writing\n", argv[1]);
        exit(1);
    }
    
    // Reads each line in input file and counts
    char line[MAX_LEN];
    int count = 0;
    for(char line[MAX_LEN]; fgets(line, MAX_LEN, in) != NULL; count++)  {}
    
    
    // Resets the pointer to the begining of the file
    rewind(in);
    
    char lines[count - 1][MAX_LEN];
    
    // Goes through the file and copies each line into array.
    for(int i = 0; fgets(line, MAX_LEN, in) != NULL; i++) {
        strcpy(lines[i++], line);
    }
    
    // Creates a new List and appends to start sorting (from Line no.0).
    List ADT = newList();
    append(ADT, 0);
    
    // Implementing Correct-Place Insertion (similar to Insertion Sort)
    for(int k = 1; k < count; k++) {
        char *str = lines[k];
        
        moveFront(ADT);
        
        if (strcmp(str, line[0]) < 0){
            prepend(ADT, k);
            k++;
            continue;
        }
        
        // To compare the current line and the lines in the list
        for(int i = k + 1; k < length(ADT) && strcmp(str, lines[i]) > 0; i++) {
            moveNext(ADT);
        }
        insertAfter(ADT, k);
    }
    
    // Resets the index to the front of the list.
    moveFront(ADT);
    
    // Goes through the list and prints out the lines in the right order.
    while(index(ADT) > 0) {
        fprintf(out, "%s ", lines[get(ADT)]);
        moveNext(ADT);
    }
    
    // Closes the files
    fclose(in);
    fclose(out);
    
    //Frees the ADT (prevent memory leaks)
    freeList(&ADT);
    
    return 0;
}


