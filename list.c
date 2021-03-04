/* list.c
*
* Created by Siyang Qiu (siyangq@student.unimelb.edu.au) 17/Aug./2020
*
* support functions for a linked list. 
* 
* functions: create new list, add elements to back of the list,
* print a whole list and free list
*
*/

#include "list.h"
#include "print.h"
#define NONE 0

// add node to the back of the list
void *listInsert(listNode_t *node, void *d) {

    listNode_t *new = (listNode_t *)malloc(sizeof(listNode_t));
    assert(new);

    // initialise the node
    new->data = d;
    new->next = node;

    return new;
}

// free all memory associated with a list
void freeList(listNode_t *node) {

    if (!node) return;
    freeList(node->next);

    deleteRecord(node->data);
    free(node);
}

// optional function to print a whole linked list to stdout
void printListToStdout(listNode_t *n) {

    while (n) {
        printOutputToStdout(n->data);
        n = n->next;
    }
    printf("\n");
}

// print the whole linked list to file (for keys x, y)
void printListToFile(listNode_t *n, FILE *filePtr, double *x, double *y) {

    while (n) {
        printOutputToFile(n->data, filePtr, x, y);
        n = n->next;
    }
    fprintf(filePtr, "\n");
}

// print the whole linked list to file (with keys x, y, r)
void printRadiusListToFile(listNode_t *n, FILE *filePtr, double x, double y, double r) {

    while (n) {
        printRadiusOutputToFile(n->data, filePtr, x, y, r);
        n = n->next;
    }
    fprintf(filePtr, "\n");
}