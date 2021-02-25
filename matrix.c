#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {max_m, sum_m, equ, dia, mul_m, mean_m, min_max_m} menu;

void clear_buffer(char buffer[100]) {
    for (int i=0; i<100; i++) buffer[i] = '\0';
}

void split(int row[], int n, const char string[], char splitter);
void read_matrix(int m, int n, int raw_matrix[m][n]);
void print_matrix(int m, int n, int matrix[m][n]);

int min(int m, int n, int matrix[m][n]);
int max(int m, int n, int matrix[m][n]);
int mean(int m, int n, int matrix[m][n]);
int equal(int m, int n, int a[m][n], int b[m][n]);
void find(int m, int n, int matrix[m][n], int to_find, int pos[2]);

void sum(int m, int n, int a[m][n], int b[m][n], int c[m][n]);
void mul(int m, int n, int p, int a[m][n], int b[n][p], int c[m][p]);

int sum_dia(int m, int matrix[m][m], int is_main);
int max_dia(int m, int matrix[m][m], int is_main);

void max_m_f() {
    int m, n;

    printf("Write M: ");
    scanf("%d", &m);
    fflush(stdout);

    printf("Write N: ");
    scanf("%d", &n);
    fflush(stdout);

    int matrix[m][n];
    printf("Write the numbers of each row separated by a comma (ex. 1,2,3)\n");
    read_matrix(m, n, matrix);

    printf("The max is %d\n", max(m, n, matrix));
}

void sum_m_f() {
    int m, n;

    printf("Write M: ");
    scanf("%d", &m);
    fflush(stdout);

    printf("Write N: ");
    scanf("%d", &n);
    fflush(stdout);

    int matrix_a[m][n], matrix_b[m][n], result[m][n];

    printf("Write the numbers of each row separated by a comma (ex. 1,2,3)\n");
    read_matrix(m, n, matrix_a);
    printf("Write the numbers of each row separated by a comma (ex. 1,2,3)\n");
    read_matrix(m, n, matrix_b);

    sum(m, n, matrix_a, matrix_b, result);
    printf("The result is:\n");
    print_matrix(m, n, result);
}

void equ_f() {
    int m, n;

    printf("Write M: ");
    scanf("%d", &m);
    fflush(stdout);

    printf("Write N: ");
    scanf("%d", &n);
    fflush(stdout);

    int matrix_a[m][n], matrix_b[m][n];

    printf("Write the numbers of each row separated by a comma (ex. 1,2,3)\n");
    read_matrix(m, n, matrix_a);
    printf("Write the numbers of each row separated by a comma (ex. 1,2,3)\n");
    read_matrix(m, n, matrix_b);
    const char *value = equal(m, n, matrix_a, matrix_b) ? "true" : "false";
    printf("The two matrices are equal? %s\n", value);
}

void dia_f() {
    int m, is_main;

    printf("Write M: ");
    scanf("%d", &m);
    fflush(stdout);

    int matrix[m][m];
    printf("Write the numbers of each row separated by a comma (ex. 1,2,3)\n");
    read_matrix(m, m, matrix);

    printf("Main[1] or secondary[0]? ");
    scanf("%d", &is_main);
    printf("The sum is %d\n", sum_dia(m, matrix, is_main));
    printf("The max is %d\n", max_dia(m, matrix, is_main));
}

void mul_m_f() {
    int m, n, p;

    printf("Write M: ");
    scanf("%d", &m);
    fflush(stdout);

    printf("Write N: ");
    scanf("%d", &n);
    fflush(stdout);

    printf("Write P: ");
    scanf("%d", &p);
    fflush(stdout);

    int matrix_a[m][n], matrix_b[n][p], result[m][p];

    printf("Write the numbers of each row separated by a comma (ex. 1,2,3)\n");
    read_matrix(m, n, matrix_a);
    printf("Write the numbers of each row separated by a comma (ex. 1,2,3)\n");
    read_matrix(n, p, matrix_b);

    mul(m, n, p, matrix_a, matrix_b, result);
    print_matrix(m, p, result);
}

void mean_m_f() {
    int m, n, y, k;

    printf("Write M: ");
    scanf("%d", &m);
    fflush(stdout);

    printf("Write N: ");
    scanf("%d", &n);
    fflush(stdout);

    printf("Write Y: ");
    scanf("%d", &y);
    fflush(stdout);

    printf("Write K: ");
    scanf("%d", &k);
    fflush(stdout);

    int matrix_a[m][n], matrix_b[y][k];
    printf("Write the numbers of each row separated by a comma (ex. 1,2,3)\n");
    read_matrix(m, n, matrix_a);
    printf("Write the numbers of each row separated by a comma (ex. 1,2,3)\n");
    read_matrix(y, k, matrix_b);

    int mean_a = mean(m, n, matrix_a), mean_b = mean(y, k, matrix_b);
    char value = mean_a > mean_b ? '>' : '<';
    printf("Mean matrix a %c mean matrix b", value);
}

void min_max_m_f() {
    int m, n, y, k;

    printf("Write M: ");
    scanf("%d", &m);
    fflush(stdout);

    printf("Write N: ");
    scanf("%d", &n);
    fflush(stdout);

    printf("Write Y: ");
    scanf("%d", &y);
    fflush(stdout);

    printf("Write K: ");
    scanf("%d", &k);
    fflush(stdout);

    int matrix_a[m][n], matrix_b[y][k];
    printf("Write the numbers of each row separated by a comma (ex. 1,2,3)\n");
    read_matrix(m, n, matrix_a);
    printf("Write the numbers of each row separated by a comma (ex. 1,2,3)\n");
    read_matrix(y, k, matrix_b);

    int min_a = min(m, n, matrix_a), max_a = max(m, n, matrix_a);
    int min_b = min(y, k, matrix_b), max_b = max(y, k, matrix_b);

    int min_p[3], max_p[3];
    int pos[2];

    min_p[0] = min_a >= min_b;
    max_p[0] = max_a <= max_b;

    if (!min_p[0]) find(m, n, matrix_a, min_a, pos);
    else find(y, k, matrix_b, min_b, pos);
    min_p[1] = pos[0], min_p[2] = pos[1];

    if (!max_p[0]) find(m, n, matrix_a, max_a, pos);
    else find(y, k, matrix_b, max_b, pos);
    max_p[1] = pos[0], max_p[2] = pos[1];

    char matrix_p = !min_p[0] ? 'a' : 'b';
    char min_s[100];
    sprintf(min_s, "Min is in %c at position [%d; %d]\n", matrix_p, min_p[1], min_p[2]);
    matrix_p = !max_p[0] ? 'a' : 'b';
    char max_s[100];
    sprintf(max_s, "Max is in %c at position [%d; %d]\n", matrix_p, max_p[1], max_p[2]);

    printf("%s%s", min_s, max_s);
}

int main() {
    menu choice;
    printf("0. Max number in matrix\n1. Sum of two matrices\n2. Check if two matrices are equal\n3. Diagonal\n"
           "4. Multiplication of two matrices\n5. Mean of two matrices\n6. Min and max of two matrices\n");
    scanf("%d", &choice);
    fflush(stdout);

    switch (choice) {
        case max_m:
            max_m_f();
            break;
        case sum_m:
            sum_m_f();
            break;
        case equ:
            equ_f();
            break;
        case dia:
            dia_f();
            break;
        case mul_m:
            mul_m_f();
            break;
        case mean_m:
            mean_m_f();
            break;
        case min_max_m:
            min_max_m_f();
            break;
        default:
            break;
    }

    return 0;
}

void split(int row[], int n, const char string[], char splitter) {
    int index = 0, index_b = 0;
    int len_string = 100;  // hard-coded
    char buffer[100];
    clear_buffer(buffer);

    for (int i=0; i<len_string; i++) {
        char buffered = string[i];
        if (buffered != splitter) {
            buffer[index_b] = buffered;
            index_b++;
        }
        else if (buffered == splitter) {
            row[index] = atoi(buffer);
            index++;
            if (index >= n) return;
            clear_buffer(buffer);
            index_b = 0; 
        }
    }
}

void read_matrix(int m, int n, int raw_matrix[m][n]) {
    for (int i=0; i<m; i++) {
        char string[100];
        char ch = ',';
        scanf("%s", string);
        strcat(string, &ch);
        split(raw_matrix[i], n, string, ',');
    }
}

void print_matrix(int m, int n, int matrix[m][n]) {
    for (int i=0; i<m; i++) {
        putchar('>');
        for (int j=0; j<n; j++) {
            printf("%5d ", matrix[i][j]);
        }
        putchar('\n');
    }
}

int min(int m, int n, int matrix[m][n]) {
    int min_v = matrix[0][0];
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            min_v = min_v <= matrix[i][j] ? min_v : matrix[i][j];
        }
    }

    return min_v;
}

int max(int m, int n, int matrix[m][n]) {
    int max_v = matrix[0][0];
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            max_v = max_v >= matrix[i][j] ? max_v : matrix[i][j];
        }
    }

    return max_v;
}

int mean(int m, int n, int matrix[m][n]) {
    int tot = 0;
    for (int i=0; i<m; i++) {
        for (int j = 0; j < n; j++) {
            tot += matrix[i][j];
        }
    }
    tot /= m*n;

    return tot;
}

int equal(int m, int n, int a[m][n], int b[m][n]) {
    int e = 1;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            e &= a[i][j] == b[i][j];
        }
    }

    return e;
}

void find(int m, int n, int matrix[m][n], int to_find, int pos[2]) {
    for (int i=0; i<m; i++) for (int j = 0; j < n; j++)
        if (matrix[i][j] == to_find) {
            pos[0] = i, pos[1] = j;
            return;
        }
}

void sum(int m, int n, int a[m][n], int b[m][n], int c[m][n]) {
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void mul(int m, int n, int p, int a[m][n], int b[n][p], int c[m][p]) {
    for (int i=0; i<m; i++) {
        for (int j=0; j<p; j++) {
            c[i][j] = 0;
            for (int k=0; k<n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int sum_dia(int m, int matrix[m][m], int is_main) {
    int s = 0;
    int start = is_main ? 0 : m-1;
    int inc = is_main ? 1 : -1;
    int j = start;
    for (int i=0; i<m; i++) {
        s += matrix[i][j];
        j += inc;
    }

    return s;
}

int max_dia(int m, int matrix[m][m], int is_main) {
    int start = is_main ? 0 : m-1;
    int max_v = matrix[0][start];
    int inc = is_main ? 1 : -1;
    int j = start;
    for (int i=0; i<m; i++) {
        max_v = max_v >= matrix[i][j] ? max_v : matrix[i][j];
        j += inc;
    }

    return max_v;
}