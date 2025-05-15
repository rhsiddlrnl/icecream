#include "main.h"

int main()
{
    srand(time(NULL));
    Owner ice_owner;
    owner_init(&ice_owner);
    table_init();
    table_print();


    Rider rider;
    rider_init(&rider);

    bingsu_menu_init();

    for (int i = 0; i < MAX_CUSTOMER_SIZE + 1; i++) {
        Sleep(1000);
        if (get_order(&ice_owner) == -1)
            printf("사장: 더이상주문을받을수없어요. 다시찾아와주세요.\n");
    }

    for (int i = 0; i < MAX_CUSTOMER_SIZE + 1; i++) {
        if (prepare_order(&ice_owner) == -1)
            printf("나: 들어온주문이더이상없어요\n");
    }

    for (int i = 0; i < MAX_CUSTOMER_SIZE + 1; i++) {
        if (rider_pickup(&ice_owner, &rider) == -1) {
            printf("라이더: 더 이상 배달할 주문이 없어요\n");
        }
        else {
            delivery_order(&ice_owner, &rider);
        }
    }

    printf("단속원 킷타아아아!!!\n");
    transposed_icecream_tb();

    return 0;
}