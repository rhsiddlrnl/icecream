#ifndef ICECREAM_H
#define ICECREAM_H

#define ROW 2
#define COL 3

typedef struct icecream {
    int number;
    char name[15];
    int stock;
} Icecream;

extern Icecream*** icecream_tb;
extern int reverse;

Icecream*** create_icecream_tb(int row, int col);
Icecream* create_icecream();
void table_init();
void table_print();
void transposed_icecream_tb();

#endif
