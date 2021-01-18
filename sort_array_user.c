#include <stdio.h>

typedef enum {false, true} bool;

void swap(int *xp, int *yp);
void bubblesort(int arr[], int n, bool reverse);
void print_array(int arr[], int n);

int main() {
    int n;
    printf("Inserisci N: ");
    scanf("%d", &n);
    fflush(stdout);

    int nums[n];
    for (int i=0; i<n; i++) {
        int input;
        printf("Inserire un numero [%d/%d]: ", i, n);
        scanf("%d", &input);
        fflush(stdout);
        nums[i] = input;
    }

    bool reverse;
    printf("Come vuoi ordinare l'array?\n0. Ordine crescente\n1. Ordine decrescente\n");
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
            // Spiego:
            // Se l'elemento j dell'array è maggiore dell'elemento j+1
            // Allora uscirà 1, altrimenti 0
            // Lo swap avviene solo quando il risultato dentro l'if è diverso da zero
            // Quindi, se è maggiore il risultato sarà 0 e non viene eseguita l'istruzione
            // Ma se è minore allora avviene lo swap
            if ((arr[j] > arr[j+1]) - reverse)
               swap(&arr[j], &arr[j+1]);
}

void print_array(int arr[], int n) {
    for (int i=0; i<n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}