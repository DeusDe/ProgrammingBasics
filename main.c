#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/src.h"


int main(void) {
    char* str_base;
    char* str_encryted;

    str_base = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\n";

    str_encryted = caeser_encrypt(str_base,1);

    printf("%s\n", str_encryted);

    free(str_encryted);

    return 0;
}