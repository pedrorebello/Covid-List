#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "persistence.h"
#include "entity.h"

/* Function Declarations */
void readFile(void);
Row createRow(char line[]);


/* Function Implementations */
int getListFromFile(Node **list, char *fileName) {
    FILE *file;
      
    char line[150];

    file = fopen(fileName, "r");

    if (file) {
        list_removeAll(list);
        
        /* Skip First Line */
        fgets(line, 150, file);
        
        int i = 0;
        while (fgets(line, 150, file) && i < MAX_ROWS) {
            
            /* If line not empty */
            if(strlen(line)>1){
                list_add(list, createRow(line), 0);
            }
            
            i++;
        }

        fclose(file);
        return 1;

    } else {
        return 0;
    }
}

int writeListToFile(Node *list, char *oldFileName, char *newFileName) {
    FILE *file, *newFile;
    int c;
    char line[150];

    file = fopen(oldFileName, "r");
    newFile = fopen(newFileName, "w");

    if (file && newFile) {
        Row row;
        int i = 0;
        
        /* Add header to new file */
        fgets(line, 150, file);
        fputs(line, newFile);
        fclose(file);

        while (list_get(&row, list, i)) {
            
            fputs(row.id, newFile);
            fputs(",", newFile);
            fputs(row.date, newFile);
            fputs(",", newFile);
            fputs(row.cases, newFile);
            fputs(",", newFile);
            fputs(row.deaths, newFile);
            fputs(",", newFile);
            fputs(row.name_fr, newFile);
            fputs(",", newFile);
            fputs(row.name_en, newFile);
            fputs("\n", newFile);
            
            i++;
        }

        fclose(newFile);
        return 1;

    } else {
        return 0;
    }
}

Row createRow(char line[]) {
    Row row;
    char s[2] = ",";

    strcpy(row.id, strtok(line, s));
    strcpy(row.date, strtok(NULL, s));
    strcpy(row.cases, strtok(NULL, s));
    strcpy(row.deaths, strtok(NULL, s));
    strcpy(row.name_fr, strtok(NULL, s));
    strcpy(row.name_en, strtok(NULL, s));
    
    /* Remove new line from the end of string */
    row.name_en[strlen(row.name_en) - 1] = '\0';
    
    return row;
}