#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


int main(void) {
    linked_list_int* ll_list_norm = nullptr;
    linked_list_int* ll_list_lower = nullptr;
    linked_list_int* ll_list_higher = nullptr;

    for (int i = 0; i < 100; i++) {
        int random = rand() % 100;

        ll_list_norm = linked_list_int_add_segment(ll_list_norm, random);
        ll_list_lower = linked_list_int_add_segment_lower(ll_list_lower, random);
        ll_list_higher = linked_list_int_add_segment_higher(ll_list_higher, random);
    }

    printf("Normal (Ohne sortierung):\n");
    linked_list_int_prt(ll_list_norm);
    printf("Lower:\n");
    linked_list_int_prt(ll_list_lower);
    printf("Higher:\n");
    linked_list_int_prt(ll_list_higher);

    linked_list_int_free(ll_list_norm);
    linked_list_int_free(ll_list_lower);
    linked_list_int_free(ll_list_higher);





}