#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "icecream.h"

Icecream*** icecream_tb;
int reverse;

Icecream*** create_icecream_tb(int row, int col)
{
    Icecream*** table = (Icecream***)malloc(sizeof(Icecream**) * row);
    for (int i = 0; i < row; i++)
        table[i] = (Icecream**)malloc(sizeof(Icecream*) * col);
    return table;
}

Icecream* create_icecream()
{
    Icecream* ice = (Icecream*)malloc(sizeof(Icecream));
    memset(ice, 0, sizeof(Icecream));
    return ice;
}

void table_init()
{
    int ice_num = 0;
    icecream_tb = create_icecream_tb(ROW, COL);
    reverse = 0;
    srand(time(NULL));

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            Icecream* ice = create_icecream();
            printf("진열할아이스크림명을입력하세요: ");
            scanf("%s", ice->name);
            ice->number = ice_num++;
            ice->stock = rand() % 5;
            icecream_tb[i][j] = ice;
        }
    }
}

void table_print()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            printf("[주문번호%d: %15s]", icecream_tb[i][j]->number, icecream_tb[i][j]->name);
        }
        printf("\n");
    }
}

void transposed_icecream_tb()
{
    Icecream*** table = create_icecream_tb(COL, ROW);
    reverse = !reverse;

    if (reverse) {
        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
                table[j][i] = icecream_tb[i][j];
    }
    else {
        for (int i = 0; i < COL; i++)
            for (int j = 0; j < ROW; j++)
                table[j][i] = icecream_tb[i][j];
    }

    free(icecream_tb);
    icecream_tb = table;

    int r = reverse ? COL : ROW;
    int c = reverse ? ROW : COL;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            printf("[(%d)%15s]", icecream_tb[i][j]->number, icecream_tb[i][j]->name);
        printf("\n");
    }
}