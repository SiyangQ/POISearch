/* map1.c
*
* Created by Siyang Qiu (siyangq@student.unimelb.edu.au) 14/Sep./2020
*
* closest neighbour search
* 
* construct a KD tree from a data file, then for every key inputed in stdin,
* output the businesses closest to that key
*
* Run this program using:
* ./map1 dataFile outputFile < keyFile
*
*/

#include "KDTree.h"
#include "structureCLUE.h"
#include "print.h"

#define DATA_FILE_NAME 1
#define OUTPUT_FILE_NAME 2
#define MAX_KEY_LINE_LENGTH 128
#define NUM_ARGC 3
#define ONE_CHAR 1
#define FALSE 0
#define TRUE 1

int readKey(double *x, double *y);

int main(int argc, char *argv[]) {
    
    // check if CLA is correct
    assert(argc == NUM_ARGC);

    // construct KD tree from input file
    KDNode_t *KDRoot = KDTreeFromCSVFile(argv[DATA_FILE_NAME]);

    // open output file to write
    FILE *filePtr = fopen(argv[OUTPUT_FILE_NAME], "w");
    assert(filePtr);

    // receive keys from stdin and process the keys
    double x, y;
    while (readKey(&x, &y)) {
        int numComparisons = 0;
        KDNode_t *closest = findNearestNeighbour(KDRoot, x, y, &numComparisons);
        printListToFile(closest->data, filePtr, &x, &y);
        printf("%f %f --> %d\n", x, y, numComparisons);
    
    }
    
    // free whole tree
    freeKDTree(KDRoot);

    // close output file
    fclose(filePtr);
}

// read a line of key from stdin
int readKey(double *x, double *y) {
    char keyBuffer[MAX_KEY_LINE_LENGTH];
    fgets(keyBuffer, MAX_KEY_LINE_LENGTH, stdin);
    
    if (strlen(keyBuffer) <= ONE_CHAR) return FALSE;

    // determine values from keyBuffer
    sscanf(keyBuffer, "%lf %lf\n", x, y);
    return TRUE;
}