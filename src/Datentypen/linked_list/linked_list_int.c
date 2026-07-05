//
// Created by max on 05.07.26.
//

#include "linked_list_int.h"

#include <stdio.h>
#include <stdlib.h>


// ==============================================================================
// DATENTYPEN (Structs, die nach außen unsichtbar sind)
// ==============================================================================

// Linked List Segment
typedef struct linked_list_int {
    int int_number;
    struct linked_list_int* next;
} linked_list_int;

// Linked List Manager
typedef struct linked_list_int_manager {
    int int_count;
    struct linked_list_int* head;
    struct linked_list_int* tail;
} linked_list_int_manager;

/* ==============================================================================
 * INTERNE PROTOTYPEN (Forward Declarations)
 * ============================================================================== */
// Segment-Funktionen
static linked_list_int *linked_list_int_create_segment(int number);
static linked_list_int *linked_list_int_get_segment(linked_list_int *ll_current, int number);
static void linked_list_int_prt(linked_list_int *ll_current);
[[maybe_unused]] static int linked_list_count(linked_list_int *ll_current);
[[maybe_unused]] static linked_list_int *linked_list_int_add_segment(linked_list_int *ll_current, int number);
[[maybe_unused]] static linked_list_int *linked_list_int_add_segment_lower(linked_list_int *ll_current, int number);
[[maybe_unused]] static linked_list_int *linked_list_int_add_segment_higher(linked_list_int *ll_current, int number);
[[maybe_unused]] static linked_list_int *linked_list_int_remove_segment_start(linked_list_int *ll_current, int number);
static void linked_list_int_remove_segment(linked_list_int *ll_previous, linked_list_int *ll_current, int number);
static void linked_list_int_free_segment(linked_list_int *ll_current);
static void linked_list_int_free(linked_list_int *ll_current);
static void linked_list_int_free_iterative(linked_list_int *ll_current);

// Manager-Funktionen
static linked_list_int_manager* linked_list_int_manager_create();
[[maybe_unused]] static linked_list_int *linked_list_int_manager_get_segment(const linked_list_int_manager *llm_current, int number);
static void linked_list_int_manager_prt(const linked_list_int_manager *llm_current);
static void linked_list_int_manager_add_segment(linked_list_int_manager *llm_current, int number);
static void linked_list_int_manager_add_segment_lower(linked_list_int_manager *llm_current, int number);
static void linked_list_int_manager_add_segment_higher(linked_list_int_manager *llm_current, int number);
static void linked_list_int_manager_remove_segment(linked_list_int_manager *llm_current, int number);
[[maybe_unused]] static void linked_list_int_manager_free(linked_list_int_manager *llm_current);
static void linked_list_int_manager_free_iterative(linked_list_int_manager *llm_current);

// Class-Wrapper
static void linked_list_int_class_add_segment(linked_list_int_class* llc_current, int number);
static void linked_list_int_class_add_segment_lower(linked_list_int_class* llc_current, int number);
static void linked_list_int_class_add_segment_higher(linked_list_int_class* llc_current, int number);
static void linked_list_int_class_remove_segment(linked_list_int_class* llc_current, int number);
static void linked_list_int_class_prt(linked_list_int_class* llc_current);


// ==============================================================================
// 1. SEGMENT-FUNKTIONEN (Normal)
// ==============================================================================

/**
 * @brief Erstellt einen neuen, isolierten Listenknoten.
 *
 * @param number Der Integer-Wert, den der Knoten speichern soll.
 * @return Pointer auf den neu erstellten Knoten oder nullptr bei Speicherfehler.
 */
static linked_list_int *linked_list_int_create_segment(int number) {
    linked_list_int *ll_current = malloc(sizeof(linked_list_int));

    // Sicherheitscheck für malloc
    if (ll_current == nullptr) {
        return nullptr;
    }

    ll_current->int_number = number;
    ll_current->next = nullptr;

    return ll_current;
}

/**
 * @brief Sucht iterativ nach einem Knoten mit einer bestimmten Zahl.
 *
 * @param ll_current Pointer auf den Startknoten.
 * @param number Die gesuchte Zahl.
 * @return Pointer auf den gefundenen Knoten, oder nullptr, wenn nicht gefunden.
 */
static linked_list_int *linked_list_int_get_segment(linked_list_int *ll_current, int number) {
    if (ll_current == nullptr) {
        return nullptr;
    }

    linked_list_int *ll_index = ll_current;

    while (ll_index != nullptr) {
        if (ll_index->int_number == number) {
            return ll_index;
        }
        ll_index = ll_index->next;
    }

    return nullptr;
}

/**
 * @brief Gibt die gesamte Liste formatiert in der Konsole aus.
 *
 * @param ll_current Pointer auf den Startknoten.
 */
static void linked_list_int_prt(linked_list_int *ll_current) {
    if (ll_current == nullptr) {
        return;
    }

    linked_list_int *ll_index = ll_current;
    int int_index = 0;

    while (ll_index != nullptr) {
        printf("index %i: %i\n", int_index, ll_index->int_number);
        ll_index = ll_index->next;
        int_index++;
    }
}

/**
 * @brief Zählt iterativ alle Knoten in der Liste.
 *
 * @param ll_current Pointer auf den Startknoten.
 * @return Die Anzahl der Knoten als Integer.
 */
static int linked_list_count(linked_list_int *ll_current) {
    linked_list_int *ll_index = ll_current;
    int count = 0;
    while (ll_index != nullptr) {
        count++;
        ll_index = ll_index->next;
    }
    return count;
}

/**
 * @brief Hängt einen neuen Knoten unsortiert an das Ende der Liste.
 *
 * @param ll_current Pointer auf den Startknoten (Head) der Liste.
 * @param number Die anzufügende Zahl.
 * @return Pointer auf den (möglicherweise neuen) Startknoten.
 */
static linked_list_int *linked_list_int_add_segment(linked_list_int *ll_current, int number) {
    if (ll_current == nullptr) {
        return linked_list_int_create_segment(number);
    }

    linked_list_int *ll_index = ll_current;

    while (ll_index->next != nullptr) {
        ll_index = ll_index->next;
    }

    ll_index->next = linked_list_int_create_segment(number);
    return ll_current;
}

/**
 * @brief Fügt eine Zahl so in die Liste ein, dass sie ABSTEIGEND sortiert bleibt.
 *
 * @param ll_current Pointer auf den Startknoten (Head).
 * @param number Die einzufügende Zahl.
 * @return Pointer auf den (möglicherweise neuen) Startknoten.
 */
static linked_list_int *linked_list_int_add_segment_lower(linked_list_int *ll_current, int number) {
    if (ll_current == nullptr) {
        return linked_list_int_create_segment(number);
    }

    if (number > ll_current->int_number) {
        linked_list_int *new_head = linked_list_int_create_segment(number);
        new_head->next = ll_current;
        return new_head;
    }

    linked_list_int *ll_index = ll_current;
    while (ll_index->next != nullptr && ll_index->next->int_number > number) {
        ll_index = ll_index->next;
    }

    linked_list_int *ll_next = ll_index->next;
    ll_index->next = linked_list_int_create_segment(number);
    ll_index->next->next = ll_next;

    return ll_current;
}

/**
 * @brief Fügt eine Zahl so in die Liste ein, dass sie AUFSTEIGEND sortiert bleibt.
 *
 * @param ll_current Pointer auf den Startknoten (Head).
 * @param number Die einzufügende Zahl.
 * @return Pointer auf den (möglicherweise neuen) Startknoten.
 */
static linked_list_int *linked_list_int_add_segment_higher(linked_list_int *ll_current, int number) {
    if (ll_current == nullptr) {
        return linked_list_int_create_segment(number);
    }

    if (number < ll_current->int_number) {
        linked_list_int *new_head = linked_list_int_create_segment(number);
        new_head->next = ll_current;
        return new_head;
    }

    linked_list_int *ll_index = ll_current;
    while (ll_index->next != nullptr && ll_index->next->int_number < number) {
        ll_index = ll_index->next;
    }

    linked_list_int *ll_next = ll_index->next;
    ll_index->next = linked_list_int_create_segment(number);
    ll_index->next->next = ll_next;

    return ll_current;
}

/**
 * @brief Entfernt eine bestimmte Zahl sicher aus der Liste (Wrapper für Start-Check).
 *
 * @param ll_current Pointer auf den Startknoten.
 * @param number Die zu löschende Zahl.
 * @return Pointer auf den (möglicherweise neuen) Startknoten.
 */
static linked_list_int *linked_list_int_remove_segment_start(linked_list_int *ll_current, int number) {
    if (ll_current == nullptr) {
        return nullptr;
    }

    if (ll_current->int_number == number) {
        linked_list_int *ll_next = ll_current->next;
        linked_list_int_free_segment(ll_current);
        return ll_next;
    }

    linked_list_int_remove_segment(ll_current, ll_current->next, number);
    return ll_current;
}

/**
 * @brief Rekursive Hilfsfunktion zum Finden und Löschen eines Knotens in der Liste.
 *
 * @param ll_previous Pointer auf den vorherigen Knoten.
 * @param ll_current Pointer auf den aktuell geprüften Knoten.
 * @param number Die zu löschende Zahl.
 */
static void linked_list_int_remove_segment(linked_list_int *ll_previous, linked_list_int *ll_current, int number) {
    if (ll_current == nullptr) return;

    if (ll_current->int_number == number) {
        if (ll_previous != nullptr) {
            ll_previous->next = ll_current->next;
        }
        linked_list_int_free_segment(ll_current);
        return;
    }

    linked_list_int_remove_segment(ll_current, ll_current->next, number);
}

/**
 * @brief Gibt den Speicherplatz eines einzelnen Knotens frei.
 *
 * @param ll_current Der zu löschende Knoten.
 */
static void linked_list_int_free_segment(linked_list_int *ll_current) {
    if (ll_current == nullptr) return;
    free(ll_current);
}

/**
 * @brief Löscht die gesamte Liste (rekursiver Ansatz). Kann bei riesigen Listen zu Stack-Overflow führen.
 *
 * @param ll_current Pointer auf den Startknoten.
 */
static void linked_list_int_free(linked_list_int *ll_current) {
    if (ll_current == nullptr) return;

    linked_list_int *ll_next = ll_current->next;
    if (ll_next != nullptr) {
        linked_list_int_free(ll_next);
    }

    linked_list_int_free_segment(ll_current);
}

/**
 * @brief Löscht die gesamte Liste (iterativer Ansatz). Sicher gegen Stack-Overflow.
 *
 * @param ll_current Pointer auf den Startknoten.
 */
static void linked_list_int_free_iterative(linked_list_int *ll_current) {
    linked_list_int *ll_index = ll_current;
    linked_list_int *ll_next;

    while (ll_index != nullptr) {
        ll_next = ll_index->next;
        linked_list_int_free_segment(ll_index);
        ll_index = ll_next;
    }
}


// ==============================================================================
// 2. MANAGER-FUNKTIONEN
// ==============================================================================

/**
 * @brief Erstellt einen neuen Listen-Manager.
 *
 * @return Pointer auf den konfigurierten Manager oder nullptr bei Speicherfehler.
 */
static linked_list_int_manager* linked_list_int_manager_create() {
    linked_list_int_manager* llm_current =  malloc(sizeof(linked_list_int_manager));

    if (llm_current == nullptr) return nullptr;

    llm_current->head = nullptr;
    llm_current->tail = nullptr;
    llm_current->int_count = 0;
    return llm_current;
}

/**
 * @brief Sucht nach einem Element in der Manager-Liste.
 *
 * @param llm_current Pointer auf den Listen-Manager.
 * @param number Die gesuchte Zahl.
 * @return Pointer auf den Knoten, oder nullptr, wenn nicht gefunden.
 */
static linked_list_int *linked_list_int_manager_get_segment(const linked_list_int_manager *llm_current, int number) {
    if (llm_current == nullptr) return nullptr;
    return linked_list_int_get_segment(llm_current->head, number);
}

/**
 * @brief Gibt die gesamte Manager-Liste in der Konsole aus.
 *
 * @param llm_current Pointer auf den Listen-Manager.
 */
static void linked_list_int_manager_prt(const linked_list_int_manager *llm_current) {
    if (llm_current == nullptr) return;
    linked_list_int_prt(llm_current->head);
}

/**
 * @brief Hängt einen Knoten O(1)-performant an das Ende der Manager-Liste.
 *
 * @param llm_current Pointer auf den Listen-Manager.
 * @param number Die anzufügende Zahl.
 */
static void linked_list_int_manager_add_segment(linked_list_int_manager *llm_current, int number) {
    if (llm_current == nullptr) return;

    if (llm_current->head == nullptr) {
        llm_current->head = llm_current->tail = linked_list_int_create_segment(number);
        llm_current->int_count = 1;
        return;
    }

    llm_current->tail->next = linked_list_int_create_segment(number);
    llm_current->tail = llm_current->tail->next;
    llm_current->int_count++;
}

/**
 * @brief Fügt einen Knoten absteigend sortiert in die Manager-Liste ein und updatet Head/Tail.
 *
 * @param llm_current Pointer auf den Listen-Manager.
 * @param number Die einzufügende Zahl.
 */
static void linked_list_int_manager_add_segment_lower(linked_list_int_manager *llm_current, int number) {
    if (llm_current == nullptr) return;

    if (llm_current->head == nullptr) {
        llm_current->head = llm_current->tail = linked_list_int_create_segment(number);
        llm_current->int_count++;
        return;
    }

    if (number > llm_current->head->int_number) {
        linked_list_int *new_head = linked_list_int_create_segment(number);
        new_head->next = llm_current->head;
        llm_current->head = new_head;
        llm_current->int_count++;
        return;
    }

    linked_list_int *ll_index = llm_current->head;
    while (ll_index->next != nullptr && ll_index->next->int_number > number) {
        ll_index = ll_index->next;
    }

    if (ll_index->next == nullptr) {
        ll_index->next = linked_list_int_create_segment(number);
        llm_current->tail = ll_index->next;
    } else {
        linked_list_int *ll_next = ll_index->next;
        ll_index->next = linked_list_int_create_segment(number);
        ll_index->next->next = ll_next;
    }
    llm_current->int_count++;
}

/**
 * @brief Fügt einen Knoten aufsteigend sortiert in die Manager-Liste ein und updatet Head/Tail.
 *
 * @param llm_current Pointer auf den Listen-Manager.
 * @param number Die einzufügende Zahl.
 */
static void linked_list_int_manager_add_segment_higher(linked_list_int_manager *llm_current, int number) {
    if (llm_current == nullptr) return;

    if (llm_current->head == nullptr) {
        llm_current->head = llm_current->tail = linked_list_int_create_segment(number);
        llm_current->int_count++;
        return;
    }

    if (number < llm_current->head->int_number) {
        linked_list_int *new_head = linked_list_int_create_segment(number);
        new_head->next = llm_current->head;
        llm_current->head = new_head;
        llm_current->int_count++;
        return;
    }

    linked_list_int *ll_index = llm_current->head;
    while (ll_index->next != nullptr && ll_index->next->int_number < number) {
        ll_index = ll_index->next;
    }

    if (ll_index->next == nullptr) {
        ll_index->next = linked_list_int_create_segment(number);
        llm_current->tail = ll_index->next;
    } else {
        linked_list_int *ll_next = ll_index->next;
        ll_index->next = linked_list_int_create_segment(number);
        ll_index->next->next = ll_next;
    }
    llm_current->int_count++;
}

/**
 * @brief Sucht und löscht ein Element aus dem Manager und korrigiert Head, Tail und Count.
 *
 * @param llm_current Pointer auf den Listen-Manager.
 * @param number Die zu löschende Zahl.
 */
static void linked_list_int_manager_remove_segment(linked_list_int_manager *llm_current, int number) {
    if (llm_current == nullptr || llm_current->head == nullptr) return;

    if (llm_current->head->int_number == number) {
        linked_list_int *node_to_delete = llm_current->head;
        llm_current->head = node_to_delete->next;

        if (llm_current->head == nullptr) {
            llm_current->tail = nullptr;
        }

        linked_list_int_free_segment(node_to_delete);
        llm_current->int_count--;
        return;
    }

    linked_list_int* ll_index = llm_current->head;
    linked_list_int* ll_prev = nullptr;

    while (ll_index != nullptr && ll_index->int_number != number) {
        ll_prev = ll_index;
        ll_index = ll_index->next;
    }

    if (ll_index == nullptr) return;

    if (ll_index->next == nullptr) {
        llm_current->tail = ll_prev;
        ll_prev->next = nullptr;
    } else {
        ll_prev->next = ll_index->next;
    }

    linked_list_int_free_segment(ll_index);
    llm_current->int_count--;
}

/**
 * @brief Löscht den gesamten Manager mitsamt allen Knoten (rekursiv).
 *
 * @param llm_current Pointer auf den Listen-Manager.
 */
static void linked_list_int_manager_free(linked_list_int_manager *llm_current) {
    if (llm_current == nullptr) return;
    linked_list_int_free(llm_current->head);
    free(llm_current);
}

/**
 * @brief Löscht den gesamten Manager mitsamt allen Knoten (iterativ).
 *
 * @param llm_current Pointer auf den Listen-Manager.
 */
static void linked_list_int_manager_free_iterative(linked_list_int_manager *llm_current) {
    if (llm_current == nullptr) return;
    linked_list_int_free_iterative(llm_current->head);
    free(llm_current);
}


// ==============================================================================
// 3. CLASS WRAPPER (Private Helfer-Funktionen für die OOP-Klasse)
// ==============================================================================

/**
 * @brief Helferfunktion für die Klasse: Fügt einen Knoten unsortiert hinzu.
 *
 * @param llc_current Pointer auf das Klassen-Objekt (self).
 * @param number Die hinzuzufügende Zahl.
 */
static void linked_list_int_class_add_segment(linked_list_int_class* llc_current, int number) {
    if (llc_current == nullptr) return;
    linked_list_int_manager_add_segment(llc_current->ll_manager, number);
}

/**
 * @brief Helferfunktion für die Klasse: Fügt einen Knoten absteigend sortiert hinzu.
 *
 * @param llc_current Pointer auf das Klassen-Objekt (self).
 * @param number Die hinzuzufügende Zahl.
 */
static void linked_list_int_class_add_segment_lower(linked_list_int_class* llc_current, int number) {
    if (llc_current == nullptr) return;
    linked_list_int_manager_add_segment_lower(llc_current->ll_manager, number);
}

/**
 * @brief Helferfunktion für die Klasse: Fügt einen Knoten aufsteigend sortiert hinzu.
 *
 * @param llc_current Pointer auf das Klassen-Objekt (self).
 * @param number Die hinzuzufügende Zahl.
 */
static void linked_list_int_class_add_segment_higher(linked_list_int_class* llc_current, int number) {
    if (llc_current == nullptr) return;
    linked_list_int_manager_add_segment_higher(llc_current->ll_manager, number);
}

/**
 * @brief Helferfunktion für die Klasse: Löscht einen bestimmten Knoten.
 *
 * @param llc_current Pointer auf das Klassen-Objekt (self).
 * @param number Die zu löschende Zahl.
 */
static void linked_list_int_class_remove_segment(linked_list_int_class* llc_current, int number) {
    if (llc_current == nullptr) return;
    linked_list_int_manager_remove_segment(llc_current->ll_manager, number);
}

/**
 * @brief Helferfunktion für die Klasse: Gibt die Liste aus.
 *
 * @param llc_current Pointer auf das Klassen-Objekt (self).
 */
static void linked_list_int_class_prt(linked_list_int_class* llc_current) {
    if (llc_current == nullptr) return;
    linked_list_int_manager_prt(llc_current->ll_manager);
}


// ==============================================================================
// 4. ÖFFENTLICHE FUNKTIONEN (Sichtbar für die main.c!)
// ==============================================================================

/**
 * @brief Simuliert eine Klasse, indem ein Wrapper um den Manager erstellt wird.
 * Verknüpft alle Funktionszeiger mit den internen Methoden.
 *
 * @return Neu angelegtes Objekt (Pointer auf die Klasse) oder nullptr bei Fehler.
 */
linked_list_int_class* linked_list_int_class_create() {
    linked_list_int_class *ll_class = malloc(sizeof(linked_list_int_class));
    if (ll_class == nullptr) {
        return nullptr;
    }

    ll_class->ll_manager = linked_list_int_manager_create();
    if (ll_class->ll_manager == nullptr) {
        free(ll_class);
        return nullptr;
    }

    // Zeigerverknüpfung zu unseren static-Helferfunktionen
    ll_class->add = linked_list_int_class_add_segment;
    ll_class->add_lower = linked_list_int_class_add_segment_lower;
    ll_class->add_higher = linked_list_int_class_add_segment_higher;
    ll_class->remove = linked_list_int_class_remove_segment;
    ll_class->print = linked_list_int_class_prt;
    ll_class->free = linked_list_int_class_free;

    return ll_class;
}

/**
 * @brief Löscht ein Linked List Class Objekt mitsamt seiner internen Struktur.
 *
 * @param ll_class Pointer auf das zu löschende Klassen-Objekt.
 */
void linked_list_int_class_free(linked_list_int_class* ll_class) {
    if (ll_class == nullptr) {
        return;
    }
    linked_list_int_manager_free_iterative(ll_class->ll_manager);
    free(ll_class);
}