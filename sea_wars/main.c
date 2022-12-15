#include <string.h>
#include <stdio.h>

#include "ships.h"
#include "utils.h"
#include "board.h"

void test() {
    bool_t ok, total = true;

    printf("Testing ships.\n");

    ok = ship_test();
    total &= ok;
    printf("ship_test: %s\n", bool_to_str(ok));

    ok = rotation_test();
    total &= ok;
    printf("rotation_test: %s\n", bool_to_str(ok));

    printf("\nTesting board.\n");
    ok = board_test();
    total &= ok;
    printf("board_test: %s\n", bool_to_str(ok));

    printf("\n\nTotal tests: %s\n", bool_to_str(total));
}

int main(int argc, char *argv[]) {
    if (argc == 2) {  // run with parameter `test`
        if (!strcmp(argv[1], "test"))
            test();
    }
    else
        printf("Game not yet finished.\n");
    return 0;
}