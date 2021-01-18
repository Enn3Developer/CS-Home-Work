#include <stdio.h>
typedef enum {false, true} bool;

bool is_ordered(int arr[], int start, int end);
void print_array(int arr[], int start, int end);
void print_len_ordered(int arr[], int n);

int main() {
    int n;
    printf("Inserire N: ");
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

    printf("Ho rivelato questo sub-array (o array) ordinato in ordine crescente:\n");
    print_len_ordered(nums, n);

    return 0;
}

// Raggio: [start, end)
bool is_ordered(int arr[], int start, int end) {
    bool ordered = true;

    for (int i=start; i<end-1; i++) {
        ordered &= (arr[i] < arr[i+1]);
    }

    return ordered;
}

// Raggio: [start, end)
void print_array(int arr[], int start, int end) {
    for (int i=start; i<end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_len_ordered(int arr[], int n) {
    int sub[n];
    int len = -1;

    for (int i=0; i<n; i++) {
        for (int j=i; j<n; j++) {
            int len_sub = (j - i) + 1;
            int sub_arr[len_sub];
            for (int k=0; k<len_sub; k++) {
                sub_arr[k] = arr[k+i];
            }
            if (len_sub > 1 && is_ordered(sub_arr, 0, len_sub) && len_sub > len) {
                len = len_sub;
                for (int k=0; k<len_sub; k++) {
                    sub[k] = sub_arr[k];
                }
            }
        }
    }

    if (len > 1) {
        print_array(sub, 0, len);
    }
}