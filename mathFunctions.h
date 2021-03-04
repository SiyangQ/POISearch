/* mathFunctions.h
*
* Created by Siyang Qiu (siyangq@student.unimelb.edu.au) 14/Sep./2020
*
* support math functions. 
* 
* functions: compare two doubles and calculate abs distance between two
* coordinates
*
*/

#ifndef MATHFUNCTIONSH
#define MATHFUNCTIONSH

#include <math.h>

#define EPSILON 0.00000001

int doubleCompare(double a, double b);
double distanceBetween(double x1, double y1, double x2, double y2);

#endif