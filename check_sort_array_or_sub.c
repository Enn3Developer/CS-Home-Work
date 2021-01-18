#include <stdio.h>

// Given an array, return the aray (or sub-array) that is increment sorted

typedef enum {false, true} bool;

bool is_ordered(int arr[], int start, int end);
void print_array(int arr[], int start, int end);
void print_len_ordered(int arr[], int n);

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

    printf("I discovered this sub-array (or the array) increment sorted:\n");
    print_len_ordered(nums, n);

    return 0;
}

// Range: [start, end)
bool is_ordered(int arr[], int start, int end) {
    bool ordered = true;

    for (int i=start; i<end-1; i++) {
        ordered &= (arr[i] < arr[i+1]);
    }

    return ordered;
}

// Range: [start, end)
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
            for (int k=0; k<len_sub; k++) {  // Create a sub-array from `i` to `j`
                sub_arr[k] = arr[k+i];
            }
            // check if the newly created sub-array has at least two elements
            // if yes then check if that is ordered and his length is bigger than the len of the previous sub-array
            if (len_sub > 1 && is_ordered(sub_arr, 0, len_sub) && len_sub > len) {
                len = len_sub;
                for (int k=0; k<len_sub; k++) {
                    sub[k] = sub_arr[k];
                }
            }
        }
    }

    if (len > 1) {
        print_array(sub, 0, len);  // prints only the elements of the sub-array
    }
}
