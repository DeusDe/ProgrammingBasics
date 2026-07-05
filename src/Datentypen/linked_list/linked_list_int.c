//
// Created by max on 05.07.26.
//

#include "linked_list_int.h"

#include <stdio.h>
#include <stdlib.h>

linked_list_int* linked_list_int_create_segment(int number) {
    linked_list_int* ll_current = malloc(sizeof(linked_list_int));

    // Sicherheitscheck für malloc
    if (ll_current == nullptr) {
        return nullptr;
    }

    ll_current->int_number = number;
    ll_current->next = nullptr;

    return ll_current;
}

linked_list_int* linked_list_int_add_segment(linked_list_int* ll_current, int number) {
    // Fall 1: Liste ist noch komplett leer
    if (ll_current == nullptr) {
        return linked_list_int_create_segment(number);
    }

    linked_list_int* ll_index = ll_current;

    // Zum letzten Knoten navigieren
    while (ll_index->next != nullptr) {
        ll_index = ll_index->next;
    }

    // Neuen Knoten am Ende anfügen
    ll_index->next = linked_list_int_create_segment(number);

    return ll_current;
}

linked_list_int* linked_list_int_add_segment_lower(linked_list_int* ll_current, int number) {
    // Fall 1: Liste ist noch komplett leer
    if (ll_current == nullptr) {
        return linked_list_int_create_segment(number);
    }

    // Fall 2: Neue Zahl ist größer als der aktuelle Startknoten (neuer Head)
    if (number > ll_current->int_number) {
        linked_list_int* new_head = linked_list_int_create_segment(number);
        new_head->next = ll_current;
        return new_head;
    }

    // Fall 3: Richtige Position in der Mitte oder am Ende suchen
    linked_list_int* ll_index = ll_current;
    while (ll_index->next != nullptr && ll_index->next->int_number > number) {
        ll_index = ll_index->next;
    }

    // Neuen Knoten an der gefundenen Position einfügen
    linked_list_int* ll_next = ll_index->next;
    ll_index->next = linked_list_int_create_segment(number);
    ll_index->next->next = ll_next;

    return ll_current;
}

linked_list_int* linked_list_int_add_segment_higher(linked_list_int* ll_current, int number) {
    // Fall 1: Liste ist noch komplett leer
    if (ll_current == nullptr) {
        return linked_list_int_create_segment(number);
    }

    // Fall 2: Neue Zahl ist kleiner als der aktuelle Startknoten (neuer Head)
    if (number < ll_current->int_number) {
        linked_list_int* new_head = linked_list_int_create_segment(number);
        new_head->next = ll_current;
        return new_head;
    }

    // Fall 3: Richtige Position in der Mitte oder am Ende suchen
    linked_list_int* ll_index = ll_current;
    while (ll_index->next != nullptr && ll_index->next->int_number < number) {
        ll_index = ll_index->next;
    }

    // Neuen Knoten an der gefundenen Position einfügen
    linked_list_int* ll_next = ll_index->next;
    ll_index->next = linked_list_int_create_segment(number);
    ll_index->next->next = ll_next;

    return ll_current;
}

linked_list_int* linked_list_int_remove_segement_start(linked_list_int* ll_current, int number) {
    // Sicherheitscheck für leere Liste
    if (ll_current == nullptr) {
        return nullptr;
    }

    // Fall 1: Die zu löschende Zahl ist direkt der Startknoten
    if (ll_current->int_number == number) {
        linked_list_int* ll_next = ll_current->next;
        linked_list_int_free_segment(ll_current);
        return ll_next;
    }

    // Fall 2: Zahl ist woanders, Suche beim zweiten Element starten
    linked_list_int_remove_segment(ll_current, ll_current->next, number);

    // Der Startknoten hat sich nicht verändert, wir geben ihn einfach zurück
    return ll_current;
}

void linked_list_int_remove_segment(linked_list_int* ll_previous, linked_list_int* ll_current, int number) {
    // Abbruchbedingung: Ende der Liste, nichts gefunden
    if (ll_current == nullptr) return;

    // Zahl gefunden: Knoten aushängen und löschen
    if (ll_current->int_number == number) {
        if (ll_previous != nullptr) {
            ll_previous->next = ll_current->next; // Kette flicken
        }
        linked_list_int_free_segment(ll_current);
        return;
    }

    // Rekursiv weitersuchen
    linked_list_int_remove_segment(ll_current, ll_current->next, number);
}

linked_list_int* linked_list_int_get_segment(linked_list_int* ll_current, int number) {
    //Leere Liste übergeben
    if (ll_current == nullptr) {
        return nullptr;
    }

    //Index setzen
    linked_list_int* ll_index = ll_current;

    //Zahl suchen
    while(ll_index != nullptr) {
        if (ll_index->int_number == number) {
            return ll_index;
        }
        ll_index = ll_index->next;
    }

    //Wenn nichts gefunden wurde
    return nullptr;
}

void linked_list_int_free_segment(linked_list_int* ll_current) {
    // Sicherheitscheck
    if (ll_current == nullptr) {
        return;
    }

    free(ll_current);
}

void linked_list_int_free(linked_list_int* ll_current) {
    // Sicherheitscheck für leere Liste
    if (ll_current == nullptr) {
        return;
    }

    // Nächsten Knoten zwischenspeichern und rekursiv löschen
    linked_list_int* ll_next = ll_current->next;
    if (ll_next != nullptr) {
        linked_list_int_free(ll_next);
    }

    // Aktuellen Knoten löschen
    linked_list_int_free_segment(ll_current);
}

void linked_list_int_free_iterative(linked_list_int* ll_current) {
    linked_list_int* ll_index = ll_current;
    linked_list_int* ll_next;

    while (ll_index != nullptr) {
        ll_next = ll_index->next;
        linked_list_int_free(ll_index);
        ll_index = ll_next;
    }
}

int linked_list_count(linked_list_int* ll_current) {
    linked_list_int* ll_index = ll_current;
    int count = 0;
    while (ll_index != nullptr) {
     count++;
    }
    return count;
}


void linked_list_int_prt(linked_list_int* ll_current) {
    // Sicherheitscheck
    if (ll_current == nullptr) {
        return;
    }

    linked_list_int* ll_index = ll_current;
    int int_index = 0;

    // Liste iterativ durchlaufen und ausgeben
    while (ll_index != nullptr) {
        printf("index %i: %i\n", int_index, ll_index->int_number);
        ll_index = ll_index->next;
        int_index++;
    }
}

void linked_list_int_manager_add_segment(linked_list_manager* llm_current, int number) {
    //Wenn die liste noch leer ist
    if (llm_current->head == nullptr) {
        llm_current->head = llm_current->tail = linked_list_int_create_segment(number);
        llm_current->int_count = 1;
        return;
    }

    //Am Ende hinzufügen
    llm_current->tail->next = linked_list_int_create_segment(number);
    llm_current->tail = llm_current->tail->next;
    llm_current->int_count++;
}

linked_list_manager* linked_list_int_manager_add_segment_lower(linked_list_manager* llm_current, int number) {

}

linked_list_manager* linked_list_int_manager_add_higher(linked_list_manager* llm_current, int number) {

}
