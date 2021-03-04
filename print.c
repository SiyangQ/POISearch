/* print.c
*
* Created by Siyang Qiu (siyangq@student.unimelb.edu.au) 14/Sep./2020
*
* support print functions to print a CLUE record or NOTFOUND to file,
* and stdout. 
*
*/

#include "print.h"

// print a record to stdout
void printOutputToStdout(record_t *record) {

    printf("%s %s --> Census year: %s || Block ID: %s || "
        "Property ID: %s || Base property ID: %s || CLUE small area: %s || "
        "Trading Name: %s ||"
        "Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || "
        "x coordinate: %s || y coordinate: %s || Location: %s || \n", 
        record->xCoordinate, record->yCoordinate, record->censusYear, record->blockID,
        record->propertyID, record->basePropertyID, record->CLUESmallArea, 
        record->tradingName, record->industryCode, record->industryDescription, 
        record->xCoordinate, record->yCoordinate, record->location);
}

// print a record to file with keys x y
void printOutputToFile(record_t *record, FILE *filePtr, double *x, double *y) {

    fprintf(filePtr, "%.6f %.6f --> Census year: %s || Block ID: %s || "
        "Property ID: %s || Base property ID: %s || CLUE small area: %s || "
        "Trading Name: %s ||"
        "Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || "
        "x coordinate: %s || y coordinate: %s || Location: %s || \n", 
        *x, *y, record->censusYear, record->blockID,
        record->propertyID, record->basePropertyID, record->CLUESmallArea, 
        record->tradingName, record->industryCode, record->industryDescription, 
        record->xCoordinate, record->yCoordinate, record->location);
}

// print a record to file with keys x y r
void printRadiusOutputToFile(record_t *record, FILE *filePtr, double x, double y, double r) {

    fprintf(filePtr, "%.6f %.6f %.6f --> Census year: %s || Block ID: %s || "
        "Property ID: %s || Base property ID: %s || CLUE small area: %s || "
        "Trading Name: %s ||"
        "Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || "
        "x coordinate: %s || y coordinate: %s || Location: %s || \n", 
        x, y, r, record->censusYear, record->blockID,
        record->propertyID, record->basePropertyID, record->CLUESmallArea, 
        record->tradingName, record->industryCode, record->industryDescription, 
        record->xCoordinate, record->yCoordinate, record->location);
}

// print a not found to file
void printNotFoundToFile(double x, double y, double r, FILE *filePtr) {
    fprintf(filePtr, "%.6f %.6f %.6f --> NOTFOUND \n\n", x, y, r);
}

// print a not found to stdout
void printNotFoundToStdOut(char *key) {
    printf("%s --> NOTFOUND \n", key);
}