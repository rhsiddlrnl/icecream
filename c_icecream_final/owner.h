#ifndef OWNER_H
#define OWNER_H

#include "customer.h"

#define MAX_DELIVERY_COUNT 5


typedef struct owner {
    int total_income;
    int price_of_cupsize[MAX_CUPSIZE];
    Queue* q;
    ListNode* tail;
} Owner;

void bingsu_menu_init();
void owner_init(Owner* ice_owner);
void cal_sales(Owner* ice_owner, int cupsize, int penalty);
int get_order(Owner* ice_owner);


typedef struct rider {
    int count;
    ListNode* tail;
}Rider;

void rider_init(Rider* rider);


int prepare_order(Owner* ice_owner);
//int delivery_order(Customer* cus);

int rider_pickup(Owner* ice_owner, Rider* rider);
void delivery_order(Owner* ice_owner, Rider* reder);


#endif
