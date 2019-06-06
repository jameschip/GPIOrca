 
#include <ctype.h>
#include "parse.h"

/*
Takes a char as input and outouts the base 36 value of it. It it is an unrecognised char it outputs 0
*/
int tobase36(char c);

char parseBuffer(char *buffer, int length, parse_r *data) {
    if (buffer[0] == 'i' && buffer[1] == 'o') {
        data->io = tobase36(buffer[2]);
        data->value = tobase36(buffer[3]);
        return 0;
    }
    return -1;
}

int tobase36(char c) {
    if (isalpha(c)) {
        return toupper(c) - 55;
    } else if (isdigit(c)) {
        return c - '0';
    } else {
        return 0;
    }
}