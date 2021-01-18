#include <stdio.h>

// Given an array by the user, sort it by increment or decrement order

typedef enum {false, true} bool;

void swap(int *xp, int *yp);
void bubblesort(int arr[], int n, bool reverse);
void print_array(int arr[], int n);

int main() {
    int n;
    printf("How many numbers? ");
    scanf("%d", &n);
    fflush(stdout);

    int nums[n];
    for (int i=0; i<n; i++) {
        int input;
        printf("Write a number [%d/%d]: ", i, n);
        scanf("%d", &input);
        fflush(stdout);
        nums[i] = input;
    }

    bool reverse;
    printf("How do you want to sort the list?\n0. Increment order\n1. Decrement order\n");
    scanf("%d", &reverse);
    fflush(stdout);
    
    bubblesort(nums, n, reverse);
    print_array(nums, n);

    return 0;
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubblesort(int arr[], int n, bool reverse) {
    int i, j; 
    for (i = 0; i < n-1; i++)   
        for (j = 0; j < n-i-1; j++)
            // Let me explain:
            // if the `j` element is greater than the `j+1`
            // then the return value'll be 1, otherwise 0
            // the swap happens only when the result inside the if is but a zero
            // so, if the result is bigger than 0 the istruction will not be executed
            // but if it's smaller than the swap happens
            if ((arr[j] > arr[j+1]) - reverse)
               swap(&arr[j], &arr[j+1]);
}

void print_array(int arr[], int n) {
    for (int i=0; i<n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
