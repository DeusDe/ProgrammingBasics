//
// Created by max on 05.07.26.
//

#ifndef PROGRAMMINGBASICS_LINKED_LIST_INT_H
#define PROGRAMMINGBASICS_LINKED_LIST_INT_H

typedef struct linked_list_int {
    int int_number;
    struct linked_list_int* next;
} linked_list_int;

linked_list_int* linked_list_int_create_segment(int number);
linked_list_int*  linked_list_int_add_segment(linked_list_int* ll_current, int number);
linked_list_int* linked_list_int_add_segment_lower(linked_list_int* ll_current, int number);
linked_list_int* linked_list_int_add_segment_higher(linked_list_int* ll_current, int number);
void linked_list_int_remove_segment(linked_list_int* ll_previous, linked_list_int* ll_current,int number);
linked_list_int* linked_list_int_get_segment(linked_list_int* ll_current, int number);
void linked_list_int_free_segment(linked_list_int* ll_current);
void linked_list_int_free(linked_list_int* ll_current);
void linked_list_int_prt(linked_list_int* ll_current);
int linked_list_count(linked_list_int* ll_current);
#endif //PROGRAMMINGBASICS_LINKED_LIST_INT_H
