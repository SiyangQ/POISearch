/* structureCLUE.h
*
* Created by Siyang Qiu (siyangq@student.unimelb.edu.au) 14/Sep./2020
*
* functions that can only be exclusively used by CLUE records
*
* read a CLUE CSV file to a record type struct, then freeing a record type
*
*/

#ifndef STRUCTCLUEH
#define STRUCTCLUEH

#include <stdlib.h>
#include <assert.h>
#include <string.h>

// record struct
typedef struct{

    char *censusYear;
    char *blockID;
    char *propertyID;
    char *basePropertyID;
    char *CLUESmallArea;
    char *tradingName;
    char *industryCode;
    char *industryDescription;
    char *xCoordinate;
    char *yCoordinate;
    char *location;

} record_t;

void deleteRecord(record_t *rec);
void *readCSVLine(char *inputLine);
void *readCSVField(char *input, int *index);
void *KDTreeFromCSVFile(char *fileName);

#endif