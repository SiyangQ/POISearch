/* print.h
*
* Created by Siyang Qiu (siyangq@student.unimelb.edu.au) 14/Sep./2020
*
* support print functions to print a CLUE record or NOTFOUND to file,
* and stdout. 
*
*/

#ifndef PRINTH
#define PRINTH

#include <stdio.h>
#include "structureCLUE.h"

void printOutputToStdout(record_t *record);
void printOutputToFile(record_t *record, FILE *filePtr, double *x, double *y);
void printRadiusOutputToFile(record_t *record, FILE *filePtr, double x, double y, double r);
void printNotFoundToFile(double x, double y, double r, FILE *filePtr);
void printNotFoundToStdOut(char *key);

#endif