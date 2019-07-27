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
*                                  List.h                                 *
*                                                                         *
**************************************************************************/

#ifndef List_h
#define List_h
#include <stdio.h>
#include <stdlib.h>

struct _Node;
typedef struct _Node Node;
struct _List;
typedef struct _List *List;

struct _Node {
    int value;
    Node *prev, *next;
};

struct _List {
    Node *front, *back, *cursor;
    int length, index;
};

/**************************************************************************
*                                                                         *
*                        Constructors - Destructors                       *
*                                                                         *
**************************************************************************/

List newList(void);

void freeList(List *pL);

void freeNodes(Node *front);

/**************************************************************************
*                                                                         *
*                            Access functions                             *
*                                                                         *
**************************************************************************/

int length(List L);

int index(List L);

int front(List L);

int back(List L);

int get(List L);

int equals(List A, List B);

/**************************************************************************
*                                                                         *
*                         Manipulation procedures                         *
*                                                                         *
**************************************************************************/

void clear(List L);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, int data);

void append(List L, int data);

void insertBefore(List L, int data);

void insertAfter(List L, int data);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

int contains(List L, int I);

/**************************************************************************
*                                                                         *
*                             Other Operations                            *
*                                                                         *
**************************************************************************/

void printList(FILE* out, List L);

List copyList(List L);

#endif /* List_h */

