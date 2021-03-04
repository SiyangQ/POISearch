/* KDTree.h
*
* Created by Siyang Qiu (siyangq@student.unimelb.edu.au) 14/Sep./2020
*
* support functions for a KDTree. 
* 
* functions: create new KDTree, add elements to the tree, find nearest neighbour in the 
  tree, range search in tree and free tree
*
*/

#ifndef KDTREEH
#define KDTREEH

#include <stdlib.h>
#include "list.h"

typedef struct KDNode KDNode_t;

struct KDNode {
    listNode_t *data;
    double key1;
    double key2;
    KDNode_t *left;
    KDNode_t *right;
    int isKey1; // TRUE if key1 is the comparing key
};

void *KDTreeInsert(KDNode_t *root, void *d, double newKey1, double newKey2);
void freeKDTree(KDNode_t *node);
KDNode_t *findNearestNeighbour(KDNode_t *node, double searchKey1, double searchKey2, int *numComparisons);
void radiusSearch(KDNode_t *root, double x, double y, double r, FILE *filePtr);

#endif