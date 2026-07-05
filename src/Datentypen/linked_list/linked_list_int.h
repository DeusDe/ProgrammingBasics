//
// Created by max on 05.07.26.
//

#ifndef PROGRAMMINGBASICS_LINKED_LIST_INT_H
#define PROGRAMMINGBASICS_LINKED_LIST_INT_H

typedef struct linked_list_int_manager linked_list_int_manager;

typedef struct linked_list_int_class {
    // Eigenschaften (Properties)
    linked_list_int_manager* ll_manager;

    // Methoden (Funktionszeiger)
    void (*add)(struct linked_list_int_class* self, int number);
    void (*add_lower)(struct linked_list_int_class* self, int number);
    void (*add_higher)(struct linked_list_int_class* self, int number);
    void (*remove)(struct linked_list_int_class* self, int number);
    void (*print)(struct linked_list_int_class* self);
    void (*free)(struct linked_list_int_class* self);
} linked_list_int_class;

linked_list_int_class* linked_list_int_class_create();
void linked_list_int_class_free(linked_list_int_class* ll_class);

#endif //PROGRAMMINGBASICS_LINKED_LIST_INT_H