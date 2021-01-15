#ifndef DATA_HEADER
#define DATA_HEADER

#include "list.h"
#include "entity.h"

/* Global constants */
#define MAX_ROWS 1000

/* Function Declarations */
int getListFromFile(Node **list, char *fileName);
int writeListToFile(Node *list, char *oldFile, char *newFile);

#endif