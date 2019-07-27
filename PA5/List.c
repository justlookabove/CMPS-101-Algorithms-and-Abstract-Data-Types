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
*                                 List.c                                  *
*                                                                         *
**************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include "List.h"

/**************************************************************************
*                                                                         *
*                        Constructors - Destructors                       *
*                                                                         *
**************************************************************************/

// Creates new empty list

List newList(void) {
    List list = (List) malloc(sizeof (struct _List));
    list->front = NULL;
    list->back = NULL;
    list->cursor = NULL;
    list->length = 0;
    list->index = -1;
    return list;
}

// Creates a Node with int value, Node prev, and Node next.

Node *newNode(int value, Node *prev, Node *next) {
    Node *n = malloc(sizeof (struct _Node));
    n->value = value;
    n->prev = prev;
    n->next = next;
    return n;
}

// Frees memory for the list

void freeList(List *pL) {
    if (pL == NULL)
        return;
    List L = *pL;
    if (L == NULL)
        return;
    freeNodes(L->front);
    free(L);
    *pL = NULL;

}

// Frees memory for the Node.

void freeNodes(Node *front) {
    Node *i = front;
    while (i != NULL) {
        Node *temp = i;
        i = i->next;
        free(temp);
    }
}

/**************************************************************************
*                                                                         *
*                            Access functions                             *
*                                                                         *
**************************************************************************/

// Returns the number of elements in this List.

int length(List L) {
    return L->length;
}

// If cursor is defined, returns the index of the cursor element

int index(List L) {
    return L->index;
}

// Returns front element.
// Pre: length() > 0

int front(List L) {
    if (L->length <= 0) {
        return 0;
    }
    return L->front->value;
}

// Returns back element.
// Pre: length() > 0

int back(List L) {
    if (L->length <= 0) {
        return 0;
    }
    return L->back->value;
}

// Returns cursor element.
// Pre: length() > 0

int get(List L) {
    if (L->length <= 0 || L->index < 0) {
        return -1;
    }
    return L->cursor->value;
}

// Returns true if this List and L are the same integer
// sequence. The cursor is ignored in both lists.

int equals(List A, List B) {
    Node* Q = A->front;
    Node* W = B->front;
    if (A->length != B->length) {
        return 0;
    }
    while (Q != NULL) {
        if (Q->value != W->value)
            return 0;
        Q = Q->next;
        W = W->next;
    }
    return 1;
}

/**************************************************************************
*                                                                         *
*                         Manipulation procedures                         *
*                                                                         *
**************************************************************************/

//Reset's ths list to its original empty state.

void clear(List L) {
    freeNodes(L->front);
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.

void moveFront(List L) {
    assert(L != NULL);
    if (L->length == 0) {
        return;
    }
    L->cursor = L->front;
    L->index = 0;
}

// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.

void moveBack(List L) {
    assert(L != NULL);
    if (L->length == 0) {
        return;
    }
    L->cursor = L->back;
    L->index = L->length - 1;
}

// If cursor is defined and not at front, moves cursor one step toward
// front of this List. If cursor is defined and at front, cursor becomes
// undefined. If cursor is undefined does nothing.

void movePrev(List L) {
    if (L->length == 0 || L->cursor == NULL) {
        return;
    }
    if (L->cursor == L->front) {
        L->cursor = NULL;
        L->index = -1;
        return;
    }
    L->cursor = L->cursor->prev;
    L->index--;
}

// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.

void moveNext(List L) {
    if (L->length == 0 || L->cursor == NULL) {
        return;
    }
    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
        return;
    }
    L->cursor = L->cursor->next;
    L->index++;
}

// Insert new element into this List. If List is non-empty, insertion
// takes place before front element.

void prepend(List L, int data) {
    Node *node = newNode(data, NULL, L->front);
    if (L->length == 0) {
        L->front = node;
        L->back = node;
        L->length++;
        return;
    }
    L->front->prev = node;
    L->front = node;
    L->length++;
    if (L->index >= 0) {
        L->index++;
    }
}

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.

void append(List L, int data) {
    Node *node = newNode(data, L->back, NULL);
    if (L->length == 0) {
        L->front = node;
        L->back = node;
        L->length = 1;
        return;
    }
    L->back->next = node;
    L->back = node;
    L->length++;
}

// Insert new element before cursor.
// Pre: length() > 0, index() >= 0

void insertBefore(List L, int data) {
    if (L->length == 0 || L->index < 0) {
        return;
    }
    if (L->cursor == L->front) {
        prepend(L, data);
        return;
    }
    Node *node = newNode(data, L->cursor->prev, L->cursor);
    L->cursor->prev->next = node;
    L->cursor->prev = node;
    L->length++;
    L->index++;
}

// Insert new element after cursor.
// Pre: length() > 0, index() >= 0

void insertAfter(List L, int data) {
    if (L->length == 0 || L->index < 0) {
        return;
    }
    if (L->cursor == L->back) {
        append(L, data);
        return;
    }
    Node *node = newNode(data, L->cursor, L->cursor->next);
    L->cursor->next->prev = node;
    L->cursor->next = node;
    L->length++;
}

// Deletes the front element.
// Pre: length() > 0

void deleteFront(List L) {
    if (L->length == 0) {
        return;
    }
    if (L->cursor == L->front) {
        L->cursor = NULL;
        L->index = -1;
    } else {
        L->index--;
    }
    Node *oldFront = L->front;
    L->front = L->front->next;
    L->length--;
    if (L->length > 0)
        L->front->prev = NULL;
    free(oldFront);
}

// Deletes the back element.
// Pre: length() > 0

void deleteBack(List L) {
    if (L->length == 0) {
        return;
    }
    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
    }
    Node *oldBack = L->back;
    L->back = L->back->prev;

    L->length--;
    if (L->length > 0)
        L->back->next = NULL;
    free(oldBack);
}

// Deletes cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0

void delete(List L) {
    if (L->length == 0 || L->index < 0) {
        return;
    }
    if (L->cursor == L->front) {
        deleteFront(L);
        L->cursor = NULL;
        return;
    }
    if (L->cursor == L->back) {
        deleteBack(L);
        L->cursor = NULL;
        return;
    }
    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev;
    free(L->cursor);
    L->cursor = NULL;
    L->index = -1;
    L->length--;
}

/**************************************************************************
*                                                                         *
*                             Other Operations                            *
*                                                                         *
**************************************************************************/

// Overrides Object's to String method. Returns a String
// representation of this List consisting of a space
// separated sequence of integers, with front on left.

void printList(FILE* out, List L) {
    for (Node *node = L->front; node != NULL; node = node->next) {
        fprintf(out, "%d ", node->value);
    }
}

// Used in addArc function in Graph.c, used to check if function 
// already has a edge.

int contains(List L, int I) {
    if (L == NULL) {
        return 0;
    }
    Node *old_cursor = L->cursor;
    int old_index = L->index;
    moveFront(L);
    while (L->cursor) {
        if (L->cursor->value == I) {
            L->cursor = old_cursor;
            L->index = old_index;
            return 1;
        }
        moveNext(L);
    }
    L->cursor = old_cursor;
    L->index = old_index;
    return 0;
}

// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.

List copyList(List L) {
    List copy = newList();
    for (Node *node = L->front; node != NULL; node = node->next) {
        append(copy, node->value);
    }
    return copy;
}
