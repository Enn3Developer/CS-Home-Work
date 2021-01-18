#include <stdio.h>

typedef enum {false, true} bool;

int main() {
    int year;
    printf("Inserire l'anno: ");
    scanf("%d", &year);
    fflush(stdout);
    // Il modo più efficiente per controllare se un anno è bisestile o meno
    // Controlla se l'anno è divisibile per 400, se si allora è bisestile
    // Se no, controlla se l'anno è divisibile per 4 e non per 100
    // Se si allora è bisestile, altrimenti no
    bool is_leap = (! (year % 400)) || (! (year % 4) && (year % 100));

    if (is_leap) {
        printf("Si\n");
    }
    else {
        printf("No\n");
    }

    return 0;
}