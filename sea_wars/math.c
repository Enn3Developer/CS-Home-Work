#include "math.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

vec2_t new_vec2(int x, int y) {
    vec2_t new = {x, y};
    return new;
}

vec2_t add_vec2(vec2_t a, vec2_t b) {
    int x = a.x + b.x;
    int y = a.y + b.y;
    return new_vec2(x, y);
}

vec2_t sub_vec2(vec2_t a, vec2_t b) {
    int x = a.x - b.x;
    int y = a.y - b.y;
    return new_vec2(x, y);
}

bool_t is_equal_vec2(vec2_t a, vec2_t b) {
    return (a.x == b.x) & (a.y == b.y);
}

bool_t is_greater_vec2(vec2_t a, vec2_t b) {
    return (a.x > b.x) & (a.y > b.y);
}

bool_t is_greater_equal_vec2(vec2_t a, vec2_t b) {
    return (a.x >= b.x) & (a.y >= b.y);
}

bool_t is_smaller_vec2(vec2_t a, vec2_t b) {
    return (a.x < b.x) & (a.y < b.y);
}

bool_t is_vec2_inside_area(vec2_t vec2, vec2_t area_start, vec2_t area_size) {
    vec2_t area_end = add_vec2(area_start, area_size);
    return is_greater_equal_vec2(vec2, area_start) & is_smaller_vec2(vec2, area_end);
}

// just to don't get a warning from CLion
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArgumentSelectionDefects"

vec2_t swap_vec2(vec2_t vec2) {
    return new_vec2(vec2.y, vec2.x);
}

#pragma clang diagnostic pop

char *vec2_to_str(vec2_t vec2) {
    int size = (int) floor(log10(abs(vec2.x))) + (int) floor(log10(abs(vec2.y))) + 2;
    // {x: ; y: } = size: 10
    char *str = malloc((10 + size) * 2);
    sprintf(str, "{x: %d; y: %d}", vec2.x, vec2.y);
    return str;
}

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int positive_sub(int a, int b) {
    return max(a, b) - min(a, b);
}