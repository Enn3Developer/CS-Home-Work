#ifndef INFO_UTILS_H
#define INFO_UTILS_H

#include <stddef.h>

typedef enum {
    false, true
} bool_t;
typedef enum {
    left, down, right, up
} direction_t;

void reseed();

char int_to_char(int a);

int char_to_int(char a);

char ship_value_to_char(int value, bool_t return_one, bool_t return_space);

// left, left, right, right
// 1, 1, 0, 0
bool_t get_position_direction(direction_t direction);

const char *bool_to_str(bool_t bool);

const char *direction_to_str(direction_t direction);

#endif //INFO_UTILS_H