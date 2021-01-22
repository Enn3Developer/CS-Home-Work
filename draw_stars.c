#include <stdio.h>

// Given `n` and `m`, draw a figure chosen by the user

typedef enum {false, true} bool;
typedef enum {rect, triangle, arrow, comp_triangle, pyramid} draw;

// |-------------------------------------------------------------|
// |                    Declaring Functions                      |
// |-------------------------------------------------------------|
void print_repetition(char string[], int times, bool new_line);
void draw_rect(int n, int m);
void draw_triangle(int n);
void draw_arrow(int n);
void draw_complementary_triangle(int n);
void draw_pyramid(int n);

int main() {
    int n, m, choice;

    printf("Choose your drawning.\n0. Rect\n1. Triangle\n2. Arrow\n3. Complementary triangle\n4. Pyramid\n");
    scanf("%d", &choice);
    fflush(stdout);

    printf("Write N: ");
    scanf("%d", &n);
    fflush(stdout);
    
    switch (choice) {  // a switch is like a lot of if-else if-else, but is more readable
        case rect:
            printf("Write M: ");
            scanf("%d", &m);
            fflush(stdout);
            draw_rect(n, m);
            break;
        case triangle:
            draw_triangle(n);
            break;
        case arrow:
            draw_arrow(n);
            break;
        case comp_triangle:
            draw_complementary_triangle(n);
            break;
        case pyramid:
            draw_pyramid(n);
            break;
    }

    return 0;
}

// prints repeating a string `times` times and if `new_line` is true than it prints a new line character
void print_repetition(char string[], int times, bool new_line) {
    for (int i=0; i<times; i++) {
        printf("%s", string);  // prints the string
    }
    if (new_line)
        printf("\n");
}

void draw_rect(int n, int m) {
    for (int i=0; i<n; i++) {  // repeats every new line
        print_repetition("* ", m, true);  // prints the stars `m` times with a new line character at the end
    }
}

void draw_triangle(int n) {
    for (int i=1; i<=n; i++) {  // repeats every new line
        print_repetition("* ", i, true);  // prints the stars `i` times
    }
}

void draw_arrow(int n) {
    int m_s = (n + 1) / 2;  // pre-computing m_s (max_star)
    int m_s_two = m_s * 2;  // and m_s_two (max_star_times_two)
    for (int i=1; i<=n; i++) {
        // this simply checks if `i` is smaller than `m_s`
        // if it is, then `s` would be `i`
        // otherwise it would be the complementary of double `m_s` (`m_s_two`) and `i`
        // this is where precomputing m_s_two boost the performance, even by a little
        // (try this with n>1000 with and without precomputing timing the execution)
        int s = i < m_s ? i : m_s_two - i;  // calculating how many stars to print
        print_repetition("* ", s, true);  // printing stars
    }
}

void draw_complementary_triangle(int n) {
    for (int i=n; i>0; i--) {  // the opposite of draw_triangle
        print_repetition("  ", n-i, false);  // two spaces so everything is alignated
        print_repetition("* ", i, true);
    }
}

void draw_pyramid(int n) {
    for (int i=1; i<=n; i+=2) {  // if I did `i++` then the result would be wrong (try it yourself)
        int spaces = (n - i) / 2;  // how much spaces has to be left before and after the stars
        print_repetition("  ", spaces, false);
        print_repetition("* ", i, false);
        print_repetition("  ", spaces, true);
    }
}