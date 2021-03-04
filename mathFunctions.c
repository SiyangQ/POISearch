/* mathFunctions.c
*
* Created by Siyang Qiu (siyangq@student.unimelb.edu.au) 14/Sep./2020
*
* support math functions. 
* 
* functions: compare two doubles and calculate abs distance between two
* coordinates
*
*/

#include "mathFunctions.h"

#define SAME 0
#define LESS_THAN -1
#define GREATER_THAN 1
#define SQUARED 2

// compare two doubles, return 0 if equal
int doubleCompare(double a, double b) {

    if (fabs(a-b) < EPSILON) return 0;
    else if ((a-b) > 0) return GREATER_THAN;
    return LESS_THAN;
}

// calculate distance between two points
double distanceBetween(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2-x1, SQUARED) + pow(y2-y1, SQUARED));
}