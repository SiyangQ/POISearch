/* list.h
*
* Created by Siyang Qiu (siyangq@student.unimelb.edu.au) 17/Aug./2020
*
* support functions for a linked list. 
* 
* functions: create new list, add elements to back of the list,
* print a whole list and free list
*
*/

#ifndef LINKEDLISTH
#define LINKEDLISTH

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "structureCLUE.h"
#include "print.h"

// linked list structs
typedef struct node listNode_t;

struct node {
    void *data;
    listNode_t *next;
};

// dictionary functions
void *listInsert(listNode_t *node, void *d);
void freeList(listNode_t *node);
void printListToStdout(listNode_t *n);
void printListToFile(listNode_t *n, FILE *filePtr, double *x, double *y);
void printRadiusListToFile(listNode_t *n, FILE *filePtr, double x, double y, double r);

#endif