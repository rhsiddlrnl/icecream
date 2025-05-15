#ifndef CUSTOMER_H
#define CUSTOMER_H

#define MAX_CUPSIZE 5
#define MAX_CUSTOMER_SIZE 5
#define MAX_COOK_BINGSU 3       //만드는 방법 종류 ex)베이스 맛이 강하게, 균형잡힌 맛으로, 깊은 여운이 나게
#define NUM_OF_INGREDIENT 7     //트리에 들어가는 재료의 수

typedef struct {
    int* icecream_number;
    int capacity;
    int top;
} Stack;

typedef struct customer {
    int cup_size;
    int order[MAX_CUPSIZE];
    int order_num;
    int vip;
    int onlyhome;
    int ingre_count;
    int bingsu_menu;
    char order_bingsu[NUM_OF_INGREDIENT][100];      //주문을 저장하는 변수
    char bingsu_make[NUM_OF_INGREDIENT][100];       //주문대로 만든 빙수를 저장하는 변수       2개 비교해서 점수
    Stack* icecream_cup;
} Customer;

typedef struct queue {
    int front, rear;
    Customer* cus[MAX_CUSTOMER_SIZE];
} Queue;

typedef struct ListNode {
    Customer* cus;
    struct ListNode* link;
}ListNode;

typedef struct TreeNode {
    char name[100];
    struct TreeNode* left, * right;
}TreeNode;

void init_queue(Queue* q);
int is_empty_queue(Queue* q);
int is_full_queue(Queue* q);
int enqueue(Queue* q, Customer* cus);
Customer* dequeue(Queue* q);
int add_front(Queue* q, Customer* cus);
Customer* delete_rear(Queue* q);

ListNode* insert_last(ListNode* tail, Customer* cus);
ListNode* insert_first(ListNode* tail, Customer* cus);
ListNode* search_list(ListNode* tail);
ListNode* put_rider_table(Customer* cus, ListNode* tail);

Customer* create_customer();
void init_cup(Stack* cup);
int is_full(Stack* cup);
int is_empty(Stack* cup);
void push(int choice, Stack* cup);
int pop(Stack* cup);

const char* get_cook_away(int cook_number);
void pre_order(Customer* cus, TreeNode* root);
void in_order(Customer* cus, TreeNode* root);
void post_order(Customer* cus, TreeNode* root);

Customer* delete_first(ListNode** ptail);
Customer* delete_(ListNode** ptail, ListNode* pre);

#endif
