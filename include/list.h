#ifndef ROW_LIST_HEADER
#define ROW_LIST_HEADER

#include <stdlib.h>

#include "entity.h"

/* Type Declarations */
typedef struct Node_s {
    Row row;
    struct Node_s *next;
    struct Node_s *prev;
} Node;

/* Constant Declarations */
#define COLUMN_ID 0
#define COLUMN_DATE 1
#define COLUMN_CASES 2
#define COLUMN_DEATHS 3
#define COLUMN_NAME_FR 4
#define COLUMN_NAME_EN 5

/* Function Declarations */
int list_add(Node **head, Row row, int pos);
int list_remove(Node **head, int pos);
int list_get(Row *row, Node *head, int pos);
int list_set(Node *head, int pos, Row row);
int list_removeAll(Node **head);
int list_sort(Node **head, int col);
int list_size(Node *head);


#endif