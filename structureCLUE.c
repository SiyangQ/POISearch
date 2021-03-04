/* structureCLUE.c
*
* Created by Siyang Qiu (siyangq@student.unimelb.edu.au) 14/Sep./2020
*
* functions that can only be exclusively used by CLUE records
*
* read a CLUE CSV file to a record type struct, then freeing a record type
*
*/

#include "structureCLUE.h"
#include "KDTree.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_STRING_LENGTH 128
#define MAX_LINE_LENGTH 512
#define ONE_CHAR 1
#define FIRST_ELEMENT 0
#define FIRST_CHAR 0
#define ONE 1

// read CSV file and construct a KD tree with the coordinates
void *KDTreeFromCSVFile(char *fileName) {
    FILE *filePtr = fopen(fileName, "r");
    assert(filePtr);

    char lineBuffer[MAX_LINE_LENGTH];

    /* skip first line */
    fgets(lineBuffer, MAX_LINE_LENGTH, filePtr);

    // read data into dictionary
    KDNode_t *rootKD = NULL;
    record_t *newRecord;
    double key1, key2;
    while (fgets(lineBuffer, MAX_LINE_LENGTH, filePtr)) {
        newRecord = readCSVLine(lineBuffer);
        key1 = atof(newRecord->xCoordinate);
        key2 = atof(newRecord->yCoordinate);
        rootKD = KDTreeInsert(rootKD, newRecord, key1, key2);
    }

    /* close data file */
    fclose(filePtr);
    
    return rootKD;
}

// read a line of csv file and store in a record type struct
void *readCSVLine(char *inputLine) {
    // create space for a new record
    record_t *newRecord = (record_t *)malloc(sizeof(record_t));
    assert(newRecord);
    int lineIndex = FIRST_CHAR;

    // read each field of record and store in struct
    newRecord->censusYear = readCSVField(inputLine, &lineIndex);
    newRecord->blockID = readCSVField(inputLine, &lineIndex);
    newRecord->propertyID = readCSVField(inputLine, &lineIndex);
    newRecord->basePropertyID = readCSVField(inputLine, &lineIndex);
    newRecord->CLUESmallArea = readCSVField(inputLine, &lineIndex);
    newRecord->tradingName = readCSVField(inputLine, &lineIndex);
    newRecord->industryCode = readCSVField(inputLine, &lineIndex);
    newRecord->industryDescription = readCSVField(inputLine, &lineIndex);
    newRecord->xCoordinate = readCSVField(inputLine, &lineIndex);
    newRecord->yCoordinate = readCSVField(inputLine, &lineIndex);
    newRecord->location = readCSVField(inputLine, &lineIndex);

    return newRecord;
}

// read a , separated field of csv field
void *readCSVField(char *input, int *index) {

    int i = FIRST_CHAR, previousCharIsQuote = FALSE, isQuoted = FALSE;
    char outputBuffer[MAX_STRING_LENGTH];

    // check if quoted string
    if (input[*index] == '"') {
        (*index)++;
        isQuoted = TRUE;
    }

    // copy character to buffer until end of field
    while (input[*index] != '\r' && input[*index] != '\0' && 
        input[*index] != '\n') {
            
        if (input[*index] == ',' && !isQuoted) {
            (*index)++;
            break;
        } else if (input[*index] == '"') {
            if (!previousCharIsQuote) {
                (*index)++;
                previousCharIsQuote = TRUE;
                isQuoted = FALSE;
                continue;
            } else {
                previousCharIsQuote = FALSE;
                isQuoted = TRUE;
            }
        }
        outputBuffer[i++] = input[*index];
        (*index)++;
    }
    outputBuffer[i] = '\0';
    
    // copy string from buffer to a new suitable sized location
    char *newStr = (char *)malloc(sizeof(char)*strlen(outputBuffer)+ONE);
    assert(newStr);
    strcpy(newStr, outputBuffer);

    return newStr;
}

// free all data in a record type struct
void deleteRecord(record_t *rec) {
    free(rec->censusYear);
    free(rec->blockID);
    free(rec->propertyID);
    free(rec->basePropertyID);
    free(rec->CLUESmallArea);
    free(rec->tradingName);
    free(rec->industryCode);
    free(rec->industryDescription);
    free(rec->xCoordinate);
    free(rec->yCoordinate);
    free(rec->location);
    free(rec);
}