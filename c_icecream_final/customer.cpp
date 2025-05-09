#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

void init_queue(Queue* q) {
    q->front = q->rear = 0;
}

int is_empty_queue(Queue* q) {
    return q->front == q->rear;
}

int is_full_queue(Queue* q) {
    return (q->rear + 1) % MAX_CUSTOMER_SIZE == q->front;
}

int enqueue(Queue* q, Customer* cus) {
    if (is_full_queue(q))
        return -1;
    q->rear = (q->rear + 1) % MAX_CUSTOMER_SIZE;
    q->cus[q->rear] = cus;
    return 0;
}

Customer* dequeue(Queue* q) {
    if (is_empty_queue(q))
        return NULL;
    q->front = (q->front + 1) % MAX_CUSTOMER_SIZE;
    return q->cus[q->front];
}

int add_front(Queue* q, Customer* cus) {
    if (is_full_queue(q))
        return -1;
    q->cus[q->front] = cus;
    q->front = (q->front - 1 + MAX_CUSTOMER_SIZE) % MAX_CUSTOMER_SIZE;
    return 0;
}

Customer* delete_rear(Queue* q) {
    int prev = q->rear;
    if (is_empty_queue(q))
        return NULL;
    q->rear = (q->rear - 1 + MAX_CUSTOMER_SIZE) % MAX_CUSTOMER_SIZE;
    return q->cus[prev];
}

ListNode* insert_last(ListNode* tail, Customer* cus)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->cus = cus;

    if (tail == NULL) {
        tail = node;
        node->link = tail;
    }
    else {
        node->link = tail->link;
        tail->link = node;
        tail = node;
    }

    return tail;
}

ListNode* insert_first(ListNode* tail, Customer* cus)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->cus = cus;

    if (tail == NULL) {
        tail = node;
        node->link = tail;
    }
    else {
        node->link = tail->link;
        tail->link = node;
    }

    return tail;
}

ListNode* search_list(ListNode* tail)
{
    ListNode* prev = tail;

    do {
        if (prev == NULL) return NULL;
        if (prev->link->cus->onlyhome == 0) return prev;

        prev = prev->link;
    } while (prev != tail);

    return NULL;
}

ListNode* put_rider_table(Customer* cus, ListNode* tail)
{
    if (cus->vip) {
        tail = insert_first(tail, cus);
    }
    else {
        tail = insert_last(tail, cus);
    }
    return tail;
}

Customer* create_customer() {
    Customer* cus = (Customer*)malloc(sizeof(Customer));
    memset(cus, 0, sizeof(Customer));
    cus->icecream_cup = (Stack*)malloc(sizeof(Stack));
    cus->ingre_count = 0;
    return cus;
}

void init_cup(Stack* cup) {
    cup->capacity = MAX_CUPSIZE;
    cup->top = -1;
    cup->icecream_number = (int*)malloc(sizeof(int) * cup->capacity);
}

int is_full(Stack* cup) {
    return cup->top == (cup->capacity - 1);
}

int is_empty(Stack* cup) {
    return cup->top == -1;
}

void push(int choice, Stack* cup) {
    if (is_full(cup)) {
        cup->capacity *= 2;
        cup->icecream_number = (int*)realloc(cup->icecream_number, sizeof(int) * cup->capacity);
    }
    cup->icecream_number[++cup->top] = choice;
}

int pop(Stack* cup) {
    if (is_empty(cup))
        return -1;
    return cup->icecream_number[cup->top--];
}

const char* get_cook_away(int cook_number)
{
    switch (cook_number) {
    case 0:
        return "º£ÀÌ½º ¸ÀÀÌ °­ÇÏ°Ô";
    case 1:
        return "±ÕÇüÀâÈù ¸ÀÀ¸·Î";
    case 2:
        return "±íÀº ¿©¿îÀÌ ³ª°Ô";
    default:
        return NULL;
    }
}

void pre_order(Customer* cus, TreeNode* root)
{
    if (root) {
        strcpy(cus->order_bingsu[cus->ingre_count], root->name);
        printf("%s ", cus->order_bingsu[cus->ingre_count]);
        cus->ingre_count++;
        pre_order(cus, root->left);
        pre_order(cus, root->right);
    }
}

void in_order(Customer* cus, TreeNode* root)
{
    if (root) {
        pre_order(cus, root->left);
        strcpy(cus->order_bingsu[cus->ingre_count], root->name);
        printf("%s ", cus->order_bingsu[cus->ingre_count]);
        cus->ingre_count++;
        pre_order(cus, root->right);
    }
}

void post_order(Customer* cus, TreeNode* root)
{
    pre_order(cus, root->left);
    pre_order(cus, root->right);
    strcpy(cus->order_bingsu[cus->ingre_count], root->name);
    printf("%s ", cus->order_bingsu[cus->ingre_count]);
    cus->ingre_count++;
}

Customer* delete_first(ListNode** ptail)
{
    ListNode* removed;
    Customer* cus;

    if (*ptail == NULL) {
        return NULL;
    }
    else if (*ptail == (*ptail)->link) {
        removed = *ptail;
        *ptail = NULL;
    }
    else {
        removed = (*ptail)->link;
        (*ptail)->link = removed->link;
    }
    
    cus = removed->cus;
    free(removed);

    return cus;
}

Customer* delete_(ListNode** ptail, ListNode* pre)
{
    ListNode* removed;
    Customer* cus;

    if (*ptail == NULL) {
        removed = *ptail;
        *ptail = NULL;
    }
    else {
        if (pre->link == *ptail) {
            *ptail = pre;
        }
        removed = pre->link;
        pre->link = removed->link;
    }

    cus = removed->cus;
    free(removed);

    return cus;
}
