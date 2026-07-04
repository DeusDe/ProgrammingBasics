#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONST_ALPHA_LEN 26


char* caeser_encrypt(char* str_base, int i_shift) {
    int i_base_len = strlen(str_base);
    char *str_encryted = malloc(sizeof(char) * (i_base_len + 1));
    char char_buffer;

    //Leerer String oder Leerer shift wird direkt returned
    if (str_encryted == NULL || i_shift == 0) {
        return str_base;
    }

    //Shift anpassen falls größer als Alphabet
    while (i_shift <= -CONST_ALPHA_LEN) {
        i_shift += CONST_ALPHA_LEN;
    }
    while (i_shift >= CONST_ALPHA_LEN) {
        i_shift -= CONST_ALPHA_LEN;
    }

    //Haupt verschlüsselungsloop
    for (int int_index = 0; int_index < i_base_len; int_index++) {

        //Buchstaben ohne veränderung zwischenspeichern
        char_buffer = str_base[int_index];

        //Großbuchstaben Handling
        if (char_buffer >= 'A' && char_buffer <= 'Z'){
            char_buffer += i_shift;
            if (char_buffer > 'Z') {
                char_buffer -= CONST_ALPHA_LEN;
            }
            else if (char_buffer < 'A') {
                char_buffer += CONST_ALPHA_LEN;
            }

            //Kleinbuchstaben Handling
        }else if (char_buffer >= 'a' && char_buffer <= 'z') {
            char_buffer += i_shift;
            if (char_buffer > 'z'){char_buffer -= CONST_ALPHA_LEN;}
            else if (char_buffer < 'a'){char_buffer += CONST_ALPHA_LEN;}
        }

        //Setzen des finalen Buchstaben
        str_encryted[int_index] = char_buffer;
    }

    //Setzen des Stringendes
    str_encryted[i_base_len] = '\0';
    return str_encryted;
}

int main(void) {
    char* str_base;
    char* str_encryted;

    str_base = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\n";

    str_encryted = caeser_encrypt(str_base,27);

    printf(str_encryted);
    return 0;
}