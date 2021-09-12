#include "include/stdparse.h"

static _Bool is_digit(int character) {
    return character >= 48 && character <= 57;
}

int stdp_int() {
    static char digit_buf[128];
    int digit_buf_index = 0;

    int curr_char;
    _Bool in_number = 0;

    do {
        curr_char = getchar();

        if (is_digit(curr_char)) {
          digit_buf[digit_buf_index++] = curr_char;
          in_number = 1;
        }
    } while (
      (!is_digit(curr_char) && !in_number) ||
      (in_number && is_digit(curr_char))
    );

    digit_buf[digit_buf_index] = '\0';
    return atoi(digit_buf);
}