/*
Simple file access program written in C by Pedro Mar Rebello
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "entity.h"
#include "logic.h"

/* Function Declarations */
void printHeader(void);
char displayMenu(void);
void optionLoadFile(void);
void optionSaveFile(void);
void optionPrintList(void);
void optionShowRow(void);
void optionEditRow(void);
void optionAddRow(void);
void optionRemoveRow(void);
void optionOrderList(void);
int optionQuit(void);
void printRow(Row row);
int getIntFromCmd(int *i);
int getStrFromCmd(char *str, int size);
void getCharFromCmd(char *c);

/* Global constants*/
#define ROW_PATTERN "%4s %12s %11s %11s %41s %41s\n"
const Row COL_NAMES = {"id", "date", "cases", "deaths", "name_fr", "name_en"};
#define ORIGN_FILE "InternationalCovid19Cases.csv"
#define NEW_FILE "InternationalCovid19CasesEDITED.csv"


int main() {
    char opt;

    int run = 1;
    do {
        opt = displayMenu();
        
        switch(opt)
        {
            case 'l':
            case 'L':
                optionLoadFile();
                break;

            case 'p':
            case 'P':
                optionPrintList();
                break;

            case 'q':
            case 'Q':
                run = optionQuit();
                break;
            
            case 's':
            case 'S':
                optionSaveFile();
                break;
            
            case 'o':
            case 'O':
                optionOrderList();
                break;
            
            case 'r':
            case 'R':
                optionShowRow();
                break;
            
            case 'e':
            case 'E':
                optionEditRow();
                break;
            
            case 'a':
            case 'A':
                optionAddRow();
                break;
            
            case 'd':
            case 'D':
                optionRemoveRow();
                break;
            
            default:
                printf("Invalid Option.\n\n");
        }

    } while(run);
   
    return 0;
}

/* Processes Load From File menu option */
void optionLoadFile(void) {
    char opt = 'o';
    char *fileName;

    printf("Chose the file you would like to open:\n");
    printf("\tO: Original dataset\n");
    printf("\tS: Saved List\n");
    printf("> ");

    getCharFromCmd(&opt);

    switch(opt){
        case 'o':
        case 'O':
            fileName = ORIGN_FILE;
            break;

        case 's':
        case 'S':
            fileName = NEW_FILE;
            break;

        default:
            printf("\nOption Invalid.\n");
            return;
    }

    if(!loadList(fileName)) {
        printf("\nError Opening File\n");
    } else {
        printf("\nList loaded from file\n");
    }
}

void optionOrderList(void) {
    printf("0: ID\n");
    printf("1: DATE 1\n");
    printf("2: CASES 2\n");
    printf("3: DEATHS 3\n");
    printf("4: NAME_FR 4\n");
    printf("5: NAME_EN 5\n");
    printf("Select the column you whant to order: ");
    int opt;
    getIntFromCmd(&opt);
    
    sortlist(opt);
}

/* Processes Save On File menu option */
void optionSaveFile(void) {
    if(!saveList(ORIGN_FILE, NEW_FILE)) {
        printf("\nError Saving File.\n");
    } else {
        printf("\nList Saved to %s file\n", NEW_FILE);
    }
}

/* Processes Print Row menu option */
void optionShowRow(void) {
    printf("Enter row number: ");

    int num;
    if(getIntFromCmd(&num)) {
        Row row;
        if(getRow(&row, num)) {
            printHeader();
            printRow(row);
        } else {
            printf("\nThere is no row with that number.\n");
        }
    } else {
        printf("\nInvalid entry.\n");
    }
}

/*  Listens user input.
    Returns a int */
int getIntFromCmd(int *i){
    int rowNumber;
    int result = scanf("%d", i);
    fflush(stdin);
    if(result != 1) {
        result = 0;
    }
    return result;
}

/*  Listens user input.
    Returns a string */
int getStrFromCmd(char *str, int size){

    fgets(str, size, stdin);
    fflush(stdin); 

    if(str != NULL) {
        int pos = strlen(str) - 1;
        if (str[pos] == '\n')
            str[pos] = '\0';

        return 1;
    } else {
        return 0;
    }
}

/*  Listens user input.
    Returns a char */
void getCharFromCmd(char *c){
    *c = getchar();
    /* Flush residual imput if present */
    fflush(stdin);
}

/* Processes Edit Row menu option */
void optionEditRow(void) {
    printf("Enter row number: ");

    int num;
    if(getIntFromCmd(&num)) {
        Row row;
        if(getRow(&row, num)) {
            
            printf("Enter ID: ");
            getStrFromCmd(row.id, 3);
            printf("Enter DATE: ");
            getStrFromCmd(row.date, 11);
            printf("Enter CASES: ");
            getStrFromCmd(row.cases, 10);
            printf("Enter DEATHS: ");
            getStrFromCmd(row.deaths, 10);
            printf("Enter NAME_FR: ");
            getStrFromCmd(row.name_fr, 40);
            printf("Enter NAME_EN: ");
            getStrFromCmd(row.name_en, 40);

            if(editRow(num, row))
                printf("\nRow edited.\n");
            else
                printf("\nFailed to edit row.\n");
            
        } else {
            printf("\nThere is no row with that number.\n");
        }
    } else {
        printf("\nInvalid entry.\n");
    }
}

/* Processes Add Row menu option */
void optionAddRow(void) {
    Row row;
    printf("Enter ID: ");
    getStrFromCmd(row.id, 3);
    printf("Enter DATE: ");
    getStrFromCmd(row.date, 11);
    printf("Enter CASES: ");
    getStrFromCmd(row.cases, 10);
    printf("Enter DEATHS: ");
    getStrFromCmd(row.deaths, 10);
    printf("Enter NAME_FR: ");
    getStrFromCmd(row.name_fr, 40);
    printf("Enter NAME_EN: ");
    getStrFromCmd(row.name_en, 40);

    if(addRow(row))
        printf("\nRow added.\n");
    else
        printf("\nFailed to add row.\n");
    
}

/* Process Delete Row menu option */
void optionRemoveRow(void) {
    printf("Enter row number: ");

    int num;
    if(getIntFromCmd(&num)) {
        Row row;
        if(getRow(&row, num)) {
            if(deleteRow(num))
                printf("\nRow deleted.\n");
            else
                printf("\nFailed to delete row.\n");
            
        } else {
            printf("\nThere is no row with that number.\n");
        }
    } else {
        printf("\nInvalid entry.\n");
    }
}

/*  Processes Quit menu option.
    Returns quit flag value*/
int optionQuit(void) {
    printf("Good bye!\n\n");
    return 0;
}

/*  Prints menu and ask for user imput. 
    Returns user choice */
char displayMenu(void) {
    char opt;

    printf("\tL: Load list from file.\n");
    printf("\tS: Save list to new file.\n");
    printf("\tP: Print list on screen.\n");
    printf("\tR: Print row on screen.\n");
    printf("\tA: Add row.\n");
    printf("\tD: Delete row.\n");
    printf("\tE: Edit row.\n");
    printf("\tO: Order list.\n");
    printf("\tQ: Exit.\n");
    printf("Type the option letter and pres enter: ");
    
    getCharFromCmd(&opt);
    
    printf("\n\n");
    
    return opt;
}

/*  Processes Print List menu option */
void optionPrintList(void) {
    Row row;
    int firstRow = 0;
    int noOfRows = 1000;

    printHeader();

    int i = firstRow;
    while(getRow(&row, i) && i < firstRow + noOfRows) {
        printRow(row);
        i++;
    }
    printf("\n");
}

/* Prints list header on screen */
void printHeader(void) {
    printf(ROW_PATTERN, COL_NAMES.id, COL_NAMES.date, COL_NAMES.cases, COL_NAMES.deaths, COL_NAMES.name_fr, COL_NAMES.name_en);
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
}

/* Prints given row on screen */
void printRow(Row row) {
        printf(ROW_PATTERN, row.id, row.date, row.cases, row.deaths, row.name_fr, row.name_en);
}
