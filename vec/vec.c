#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "vec.h"

vec_t new_vec() {
    unsigned long size = 0;
    int *elements = malloc(size * sizeof(int));
    vec_t vec = {size, elements};
    return vec;
}

int push(vec_t *vec, int element) {
    int *tmp = realloc(vec->elements, (vec->size + 1) * sizeof(int));
    if (tmp == NULL)
        return 0;
    vec->elements = tmp;
    vec->elements[vec->size] = element;
    vec->size++;
    return 1;
}

// Execution time: +1s
//int pop(vec_t *vec) {
//    int *tmp = malloc((vec->size - 1) * sizeof(int));
//    int last = vec->elements[vec->size - 1];
//    for (unsigned long i=0; i<vec->size-1; i++)
//        tmp[i] = vec->elements[i];
//    vec->elements = tmp;
//    vec->size--;
//    return last;
//}

// Execution time: ~50ms
int pop(vec_t *vec) {
    if (vec->size == 0)
        return 0;
    int last = vec->elements[vec->size - 1];
    int *tmp = realloc(vec->elements, (vec->size - 1) * sizeof(int));
    if (tmp == NULL)
        return 0;
    vec->elements = tmp;
    vec->size--;
    return last;
}

int get(vec_t vec, int index) {
    if ((index >= 0) & (index < vec.size))
        return vec.elements[index];
    return 0;
}

int len_of_int(int a) {
    if (a == 0) {  // if it's 0 we cannot compute the len with the formula below
        return 1;
    }
    int len = (int) floor(log10((abs(a)))) + 1;
    len += a < 0;  // we need to add the `-` symbol
    return len;
}

char *to_str(vec_t vec) {
    if (vec.size == 0) {
        char *str = malloc(3 * sizeof(char));
        str[0] = '[', str[1] = ']';
        return str;
    }
    unsigned long size = 2*vec.size;  // 2 + 2 * (vec.size - 1)
    unsigned long i;
    for (i=0; i<vec.size; i++) {
        size += len_of_int(vec.elements[i]);
    }
    char *str = malloc((size + 1) * sizeof(char));  // +1 because we need the last `\0` to have a printable str
    str[0] = '[';
    for (i=0; i<vec.size; i++) {
        int len = len_of_int(vec.elements[i]) + 3;
        char *tmp = malloc(len * sizeof(int));
        snprintf(tmp, len, "%d, ", vec.elements[i]);
        strcat(str, tmp);
    }
    str[size-1] = ']', str[size] = '\0';
    return str;
}