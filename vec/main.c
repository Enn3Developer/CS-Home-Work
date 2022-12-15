#include <stdio.h>
#include "vec.h"

int main() {
    // Instantiating a new stack
    vec_t vec = new_vec();
    printf("vec = %s\n", to_str(vec));
    // Testing `push` and `pop`
    for (int i=0; i<32768; i++)
        push(&vec, i);
    printf("vec = %s\n", to_str(vec));
    for (int i=0; i<32758; i++)
        pop(&vec);
    printf("vec = %s\n", to_str(vec));
    // Testing `get` with a value that is in the stack and one that isn't there
    printf("vec[5] = %d\n", get(vec, 5));
    printf("vec[50] = %d\n", get(vec, 50));

    return 0;
}