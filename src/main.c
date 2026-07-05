#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


int main(void) {
    linked_list_int_class* llc_list = linked_list_int_class_create();
    for (int i = 0; i < 20; i++) {
        int random = rand() % 100;
        llc_list->add_lower(llc_list, random);
    }

    llc_list->print(llc_list);

    llc_list->free(llc_list);
}