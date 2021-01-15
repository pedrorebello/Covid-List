/*
 * Simple double linked list written by Pedro Rebello
 */
#include <string.h>
#include <stdio.h>

#include "list.h"

/* Function Declarations */
Node *find(Node *head, int pos);
Node *sort(Node *head, int col);
Node *merge(Node *first, Node *second, int col);
Node *splitListInHalf(Node *head);
Node *splitList(Node *newList);
int stringToInt(char *num);
int compareCol(Row row1, Row row2, int col);
int compareInt(int value1, int value2);


/* Function Implementations */

/*
 * list_size
 * Returns the number of members in the list
 *  *head - head of the list
 * return int with the number of members in the list
 */
int list_size(Node *head) {
    int size = 0;
    Node *node = head;
    while(node != NULL) {
        size++;
        node = node->next;
    }
    return size;
}

/*
 * list_add
 * Adds a new node to a list in the given position
 *  **head - address to the head of the list (head can have a new value if position is 0)
 *  row - data to be added to the list
 *  pos - position of the new list node
 * return 1 on success and zero on fail
 */
int list_add(Node ** head, Row row, int pos)
{
    if(pos == 0) {
        Node *newNode = (Node *) malloc(sizeof(Node));
        newNode->row = row;
        newNode->prev = NULL;
        newNode->next = *head;
        if(newNode->next != NULL)
            newNode->next->prev = newNode;
        *head = newNode;
    } else {
        Node *prevNode = find(*head, pos-1);
        if(prevNode == NULL)
            return 0;
        else {
            Node *newNode = (Node *) malloc(sizeof(Node));
            newNode->row = row;
            newNode->prev = prevNode;
            newNode->next = prevNode->next;
            prevNode->next = newNode;
            if(newNode->next != NULL)
                newNode->next->prev = newNode;
        }
    }
    return 1;
}

/*
 * list_remove
 * Removes a new node from a list in the given position
 *  **head - address to the head of the list (head can have a new value if position is 0)
 *  pos - position of the node to be removed
 * return 1 on success and zero on fail
 */
int list_remove(Node ** head, int pos)
{
    Node *node = find(*head, pos);

    if(node != NULL) {
        if(node->prev != NULL)
            node->prev->next = node->next;
        else
            *head = node->next;

        if(node->next != NULL)
            node->next->prev = node->prev;

        free(node);

        return 1;
    } else {
        return 0;
    }
}

/*
 * list_get
 * Gets data in the given position in a list
 *  *row - address to a row where data will be stored
 *  *head - head of the list
 *  pos - position in the list
 * return 1 on success and zero on fail
 */
int list_get(Row *row, Node *head, int pos)
{
    Node *node = find(head, pos);

    if(node != NULL) {
        *row = node->row;
        return 1;
    } else {
        return 0;
    }
}

/*
 * list_set
 * Replaces data in the given position in a list
 *  *head - head of the list
 *  pos - position in the list
 *  row - new data to replace the one on given position
 * return 1 on success and zero on fail
 */
int list_set(Node *head, int pos, Row row)
{
    Node *node = find(head, pos);

    if(node != NULL) {
        node->row = row;
        return 1;
    } else {
        return 0;
    }
}

/*
 * list_removeAll
 * Removes all nodes from a list
 *  **head - address to the head of the list (head will be replaced by NULL)
 * return 1 on success and zero on fail
 */
int list_removeAll(Node **head)
{
    while(*head != NULL) {
        list_remove(head, 0);
    }
    return 1;
}

/*
 * list_sort
 * Sorts a list by indicated column
 *  **head - address to head of the list (*head can have a new value)
 * return 0 on error, 1 otherwise
 */
int list_sort(Node **head, int col)
{
    if(col < 0 || col > 5) return 0;

    *head = sort(*head, col);

    return 1;
}

/*
 * sort
 * Sorts a list by indicated column
 *  *head - head of the list
 * return new head of the sorted list
 */
Node *sort(Node *head, int col)
{
    Node *secondListHead;

    if (!head || !head->next)
        return head;

    secondListHead = splitListInHalf(head);

    head = sort(head, col);
    secondListHead = sort(secondListHead, col);

    return merge(head, secondListHead, col);
}

/* Helper functions */

/*
 * compare
 * Compare two Rows based on provided column
 * row1, row2 rows to compare
 * col column of the row to compare
 * return >0 if the first is bigger, <0 if the second is bigger and 0 if they are equivalent
 */
int compareCol(Row row1, Row row2, int col) {
    switch(col)
    {
        case COLUMN_ID:
            return strcmp(row1.id, row2.id);
            break;
        case COLUMN_DATE:
            return strcmp(row1.date, row2.date);
            break;
        case COLUMN_CASES:
            return compareInt(stringToInt(row1.cases), stringToInt(row2.cases));
            break;
        case COLUMN_DEATHS:
            return compareInt(stringToInt(row1.deaths), stringToInt(row2.deaths));
            break;
        case COLUMN_NAME_FR:
            return strcmp(row1.name_fr, row2.name_fr);
            break;
        case COLUMN_NAME_EN:
            return strcmp(row1.name_en, row2.name_en);
            break;
    }
}

int compareInt(int value1, int value2) {
    if(value1 > value2) return 1;
    if(value1 < value2) return -1;
    return 0;
}

/*
 * merge
 * merge two ordered lists into a ordered list
 *  *firstList - head of the first ordered list
 *  *secondList - head of the second ordered list
 * return head of the sorted list
 */
Node *merge(Node *firstList, Node *secondList, int col)
{
    if (!firstList)
        return secondList;
    if (!secondList)
        return firstList;

    if (compareCol(firstList->row, secondList->row, col) < 0)
    {
        firstList->next = merge(firstList->next, secondList, col);
        firstList->next->prev = firstList;
        firstList->prev = NULL;
        return firstList;
    } else {
        secondList->next = merge(firstList, secondList->next, col);
        secondList->next->prev = secondList;
        secondList->prev = NULL;
        return secondList;
    }
}

/*
 * splitListInHalf
 * splits a list in half
 *  *head - head of the list to be splited
 * return head of the second list
 */
Node *splitListInHalf(Node *head)
{
    Node *end = head;
    Node *middle = head;

    while (end->next && end->next->next)
    {
        end = end->next->next;
        middle = middle->next;
    }
    middle = middle->next;

    splitList(middle);

    return middle;
}

Node *splitList(Node *newList)
{
    newList->prev->next = NULL;
    newList->prev = NULL;
    return newList;
}

/*
 * find
 * find a lode of a list in the given position
 *  *head - head of the list
 *  pos - position of the node
 * return node in position
 */
Node *find(Node *head, int pos)
{
    Node *currentNode = head;

    int i = 0;
    while(i < pos && currentNode != NULL) {
        currentNode = currentNode->next;
        i++;
    }

    return currentNode;
}

/*
 * stringToInt
 * converts a number written in string to a int value
 *  *num - string with a positive integer
 * returns int with the value in the string
 */
int stringToInt(char *num){
    int size;
    int result = 0;

    size = strlen(num);

    for(int i = 0; i < size; i++){
        result = result * 10 + (num[i] - '0');
    }

    return result;
}
