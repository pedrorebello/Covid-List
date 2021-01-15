#ifndef ROW_STRUCT
#define ROW_STRUCT

typedef struct {
    char id[3];
    char date[11];
    char cases[10];
    char deaths[10];
    char name_fr[40];
    char name_en[40];
} Row;

#endif