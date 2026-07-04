//
// Created by max on 04.07.26.
//

#include "caeser.h"

char* caeser_encrypt(const char* str_base, int i_shift) {
    int i_base_len = strlen(str_base);
    char *str_encryted = malloc(sizeof(char) * (i_base_len + 1));
    int char_buffer;

    //Leeren String returnen wenn kein String angegeben wurde
    if (str_encryted == NULL) {
        return nullptr;
    }

    //String Kopieren wenn der shift 0 ist
    if (i_shift == 0) {
        strcpy(str_encryted, str_base);
        return str_encryted;
    }

    //Shift anpassen falls größer als Alphabet
    i_shift = i_shift % CONST_ALPHA_LEN;

    //Haupt verschlüsselungsloop
    for (int int_index = 0; int_index < i_base_len; int_index++) {

        //Buchstaben ohne veränderung zwischenspeichern
        char_buffer = str_base[int_index];

        //Großbuchstaben Handling
        if (char_buffer >= 'A' && char_buffer <= 'Z'){
            char_buffer = caeser_range_helper(char_buffer + i_shift, 'A', 'Z');
            //Kleinbuchstaben Handling
        }else if (char_buffer >= 'a' && char_buffer <= 'z') {
            char_buffer = caeser_range_helper(char_buffer + i_shift, 'a', 'z');
        }

        //Setzen des finalen Buchstaben
        str_encryted[int_index] = (char)char_buffer;
    }

    //Setzen des Stringendes
    str_encryted[i_base_len] = '\0';
    return str_encryted;
}

int caeser_range_helper(const int i_char_buffer, const char char_min, const char char_max) {
    if (i_char_buffer > char_max) {
        return i_char_buffer - CONST_ALPHA_LEN;
    }

    if (i_char_buffer < char_min) {
        return i_char_buffer + CONST_ALPHA_LEN;
    }

    return i_char_buffer;
}