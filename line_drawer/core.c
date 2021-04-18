#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef linux

#include <sys/ioctl.h>
#include <unistd.h>

#endif

vec2_t new_vec(double x, double y) {
    vec2_t vec2 = {x, y};
    return vec2;
}

int vec2_to_index(vec2_t vec2, win_size_t size) {
    return (size.h / 2 - (int) round(vec2.y)) * size.w + (size.w / 2 + (int) round(vec2.x));
}

win_size_t get_terminal_size() {
    int w, h;

#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#endif

#ifdef linux
    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    w = win.ws_col;
    h = win.ws_row;
#endif

    win_size_t size = {w, h};
    return size;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
win_size_t get_win_size() {
    bool_t default_size;
    printf("Using the default size? [1 yes / 0 no] ");
    scanf("%d", &default_size);
    fflush(stdout);
    if (default_size)
        return get_terminal_size();
    int w, h;
    printf("Write w: ");
    scanf("%d", &w);
    fflush(stdout);
    printf("Write h: ");
    scanf("%d", &h);
    fflush(stdout);
    win_size_t size = {w, h};
    return size;
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
equation_type_t get_type() {
    equation_type_t type;
    printf("Write type\n0. Line\n1. Parable\n");
    scanf("%d", &type);
    fflush(stdout);
    return type;
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
equation_line_t get_equation_l() {
    double m, q;

    printf("Write m (y=mx+q): ");
    scanf("%lf", &m);
    fflush(stdout);

    printf("Write q (y=mx+q): ");
    scanf("%lf", &q);
    fflush(stdout);

    equation_line_t equation = {m, q};
    return equation;
}
#pragma clang diagnostic pop

equation_line_t zero_l() {
    equation_line_t equation = {0, 0};
    return equation;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
equation_parable_t get_equation_p() {
    double a, b, c;
    printf("Write a (y=ax²+bx+c): ");
    scanf("%lf", &a);
    fflush(stdout);
    printf("Write b (y=ax²+bx+c): ");
    scanf("%lf", &b);
    fflush(stdout);
    printf("Write c (y=ax²+bx+c): ");
    scanf("%lf", &c);
    fflush(stdout);

    equation_parable_t equation = {a, b, c};
    return equation;
}
#pragma clang diagnostic pop

equation_parable_t zero_p() {
    equation_parable_t equation = {0, 0, 0};
    return equation;
}

equation_t get_equation() {
    equation_type_t type = get_type();
    equation_line_t eq_l;
    equation_parable_t eq_p;
    if (type == line) {
        eq_l = get_equation_l();
        eq_p = zero_p();
    } else if (type == parable) {
        eq_l = zero_l();
        eq_p = get_equation_p();
    }
    equation_t equation = {type, eq_l, eq_p};
    return equation;
}

win_size_t get_max_win(win_size_t size) {
    int w = size.w - 1, h = size.h - 1;
    if (w % 2)
        w--;
    if (h % 2)
        h--;
    win_size_t min_max_win = {w, h};
    return min_max_win;
}

board_t new_board() {
    win_size_t size = get_win_size();
    equation_t equation = get_equation();
    win_size_t max_size = get_max_win(size);
    bool_t *bools = malloc(max_size.w * max_size.h * sizeof(bool_t));
    for (int i=0; i<max_size.h; i++)
        for (int j=0; j<max_size.w; j++)
            bools[i*max_size.w+j] = false;
    board_t board = {equation, max_size, bools};
    return board;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-flp30-c"
void compute_board(board_t board) {
    int max_abs_w = board.size.w / 2;
    int max_abs_h = board.size.h / 2;
    if (board.equation.type == line) {
        for (double x = (double) -max_abs_w; x <= (double) max_abs_w; x += 1 / board.equation.eq_l.m) {
            double y = x * board.equation.eq_l.m + board.equation.eq_l.q;
            if ((y >= (double) -max_abs_h) & (y <= (double) max_abs_h + 1))
                board.bools[vec2_to_index(new_vec(x, y), board.size)] = true;
        }
    }
    else if (board.equation.type == parable) {
        int unit = 1000;
        for (int i=-max_abs_w; i<=max_abs_w; i++) {
            for (int j=1; j<=unit; j++) {
                double x = (double) i / j;
                double y = x * x * board.equation.eq_p.a + x * board.equation.eq_p.b + board.equation.eq_p.c;
                if ((y >= (double) -max_abs_h) & (y <= (double) max_abs_h + 1)) {
                    int index = vec2_to_index(new_vec(x, y), board.size);
                    if ((index >= 0) & (index < board.size.h * board.size.w))
                        board.bools[index] = true;
                }
            }
        }
    }
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
void draw_board(board_t board) {
    for (int i = 0; i < board.size.h; i++) {
        for (int j = 0; j < board.size.w; j++) {
            char to_print = i == board.size.h / 2 ? '-' : '.';
            to_print = j == board.size.w / 2 ? '|' : to_print;
            to_print = ((j == board.size.w / 2) & (i == board.size.h / 2)) ? '+' : to_print;
            if (board.bools[i * board.size.w + j])
                printf("\033[41m%c\033[0m", to_print);
            else
                printf("%c", to_print);
        }
        putchar('\n');
    }
}
#pragma clang diagnostic pop