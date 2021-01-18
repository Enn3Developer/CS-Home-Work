#include <stdio.h>

// Given an array, count every positive and negative numbers
// If zero was given, warn the user and ask the number again

int main() {
    int n;
    printf("How many numbers? ");
    scanf("%d", &n);
    fflush(stdout);
    int counter[2];
    counter[0] = 0;  // Positives
    counter[1] = 0;  // Negatives

    for (int i=0; i<n; i++) {
        int input;
        do {
            printf("Write a number [%d/%d]: ", i, n);
            scanf("%d", &input);
            fflush(stdout);
            
            if (! input) {  // It's the same as `input != 0`
                printf("You wrote 0; write the remaining numbers\n");
            }
        } while (! input);  // It's the same as `input != 0`
        // If the number is negative, then `index` is 1 as the index of negative numbers' counter
        int index = input < 0;
        counter[index]++;
    }

    printf("Positive numbers: %d\nNegative numbers: %d\n", counter[0], counter[1]);

    return 0;
}