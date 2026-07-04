//
// Created by max on 04.07.26.
//

#ifndef PROGRAMMINGBASICS_CAESER_H
#define PROGRAMMINGBASICS_CAESER_H

#define CONST_ALPHA_LEN 26
#include <stdlib.h>
#include <string.h>

char* caeser_encrypt(const char* str_base, int i_shift);
int caeser_range_helper(const int i_char_buffer, const char char_min, const char char_max);
#endif //PROGRAMMINGBASICS_CAESER_H
