#ifndef BUSINESS_HEADER
#define BUSINESS_HEADER

#include "entity.h"

/* Function Declarations */
int loadList(char * fileNAme);
int saveList(char *oldFile, char *newFile);
int getRow(Row *row, int pos);
int deleteRow(int pos);
int addRow(Row row);
int editRow(int pos, Row row);
int sortlist(int col);
int getListSize(void);


//void saveList(void);

#endif

