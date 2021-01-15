/*
 * Simple test using Unity test framework written by Pedro Rebello
 */
#include <stdio.h>
#include <string.h>

#include "unity.h"
#include "persistence.h"
#include "Entity.h"
#include "list.h"

/* Function Declarations */
void setUp (void);
void tearDown (void);
void test_OpenFileCorrectName(void);
void test_OpenFileWrongName(void);
void test_sortList(void);

/* Function Implementations */

/*
 * main function - call all tests
 */
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_OpenFileCorrectName);
    RUN_TEST(test_OpenFileWrongName);
    RUN_TEST(test_sortList);
    return UNITY_END();
}

/*
 * test_OpenFileCorrectName
 * test getListFromFile() return opening an existing file
 */
void test_OpenFileCorrectName(void)
{
    Node *list = NULL;
    TEST_ASSERT_EQUAL_HEX8(1, getListFromFile(&list, "testfile.txt"));
}

/*
 * test_OpenFileWrongName
 * test getListFromFile() return opening an inexisting file
 */
void test_OpenFileWrongName(void)
{
    Node *list = NULL;
    TEST_ASSERT_EQUAL_HEX8(0, getListFromFile(&list, "wrongname.txt"));
}

/*
 * test_sortList
 * test list_sort() if it returns a sorted list
 */
void test_sortList(void) {
    Node* list = NULL;
    Row row;
    char orderedCasesArray[10][10];
    char casesArray[] = {2, 5, 1, 3, 7, 8, 6, 4, 9, 0};
    for(int i = 0; i < 10; i++) {
        strcpy(row.id, "");
        strcpy(row.date, "");
        strcpy(row.deaths, "");
        strcpy(row.name_fr, "");
        strcpy(row.name_en, "");
        sprintf(row.cases, "%d", casesArray[i]);

        sprintf(orderedCasesArray[i], "%d", i);

        list_add(&list, row, 0);
    }

    list = list_sort(list);

    for(int i = 0; i < 10; i++) {
        list_get(&row, list, i);
        TEST_ASSERT_EQUAL_STRING(orderedCasesArray[i], row.cases);
    }
}

void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */