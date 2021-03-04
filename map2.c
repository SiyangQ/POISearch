/* map2.c
*
* Created by Siyang Qiu (siyangq@student.unimelb.edu.au) 14/Sep./2020
*
* range search
* 
* construct a KD tree from a data file, then for every key inputed in stdin,
* output the businesses in a specific range of that key
*
* Run this program using:
* ./map2 dataFile outputFile < keyFile
*
*/

#include "KDTree.h"
#include "structureCLUE.h"
#include "print.h"

#define DATA_FILE_NAME 1
#define OUTPUT_FILE_NAME 2
#define NUM_ELEMENT_IN_KEY 3
#define NUM_ARGC 3
#define FALSE 0
#define TRUE 1

int readKey(double *x, double *y, double *r);

int main(int argc, char *argv[]) {
    
    // check if CLA is correct
    assert(argc == NUM_ARGC);

    // construct KD tree from input file
    KDNode_t *KDRoot = KDTreeFromCSVFile(argv[DATA_FILE_NAME]);

    // open output file to write
    FILE *filePtr = fopen(argv[OUTPUT_FILE_NAME], "w");
    assert(filePtr);

    // receive keys from stdin
    double x, y, r;
    while (readKey(&x, &y, &r)) {
        radiusSearch(KDRoot, x, y, r, filePtr);
    }
    
    // free whole tree
    freeKDTree(KDRoot);

    // close output file
    fclose(filePtr);
}

// read a line of key from stdin
int readKey(double *x, double *y, double *r) {
    if (scanf("%lf %lf %lf", x, y, r) != NUM_ELEMENT_IN_KEY) return FALSE;
    return TRUE;
}