/* KDTree.c
*
* Created by Siyang Qiu (siyangq@student.unimelb.edu.au) 14/Sep./2020
*
* support functions for a KDTree. 
* 
* functions: create new KDTree, add elements to the tree, find nearest neighbour in the 
  tree, range search in tree and free tree
*
*/

#include "KDTree.h"
#include "structureCLUE.h"
#include "mathFunctions.h"
#include "list.h"
#include <assert.h>
#include <float.h>

#define TRUE 1
#define FALSE 0
#define SAME 0
#define NO_DISTANCE 0
#define INITIAL_VALUE 0

// insert an element into KD tree
void *KDTreeInsert(KDNode_t *root, void *d, double newKey1, double newKey2) {
    
    KDNode_t **insertLocation = &root;
    int isX = TRUE;
    // find location to insert at
    while (*insertLocation) {
        // if exactly the same coordinate as an existing node, link data to that node as linked list
        if (doubleCompare(newKey1, (*insertLocation)->key1) == SAME && doubleCompare(newKey2, (*insertLocation)->key2) == SAME) {
            (*insertLocation)->data = listInsert((*insertLocation)->data, d);
            return root;
        }

        // go down the tree
        if (isX) {
            if (newKey1 < (*insertLocation)->key1) insertLocation = &((*insertLocation)->left); 
            else insertLocation = &((*insertLocation)->right);

            isX = FALSE;
        } else {
            if (newKey2 < (*insertLocation)->key2) insertLocation = &((*insertLocation)->left);
            else insertLocation = &((*insertLocation)->right);
            
            isX = TRUE;
        }
    }
    
    // create new node
    *insertLocation = (KDNode_t *)malloc(sizeof(KDNode_t));
    assert(*insertLocation);
    (*insertLocation)->data = listInsert(NULL, d);
    (*insertLocation)->left = NULL;
    (*insertLocation)->right = NULL;
    (*insertLocation)->key1 = newKey1;
    (*insertLocation)->key2 = newKey2;
    (*insertLocation)->isKey1 = isX;

    return root;
}

// free whole tree
void freeKDTree(KDNode_t *node) {
    if (!node) return;

    // free list via post-order traversal
    freeKDTree(node->left);
    freeKDTree(node->right);

    freeList(node->data);
    free(node);
}

// recursively find the closest neighbour of key (x, y)
void findNearest(KDNode_t *node, double x, double y, double *shortestDistance, KDNode_t **closestNode, int *numComparisons) {

    // finish if reached child of a leaf
    if (!node) return;

    // count number of comparisons
    (*numComparisons)++;

    // if a point exactly matches search location
    if (doubleCompare(x, node->key1) == SAME && doubleCompare(y, node->key2) == SAME) {
        *shortestDistance = NO_DISTANCE;
        *closestNode = node;
        return;
    }

    // check if this node is closer than current closest
    double distance = distanceBetween(x, y, node->key1, node->key2);
    if (distance < *shortestDistance) {
        *shortestDistance = distance;
        *closestNode = node;
    }

    // go down the tree to find closest key
    if (node->isKey1) {
        if (x < node->key1) {
            findNearest(node->left, x, y, shortestDistance, closestNode, numComparisons);
            if (fabs(node->key1 - x) < *shortestDistance) findNearest(node->right, x, y, shortestDistance, closestNode, numComparisons);
        }
        else {
            findNearest(node->right, x, y, shortestDistance, closestNode, numComparisons);
            if (fabs(node->key1 - x) < *shortestDistance) findNearest(node->left, x, y, shortestDistance, closestNode, numComparisons);
        }
    } else {
        if (y < node->key2) {
            findNearest(node->left, x, y, shortestDistance, closestNode, numComparisons);
            if (fabs(node->key2 - y) < *shortestDistance) findNearest(node->right, x, y, shortestDistance, closestNode, numComparisons);
        }
        else {
            findNearest(node->right, x, y, shortestDistance, closestNode, numComparisons);
            if (fabs(node->key2 - y) < *shortestDistance) findNearest(node->left, x, y, shortestDistance, closestNode, numComparisons);
        }
    }
}

// function to start the closest neighbour search recursion
KDNode_t *findNearestNeighbour(KDNode_t *node, double searchKey1, double searchKey2, int *numComparisons) {
    double distance = distanceBetween(searchKey1, searchKey2, node->key1, node->key2);
    KDNode_t **closestPoint = &node;
    findNearest(node, searchKey1, searchKey2, &distance, closestPoint, numComparisons);
    return *closestPoint;
}

// recursively find all nodes that are within radius r of key (x, y)
void scanRadius(KDNode_t *node, double x, double y, double r, int *numComparisons, int *numFound, FILE *filePtr) {
    
    // finish if reached child of a leaf
    if (!node) return;

    // incriment number of comparisons
    (*numComparisons)++;

    // check if current node is within radius
    double distance = distanceBetween(x, y, node->key1, node->key2);
    if (distance < r) {
        (*numFound)++;
        printRadiusListToFile(node->data, filePtr, x, y, r);
    }

    // go down the tree to find all keys in radius
    if (node->isKey1) {
        if (x < node->key1) {
            scanRadius(node->left, x, y, r, numComparisons, numFound, filePtr);
            if (fabs(node->key1 - x) < r) scanRadius(node->right, x, y, r, numComparisons, numFound, filePtr);
        }
        else {
            scanRadius(node->right, x, y, r, numComparisons, numFound, filePtr);
            if (fabs(node->key1 - x) < r) scanRadius(node->left, x, y, r, numComparisons, numFound, filePtr);
        }
    } else {
        if (y < node->key2) {
            scanRadius(node->left, x, y, r, numComparisons, numFound, filePtr);
            if (fabs(node->key2 - y) < r) scanRadius(node->right, x, y, r, numComparisons, numFound, filePtr);
        }
        else {
            scanRadius(node->right, x, y, r, numComparisons, numFound, filePtr);
            if (fabs(node->key2 - y) < r) scanRadius(node->left, x, y, r, numComparisons, numFound, filePtr);
        }
    }
}

// function to start the range search recursive operation
void radiusSearch(KDNode_t *root, double x, double y, double r, FILE *filePtr) {
    
    int numComparisons = INITIAL_VALUE;
    int numFound = INITIAL_VALUE;

    scanRadius(root, x, y, r, &numComparisons, &numFound, filePtr);

    // print results to file and number of nodes visited to stdout
    if (!numFound) printNotFoundToFile(x, y, r, filePtr);
    printf("%.6f %.6f %.6f --> %d\n", x, y, r, numComparisons);
}