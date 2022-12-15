#ifndef INFO_VEC_H
#define INFO_VEC_H

typedef struct vec {
    unsigned long size;
    int *elements;
} vec_t;

// Create a new stack with 0 elements inside
vec_t new_vec();

// Adds an element to the stack (index = size - 1)
int push(vec_t *vec, int element);

// Deletes the last element in the stack and returns it (index = size - 1)
int pop(vec_t *vec);

// Gets an element of the stack with a given index
// if index is not valid, it returns 0;
int get(vec_t vec, int index);

// Converts the stack to `char *` to print it
char *to_str(vec_t vec);

#endif