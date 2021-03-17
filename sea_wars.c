#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>

#define ROW 8
#define COL 10

void reseed() {
    srandom(time(0) + clock() + random() + getpid());
}

void clear() {
    while (getchar() != '\n');
}

char int_to_char(int a) {
    assert((a >= 0) & (a < 26));
    return (char)(97 + a);
}

int char_to_int(char a) {
    assert((a >= 97) & (a <= 122));
    return a-97;
}

char board_int_to_char(int a, int return_one) {
    switch (a) {
        case 1:
            // If it should return `*`, return it
            // else return `-`
            if (return_one)
                return '*';
        case 0:
            return '-';
        case 2:
            return '+';
        case 3:
            return 'o';
        default:
            return '\0';
    }
}

void generate_board(int board[ROW][COL]) {
    for (int i=0; i<ROW; i++)
        for (int j=0; j<COL; j++) {
            int board_value = (int) random() % 3;
            board[i][j] = board_value == 2;
        }
}

void print_board(int board[ROW][COL], int return_one) {
//  Print the column numbers
    printf("   ");
    for (int i=1; i<=COL; i++)
        printf("%1d ", i);
    putchar('\n');
//  ------------------------------------------------------------------------
//  Print the rows letters + the board
    for (int i=0; i<ROW; i++) {
        printf("%c: ", int_to_char(i));
        for (int j=0; j<COL; j++) {
            printf("%c ", board_int_to_char(board[i][j], return_one));
        }
        putchar('\n');
    }
//  ------------------------------------------------------------------------
}

int can_hit_here(int board[ROW][COL], int r, int c) {
    int valid = 1;
    valid &= (r >= 0) & (r < ROW);
//    printf("Debug: valid = %d\n", valid);
    valid &= (c >= 0) & (c < COL);
//    printf("Debug: valid = %d\n", valid);
    valid &= board[r][c] < 2;
//    printf("Debug: valid = %d\n", valid);
    return valid;
}

int hit_board(int board[ROW][COL], int r, int c) {
    board[r][c] += 2;
    return board[r][c] == 3;
}

void generate_enemy_turn(int coord[2]) {
    coord[0] = (int) random() % ROW;
    coord[1] = (int) random() & COL;
}

int check_winner(int player[ROW][COL], int enemy[ROW][COL]) {
    int p_winner = 1, e_winner = 1;

    for (int i=0; i<ROW; i++) {
        for (int j=0; j<COL; j++) {
            p_winner &= enemy[i][j] != 1;
            e_winner &= player[i][j] != 1;
        }
    }

    if (p_winner) return 1;
    else if (e_winner) return 2;

    return 0;
}

void update_board(int player_board[ROW][COL], int enemy_board[ROW][COL]) {
    printf("Your Board:\n");
    print_board(player_board, 1);
    putchar('\n');
    printf("Enemy Board:\n");
    print_board(enemy_board, 0);
}

int msleep(long milli) {
    struct timespec ts;
    int res;

    if (milli < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = milli / 1000;
    ts.tv_nsec = (milli % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

int int_to_char_test();
int char_to_int_test();
int board_int_to_char_test();
int generate_board_test();

void test() {
    printf("Test\n");
    int tests = 4;
    int results[4];

    results[0] = int_to_char_test();
    printf("int_to_char_test(): %d\n", results[0]);
    results[1] = char_to_int_test();
    printf("char_to_int_test(): %d\n", results[1]);
    results[2] = board_int_to_char_test();
    printf("board_int_to_char_test(): %d\n", results[2]);
    results[3] = generate_board_test();
    printf("generate_board_test(): %d\n", results[3]);

    int valid = 1;
    for (int i=0; i<tests; i++)
        valid &= results[i];
    printf("\n\nTotal result from the tests: %d\n", valid);
}

int main(int argc, char *argv[]) {
    reseed();
    // Run with parameter `test` to run unit tests
    if (argc == 2) {
        if (!strcmp(argv[1], "test"))
            test();
    }
    else {
        printf("     **** SEA WARS ****\n\n");  // 5 spaces
        long long board_player = 0;
        int player_board[ROW][COL], enemy_board[ROW][COL];
        generate_board(player_board); generate_board(enemy_board);
        update_board(player_board, enemy_board);
        while (1) {
            if (!(board_player % 2)) {
                fflush(stdout);
                printf("Your turn:\n");
                int to_break = 0;
                int valid = 0;
                int r, c;
                while (!valid) {
                    printf("To choose a location, write the letter and then the number (e.g. `e 8`)\n");
                    char command[5];
                    scanf("%5[0-9a-zA-Z ]", command);
                    fflush(stdout);
                    clear();
//                    printf("Debug: command = %s\n", command);
                    if (!strcmp(command, "exit") | !strcmp(command, "e")) {
                        printf("Exiting...");
                        to_break = 1;
                        break;
                    }
                    r = char_to_int(command[0]);
                    char coord[2];
                    coord[0] = command[2], coord[1] = command[3];
                    c = (int) strtol(coord, NULL, 10) - 1;
//                    printf("Debug: c = %d\n", c);
                    if (can_hit_here(enemy_board, r, c))
                        valid = 1;
                    else
                        printf("Not a valid location. Retry\n");
                    reseed();
                }
                if (to_break) break;
                if (hit_board(enemy_board, r, c)) {
                    printf("You hit an enemy spot! One more turn to go.\n");
                    board_player--;
                }
                else {
                    printf("Water!\n");
                }
            }
            else {
                printf("Enemy turn:\n");
                reseed();
                msleep(1000);
                int valid = 0;
                int turns = -1;
                int coord[2];
                while (!valid) {
                    turns++;
                    if (turns >= 1000) {
                        reseed();
                        turns = -1;
                    }
                    generate_enemy_turn(coord);
                    if (can_hit_here(player_board, coord[0], coord[1]))
                        valid = 1;
                }
                char *coord_print = (char*)malloc(4 * sizeof(char));
                sprintf(coord_print, "%c %d", int_to_char(coord[0]), coord[1]+1);
                if (hit_board(player_board, coord[0], coord[1])) {
                    printf("%s. The enemy hit one of your spot. Ouch!\n", coord_print);
                    board_player--;
                }
                else {
                    printf("%s. Water! You're lucky\n", coord_print);
                }
            }
            msleep(3000);
            board_player++;
            update_board(player_board, enemy_board);
            msleep(3000);
            int winner = check_winner(player_board, enemy_board);
            if (winner) {
                printf("There's a winner!\n");
                winner--;
                const char *winner_name = winner ? "Enemy" : "You";
                printf("%s win!\n", winner_name);
                break;
            }
        }
    }
    return 0;
}

int int_to_char_test() {
    return (int_to_char(0) == 'a') & (int_to_char(25) == 'z');
}

int char_to_int_test() {
    return (char_to_int('a') == 0) & (char_to_int('z') == 25);
}

int board_int_to_char_test() {
    int test_board = 1;
    test_board &= board_int_to_char(0, 0) == '-';
    test_board &= board_int_to_char(1, 0) == '-';
    test_board &= board_int_to_char(1, 1) == '*';
    test_board &= board_int_to_char(2, 0) == '+';
    test_board &= board_int_to_char(3, 0) == 'o';

    return test_board;
}

int generate_board_test() {
    int valid;
    int board[ROW][COL];
    generate_board(board);
    print_board(board, 1);
    printf("Asking the developer. Is the board valid? ");
    scanf("%d", &valid); // NOLINT(cert-err34-c)
    fflush(stdout);
    return valid;
}