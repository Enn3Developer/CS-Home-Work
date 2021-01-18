#include <stdio.h>

// Given a year, check if that is a leap year or not

typedef enum {false, true} bool;

int main() {
    int year;
    printf("Write the year: ");
    scanf("%d", &year);
    fflush(stdout);
    // The more efficient way to check if a year is a leap year or not
    // it checks if the year is divisible by 400, if yes then it is
    // if not then it checks if the year is divisible by 4 and not by 100
    // if yes then it's a leap year otherwise not
    bool is_leap = (! (year % 400)) || (! (year % 4) && (year % 100));

    if (is_leap) {
        printf("Yes\n");
    }
    else {
        printf("No\n");
    }

    return 0;
}
