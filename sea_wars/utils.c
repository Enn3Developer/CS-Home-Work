#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"

void reseed() {
    srandom(time(0) + clock() + random() + getpid());
}

char int_to_char(int a) {
    assert((a >= 0) & (a < 26));
    return (char) (97 + a);
}

int char_to_int(char a) {
    assert((a >= 97) & (a <= 122));
    return a - 97;
}

char ship_value_to_char(int value, bool_t return_one, bool_t return_space) {
    switch (value) {
        case 1:
            if (return_one)
                return '*';
        case 0:
            if (return_space)
                return ' ';
            else
                return '-';
        case 2:
            return 'x';
        case 3:
            return '+';
        case 4:
            return 'o';
        default:
            return '\0';
    }
}

const char *bool_to_str(bool_t bool) {
    return bool ? "true" : "false";
}

const char *direction_to_str(direction_t direction) {
    switch (direction) {
        case left:
            return "left";
        case down:
            return "down";
        case right:
            return "right";
        case up:
            return "up";
        default:
            return "err";
    }
}

bool_t get_position_direction(direction_t direction) {
    return direction < 2;
}