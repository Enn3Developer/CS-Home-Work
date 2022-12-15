#ifndef INFO_MATH_H
#define INFO_MATH_H

#include "utils.h"

typedef struct vec_2 {
    int x;
    int y;
} vec2_t;

vec2_t new_vec2(int x, int y);

vec2_t add_vec2(vec2_t a, vec2_t b);

vec2_t sub_vec2(vec2_t a, vec2_t b);

bool_t is_equal_vec2(vec2_t a, vec2_t b);

bool_t is_greater_vec2(vec2_t a, vec2_t b);

bool_t is_greater_equal_vec2(vec2_t a, vec2_t b);

bool_t is_smaller_vec2(vec2_t a, vec2_t b);

bool_t is_vec2_inside_area(vec2_t vec2, vec2_t area_start, vec2_t area_size);

vec2_t swap_vec2(vec2_t vec2);

char *vec2_to_str(vec2_t vec2);

int min(int a, int b);

int max(int a, int b);

int positive_sub(int a, int b);

#endif //INFO_MATH_H