#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "icecream.h"
#include "owner.h"

int order_count = 0;
//TreeNode ddalgichung = { "딸기청", NULL, NULL };
//TreeNode whiping = { "휘핑", NULL,NULL };
//TreeNode chocochip = { "초코칩", NULL, NULL };
//TreeNode nuts = { "견과류", NULL, NULL };
//
//TreeNode strawberry = { "딸기", &ddalgichung, &whiping };
//TreeNode chocolate = { "초코", &chocochip, &nuts };
//
//TreeNode milk = { "우유", &strawberry, &chocolate };
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

    strcpy(ingre1->name, "딸기청");
    ingre1->left = NULL;
    ingre1->right = NULL;
    strcpy(ingre2->name, "휘핑");
    ingre2->left = NULL;
    ingre2->right = NULL;
    strcpy(ingre3->name, "초코칩");
    ingre3->left = NULL;
    ingre3->right = NULL;
    strcpy(ingre4->name, "견과류");
    ingre4->left = NULL;
    ingre4->right = NULL;
    strcpy(ingre5->name, "딸기");
    ingre5->left = ingre1;
    ingre5->right = ingre2;
    strcpy(ingre6->name, "초코");
    ingre6->left = ingre3;
    ingre6->right = ingre4;
    strcpy(ingre7->name, "우유");
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
    printf("나: 오케이! 이번 주문으로 %d원, 총 %d원을 벌었어!\n", income, ice_owner->total_income);
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
    printf("사장: 고객님주문받겠습니다.\n");

    cus->bingsu_menu = rand() % MAX_COOK_BINGSU;
    Sleep(1000);
    printf("고객: 저 빙수 %s 만들어 주세요...\n", get_cook_away(cus->bingsu_menu));
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



    printf("고객: 저cupsize%d으로", cus->cup_size);

    for (int i = 0; i < cus->cup_size; i++) {
        int ice_num = rand() % (ROW * COL);
        int row = reverse ? ice_num % COL : ice_num / COL;
        int col = reverse ? ice_num / COL : ice_num % COL;
        cus->order[i] = ice_num;
        printf("%s, ", icecream_tb[row][col]->name);
    }
    printf("순서로 쌓아주세요\n");

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
            printf("고객: 너무 오래 기다리네요. 주문 취소할게요\n");
    }*/

    Customer* cus = dequeue(ice_owner->q);
    if (cus == NULL) {
        return -1;
    }

    //bingsu
    printf("사장: 빙수부터 만들어야겠다. %s으로 빙수를 만들어달라고 하셨네...\n", get_cook_away(cus->bingsu_menu));
    printf("사장: 빙수 재료는 우유, 딸기, 초코, 딸기청, 휘핑, 초코칩, 견과류가 있으니깐\n");

    for (int i = 0; i < NUM_OF_INGREDIENT; i++) {
        printf("재료 이름: ");
        scanf("%s", cus->bingsu_make[i]);
    }
    printf("이 순서대로 재료를 넣으면 되겠다!!");




    Stack* cup = cus->icecream_cup;
    init_cup(cup);

    int cupsize = -1;
    printf("나: 손님이 고른 컵사이즈가 뭐였더라?\n");
    scanf("%d", &cupsize);

    for (int i = 0; i < cupsize; i++) {
        int choice;
        printf("나: 몇 번 아이스크림을 쌓아야하지?\n");
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
//            printf("고객: 내가 주문한 아이스크림 어따 팔아먹었어!\n");
//            penalty++;
//        }
//        else if (num == cus->order[i]) {
//            printf("고객: 우마이~ 그래그래 이 순서지.\n");
//        }
//        else {
//            printf("고객: 아니야! 이순서가 아니라고!\n");
//            penalty++;
//        }
//    }
//
//    if (cus->icecream_cup->top > -1) {
//        penalty += (cus->icecream_cup->top + 1);
//        printf("고객: 공짜 아이스크림? 누굴 거지로 아나!\n");
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
    printf("배달 시작~\n");
    if (cus->onlyhome == 0) {
        printf("오잉 한집배달이 아니네\n");
        while (rider->count < MAX_DELIVERY_COUNT) {
            prev = search_list(ice_owner->tail);
            if (prev != NULL) {
                cus = delete_(&(ice_owner->tail), prev);
                rider->tail = insert_last(rider->tail, cus);
                rider->count++;
                printf("가는김에 한탕 더 뛰어야지\n");
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
        printf("[vip %d onlyhome %d]주문번호 %d 고객님 아이스크림 배달왔습니다.\n", cus->vip, cus->onlyhome, cus->order_num);

        printf("빙수는 잘 만들었는지 볼까\n");
        for (int i = 0; i < NUM_OF_INGREDIENT; i++) {
            if (strcmp(cus->bingsu_make[i], cus->order_bingsu[i]) != 0) {
                penalty++;
                printf("고객: 왜 내가 주문한 방법으로 빙수를 만들지 않은거야!\n");
            }
            else {
                printf("고객: 굿 빙수 잘만드네.\n");
            }
        }


        printf("아이스크림 맛도 봐볼까?\n");
        for (int i = cus->cup_size; i--;) {
            int num = pop(cus->icecream_cup);
            if (num == -1) {
                printf("고객: 내가 주문한 아이스크림 어따 팔아먹었어!\n");
                penalty++;
            }
            else if (num == cus->order[i]) {
                printf("고객: 우마이~ 그래그래 이 순서지.\n");
            }
            else {
                printf("고객: 아니야! 이순서가 아니라고!\n");
                penalty++;
            }
        }

        if (cus->icecream_cup->top > -1) {
            penalty += (cus->icecream_cup->top + 1);
            printf("고객: 공짜 아이스크림? 누굴 거지로 아나!\n");
        }

        cal_sales(ice_owner, cus->cup_size, penalty);
        rider->count--;
        Sleep(1000);
    }
}
