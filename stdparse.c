#include "include/stdparse.h"

int stdp_int()
{
    static char digit_buf[128];
    int digit_buf_index = 0;

    int curr_char;
    _Bool in_number = 0;
    _Bool is_digit = 0;

    do {
        curr_char = getchar();
        is_digit = curr_char >= 48 && curr_char <= 57;

        if (is_digit) {
          digit_buf[digit_buf_index++] = curr_char;
          in_number = 1;
        }
    } while (
      (!is_digit && !in_number) ||
      (in_number && is_digit)
    );

    digit_buf[digit_buf_index] = '\0';
    return atoi(digit_buf);
}