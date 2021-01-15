#include "logic.h"
#include "persistence.h"
#include "entity.h"

Node *list = NULL;

int loadList(char * fileNAme) {
    return getListFromFile(&list, fileNAme);
}

int saveList(char *oldFile, char *newFile) {
    return writeListToFile(list, oldFile, newFile);
}

int getRow(Row *row, int pos) {
    return list_get(row, list, pos);
}

int deleteRow(int pos) {
    return list_remove(&list, pos);
}

int addRow(Row row) {
    return list_add(&list, row, 0);
}

int editRow(int pos, Row row) {
    return list_set(list, pos, row);
}

int sortlist(int opt) {
    return list_sort(&list, opt);
}

int getListSize(void) {
    return list_size(list);
}
