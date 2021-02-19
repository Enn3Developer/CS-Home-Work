#include <stdio.h>

typedef enum {false, true} bool;

int abs(int a);
void print_repetition(char string[], int times, bool new_line);
void draw_arrow(int n, bool up);

int main() {
    int n;
    bool up;

    printf("Write N: ");
    scanf("%d", &n);
    fflush(stdout);

    printf("Write the direction [1 for up, 0 for down]: ");
    scanf("%d", &up);
    fflush(stdout);

    draw_arrow(n, up);
}
// Returns the absolute value of `a`
int abs(int a) {
    return a >= 0 ? a : -a;
}

// prints repeating a string `times` times and if `new_line` is true than it prints a new line character
void print_repetition(char string[], int times, bool new_line) {
    for (int i=0; i<times; i++) {
        printf("%s", string);  // prints the string
    }
    if (new_line)
        printf("\n");
}

// Draws an arrow taking the size (`n`) and the direction (`up`)
void draw_arrow(int n, bool up) {
    int i;
    float third = n / 3;  // used to draw the trail of the arrow
    int inc = up ? 2 : -2;  // if `up`, then it should increment by 2, else it should decrement
    int dir = up ? 1 : n;  // if `up`, then it should start from 1, else it should start from `n`
    if (!up) {  // drawing the trail of the arrow if the direction is down (not `up`)
        for (i=0; i<n/2; i++) {
            print_repetition(" ", third, false);
            print_repetition("*", third, false);
            print_repetition(" ", third, true);
        }
    }

    for (i= dir; (i<=n) & (i>= 1); i += inc) {
        int spaces = (n - abs(i)) / 2;
        print_repetition(" ", spaces, false);
        print_repetition("*", abs(i), false);
        print_repetition(" ", spaces, true);
    }
    if (up) {  // drawing the trail of the arrow if the direction is up
        for (i=0; i<n/2; i++) {
            print_repetition(" ", third, false);
            print_repetition("*", third, false);
            print_repetition(" ", third, true);
        }
    }
}