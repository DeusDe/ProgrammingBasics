//
// Created by max on 05.07.26.
//

#include "linked_list_int.h"

#include <stdio.h>
#include <stdlib.h>

linked_list_int* linked_list_int_create_segment(int number) {
    linked_list_int* ll_current = malloc(sizeof(linked_list_int));
    if (ll_current == nullptr) {
        return nullptr;
    }
    ll_current->int_number = number;
    ll_current->next = nullptr;
    return ll_current;
}

linked_list_int*  linked_list_int_add_segment(linked_list_int* ll_current, int number) {

    if (ll_current == nullptr) {
        return linked_list_int_create_segment(number);
    }

    linked_list_int* ll_index = ll_current; //Buffer Variable setzen

    while (ll_index->next != nullptr) { //Letzten Knoten suchen
        ll_index = ll_index->next;
    }

    ll_index->next = linked_list_int_create_segment(number); //Neuen Knoten hinzufügen
    return ll_current;
}

linked_list_int* linked_list_int_remove_segement_start(linked_list_int* ll_current, int number) {
    // Sicherheitscheck für leere Liste
    if (ll_current == nullptr) {
        return nullptr;
    }

    //Die zu löschende Zahl ist direkt der Start-Knoten
    if (ll_current->int_number == number) {
        linked_list_int* ll_next = ll_current->next;
        linked_list_int_free_segment(ll_current);
        return ll_next;
    }

    //Zahl ist woanders. Wir starten die Suche beim zweiten Element.
    linked_list_int_remove_segement(ll_current, ll_current->next, number);

    // Der Start-Knoten hat sich nicht verändert, wir geben ihn einfach zurück
    return ll_current;
}

void linked_list_int_remove_segement(linked_list_int* ll_previous, linked_list_int* ll_current,int number){
    if (ll_current == nullptr) return; // Ende der Liste, nichts gefunden

    if (ll_current->int_number == number) {
        if (ll_previous != nullptr) {
            ll_previous->next = ll_current->next; // Kette flicken
        }
        linked_list_int_free_segment(ll_current); // Knoten löschen!
        return;
    }

    //Weiter suchen
    linked_list_int_remove_segement(ll_current, ll_current->next, number);

}

void linked_list_int_free_segment(linked_list_int* ll_current) {
    if (ll_current == nullptr) {
        return;
    }
    free(ll_current);
}

void linked_list_int_free(linked_list_int* ll_current) {
    if (ll_current == nullptr) {
        return;
    }
    linked_list_int* ll_next = ll_current->next; //Nächsten Knoten zwischenspeichern
    if (ll_next != nullptr) {
        linked_list_int_free(ll_next); //Nächsten Knoten löschen
    }
    linked_list_int_free_segment(ll_current); //Aktuellen Knoten löschen
}

void linked_list_int_prt(linked_list_int* ll_current) {
    if (ll_current == nullptr) {
        return;
    }

    linked_list_int* ll_index = ll_current;
    int int_index = 0;
    while (ll_index != nullptr) {
        printf("index %i: %i\n", int_index, ll_index->int_number);
        ll_index = ll_index->next;
        int_index++;
    }
}