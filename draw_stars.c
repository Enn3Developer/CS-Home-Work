#include <stdio.h>

// Given `n` and `m`, draw a figure chosen by the user

void print_repetition(char string[], int times);
void draw_rect(int n, int m);
void draw_triangle(int n);
void draw_arrow(int n);

int main() {
    int n;
    int m;
    int choice;

    do {
        printf("Choose your drawning.\n1. Rect\n2. Triangle\n3. Arrow\n");
        scanf("%d", &choice);
        fflush(stdout);
        if (choice != 1 && choice != 2 && choice != 3) {  // I could've used an enum, but I'm too lazy to do it
            choice = 0;
            printf("Invalid choice. Retry\n");
        }
    } while (! choice);

    printf("Write N: ");
    scanf("%d", &n);
    fflush(stdout);
    
    switch (choice) {
    case 1:
        printf("Write M: ");
        scanf("%d", &m);
        fflush(stdout);
        draw_rect(n, m);
        break;
    case 2:
        draw_triangle(n);
        break;
    case 3:
        draw_arrow(n);
    default:
        break;
    }

    return 0;
}

void print_repetition(char string[], int times) {
    for (int i=0; i<times; i++) {
        printf("%s", string);
    }
    printf("\n");
}

void draw_rect(int n, int m) {
    for (int i=0; i<n; i++) {
        print_repetition("* ", m);
    }
}

void draw_triangle(int n) {
    for (int i=0; i<n; i++) {
        print_repetition("* ", i+1);
    }
}

void draw_arrow(int n) {
    int m_s = (n + 1) / 2;  // pre-computing m_s (max_star)
    int m_s_two = m_s * 2;  // and m_s_two (max_star_times_two)
    for (int i=1; i<=n; i++) {
        int s;
        if (i < m_s) {  // calculating how many stars to print
            s = i;
        }
        else {
            s = m_s_two - i;
        }
        print_repetition("* ", s);  // printing stars
    }
}