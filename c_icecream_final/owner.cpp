#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "icecream.h"
#include "owner.h"

int order_count = 0;
//TreeNode ddalgichung = { "����û", NULL, NULL };
//TreeNode whiping = { "����", NULL,NULL };
//TreeNode chocochip = { "����Ĩ", NULL, NULL };
//TreeNode nuts = { "�߰���", NULL, NULL };
//
//TreeNode strawberry = { "����", &ddalgichung, &whiping };
//TreeNode chocolate = { "����", &chocochip, &nuts };
//
//TreeNode milk = { "����", &strawberry, &chocolate };
//
//TreeNode* bingsu_num = &milk;
TreeNode* bingsu_num;

void bingsu_menu_init()
{
    TreeNode* ingre1, * ingre2, * ingre3, * ingre4, * ingre5, * ingre6, * ingre7;
    ingre1 = (TreeNode*)malloc(sizeof(TreeNode));
    ingre2 = (TreeNode*)malloc(sizeof(TreeNode));
    ingre3 = (TreeNode*)malloc(sizeof(TreeNode));
    ingre4 = (TreeNode*)malloc(sizeof(TreeNode));
    ingre5 = (TreeNode*)malloc(sizeof(TreeNode));
    ingre6 = (TreeNode*)malloc(sizeof(TreeNode));
    ingre7 = (TreeNode*)malloc(sizeof(TreeNode));

    strcpy(ingre1->name, "����û");
    ingre1->left = NULL;
    ingre1->right = NULL;
    strcpy(ingre2->name, "����");
    ingre2->left = NULL;
    ingre2->right = NULL;
    strcpy(ingre3->name, "����Ĩ");
    ingre3->left = NULL;
    ingre3->right = NULL;
    strcpy(ingre4->name, "�߰���");
    ingre4->left = NULL;
    ingre4->right = NULL;
    strcpy(ingre5->name, "����");
    ingre5->left = ingre1;
    ingre5->right = ingre2;
    strcpy(ingre6->name, "����");
    ingre6->left = ingre3;
    ingre6->right = ingre4;
    strcpy(ingre7->name, "����");
    ingre7->left = ingre5;
    ingre7->right = ingre6;

    bingsu_num = ingre7;
}

void owner_init(Owner* ice_owner)
{
    for (int i = 0; i < MAX_CUPSIZE; i++)
        ice_owner->price_of_cupsize[i] = (i + 1) * 100;

    ice_owner->total_income = 0;
    
    ice_owner->q = (Queue*)malloc(sizeof(Queue));
    init_queue(ice_owner->q);



    Queue* q = (Queue*)malloc(sizeof(Queue));
    memset(q, 0, sizeof(Queue));
    init_queue(q);
    ice_owner->q = q;
    ice_owner->tail = NULL;
}

void cal_sales(Owner* ice_owner, int cupsize, int penalty)
{
    int income = ice_owner->price_of_cupsize[cupsize - 1];
    income -= penalty;
    ice_owner->total_income += income;
    printf("��: ������! �̹� �ֹ����� %d��, �� %d���� ������!\n", income, ice_owner->total_income);
}

int get_order(Owner* ice_owner)
{
    //int ret = is_full_queue(ice_owner->q);

    //if (ret == 1) {
    //    return -1;
    //}

    Customer* cus = create_customer();
    cus->order_num = order_count++;

    Sleep(1000);
    srand(time(NULL));
    printf("����: �����ֹ��ްڽ��ϴ�.\n");

    cus->bingsu_menu = rand() % MAX_COOK_BINGSU;
    Sleep(1000);
    printf("��: �� ���� %s ����� �ּ���...\n", get_cook_away(cus->bingsu_menu));
    if (cus->bingsu_menu == 0) {
        pre_order(cus, bingsu_num);
    }
    if (cus->bingsu_menu == 1) {
        in_order(cus, bingsu_num);
    }
    if (cus->bingsu_menu == 2) {
        post_order(cus, bingsu_num);
    }
    printf("\n");


    cus->cup_size = (rand() % MAX_CUPSIZE) + 1;

    cus->vip = (rand() % 2);
    Sleep(1000);
    cus->onlyhome = (rand() % 2);



    printf("��: ��cupsize%d����", cus->cup_size);

    for (int i = 0; i < cus->cup_size; i++) {
        int ice_num = rand() % (ROW * COL);
        int row = reverse ? ice_num % COL : ice_num / COL;
        int col = reverse ? ice_num / COL : ice_num % COL;
        cus->order[i] = ice_num;
        printf("%s, ", icecream_tb[row][col]->name);
    }
    printf("������ �׾��ּ���\n");

    int ret = enqueue(ice_owner->q, cus);
    if (ret == -1) {
        free(cus);
        return -1;
    }
    return 0;
}

void rider_init(Rider* rider)
{
    rider->count = 0;
    rider->tail = NULL;
}

int prepare_order(Owner* ice_owner)
{
    /*if (rand() % 4 == 0) {
        Customer* cancel = delete_rear(ice_owner->q);
        if (cancel != NULL)
            printf("��: �ʹ� ���� ��ٸ��׿�. �ֹ� ����ҰԿ�\n");
    }*/

    Customer* cus = dequeue(ice_owner->q);
    if (cus == NULL) {
        return -1;
    }

    //bingsu
    printf("����: �������� �����߰ڴ�. %s���� ������ �����޶�� �ϼ̳�...\n", get_cook_away(cus->bingsu_menu));
    printf("����: ���� ���� ����, ����, ����, ����û, ����, ����Ĩ, �߰����� �����ϱ�\n");

    for (int i = 0; i < NUM_OF_INGREDIENT; i++) {
        printf("��� �̸�: ");
        scanf("%s", cus->bingsu_make[i]);
    }
    printf("�� ������� ��Ḧ ������ �ǰڴ�!!");




    Stack* cup = cus->icecream_cup;
    init_cup(cup);

    int cupsize = -1;
    printf("��: �մ��� �� �Ż���� ��������?\n");
    scanf("%d", &cupsize);

    for (int i = 0; i < cupsize; i++) {
        int choice;
        printf("��: �� �� ���̽�ũ���� �׾ƾ�����?\n");
        scanf("%d", &choice);
        push(choice, cup);
    }

    ice_owner->tail = put_rider_table(cus, ice_owner->tail);

    //int penalty = delivery_order(cus);
    //cal_sales(ice_owner, cus->cup_size, penalty);
    return 0;
}

//int delivery_order(Customer* cus)
//{
//    int penalty = 0;
//
//    for (int i = cus->cup_size; i--;) {
//        int num = pop(cus->icecream_cup);
//        if (num == -1) {
//            printf("��: ���� �ֹ��� ���̽�ũ�� ��� �ȾƸԾ���!\n");
//            penalty++;
//        }
//        else if (num == cus->order[i]) {
//            printf("��: �츶��~ �׷��׷� �� ������.\n");
//        }
//        else {
//            printf("��: �ƴϾ�! �̼����� �ƴ϶��!\n");
//            penalty++;
//        }
//    }
//
//    if (cus->icecream_cup->top > -1) {
//        penalty += (cus->icecream_cup->top + 1);
//        printf("��: ��¥ ���̽�ũ��? ���� ������ �Ƴ�!\n");
//    }
//
//    return penalty;
//}

int rider_pickup(Owner* ice_owner, Rider* rider)
{
    Customer* cus = delete_first(&(ice_owner->tail));
    ListNode* prev;
    if (cus == NULL) {
        return -1;
    }

    rider->tail = insert_last(rider->tail, cus);
    rider->count++;
    printf("------------------------------------------------------------\n");
    printf("��� ����~\n");
    if (cus->onlyhome == 0) {
        printf("���� ��������� �ƴϳ�\n");
        while (rider->count < MAX_DELIVERY_COUNT) {
            prev = search_list(ice_owner->tail);
            if (prev != NULL) {
                cus = delete_(&(ice_owner->tail), prev);
                rider->tail = insert_last(rider->tail, cus);
                rider->count++;
                printf("���±迡 ���� �� �پ����\n");
            }
            else {
                break;
            }
        }
    }
    return 1;
}

void delivery_order(Owner* ice_owner, Rider* rider)
{
    int ice_num;
    int penalty = 0;
    Customer* cus;

    while (rider->count > 0) {
        cus = delete_first(&(rider->tail));

        printf("------------------------------------------------------------\n");
        printf("[vip %d onlyhome %d]�ֹ���ȣ %d ���� ���̽�ũ�� ��޿Խ��ϴ�.\n", cus->vip, cus->onlyhome, cus->order_num);

        printf("������ �� ��������� ����\n");
        for (int i = 0; i < NUM_OF_INGREDIENT; i++) {
            if (strcmp(cus->bingsu_make[i], cus->order_bingsu[i]) != 0) {
                penalty++;
                printf("��: �� ���� �ֹ��� ������� ������ ������ �����ž�!\n");
            }
            else {
                printf("��: �� ���� �߸����.\n");
            }
        }


        printf("���̽�ũ�� ���� ������?\n");
        for (int i = cus->cup_size; i--;) {
            int num = pop(cus->icecream_cup);
            if (num == -1) {
                printf("��: ���� �ֹ��� ���̽�ũ�� ��� �ȾƸԾ���!\n");
                penalty++;
            }
            else if (num == cus->order[i]) {
                printf("��: �츶��~ �׷��׷� �� ������.\n");
            }
            else {
                printf("��: �ƴϾ�! �̼����� �ƴ϶��!\n");
                penalty++;
            }
        }

        if (cus->icecream_cup->top > -1) {
            penalty += (cus->icecream_cup->top + 1);
            printf("��: ��¥ ���̽�ũ��? ���� ������ �Ƴ�!\n");
        }

        cal_sales(ice_owner, cus->cup_size, penalty);
        rider->count--;
        Sleep(1000);
    }
}
