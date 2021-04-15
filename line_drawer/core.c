#include "core.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef linux

#include <sys/ioctl.h>
#include <unistd.h>

#endif

vec2_t new_vec(float x, float y) {
    vec2_t vec2 = {x, y};
    return vec2;
}

win_size_t get_terminal_size() {
    int w, h;

#ifdef _WIN32
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

float get_unit() {
    float unit;
    printf("Enter the unit: ");
    scanf("%f", &unit);
    fflush(stdout);

    return unit;
}

equation_t get_equation() {
    float m, q;

    printf("Write m (y=mx+q): ");
    scanf("%f", &m);
    fflush(stdout);

    printf("Write q (y=mx+q): ");
    scanf("%f", &q);
    fflush(stdout);

    equation_t equation = {m, q};
    return equation;
}

win_size_t get_max_win(win_size_t size) {
    int w = size.w - 1, h = size.h - 1;
    if (w % 2)
        w--;
    if (h & 2)
        h--;
    win_size_t min_max_win = {w, h};
    return min_max_win;
}

board_t new_board() {
    win_size_t size = get_win_size();
    equation_t equation = get_equation();
    win_size_t max_size = get_max_win(size);
    vec2_t *vecs = malloc(max_size.w * max_size.h * sizeof(vec2_t));
    bool_t *bools = malloc(max_size.w * max_size.h * sizeof(bool_t));
    float default_value_x = (float) (-max_size.w) / 2;
    float next_value_x = default_value_x;
    float next_value_y = (float) max_size.h / 2;
    for (int i = 0; i < max_size.h; i++) {
        for (int j = 0; j < max_size.w; j++) {
            bools[i * max_size.w + j] = false;
            vecs[i * max_size.w + j] = new_vec(next_value_x, next_value_y);
            next_value_x++;
        }
        next_value_x = default_value_x;
        next_value_y--;
    }
    board_t board = {equation, max_size, vecs, bools};
    return board;
}

void compute_board(board_t board) {
    for (int i = 0; i < board.size.h; i++) {
        for (int j = 0; j < board.size.w; j++) {
            vec2_t vec2 = board.vecs[i * board.size.w + j];
            board.bools[i * board.size.w + j] = vec2.x * board.equation.m + board.equation.q == vec2.y;
        }
    }
}

void draw_board(board_t board) {
    for (int i = 0; i < board.size.h; i++) {
        for (int j = 0; j < board.size.w; j++) {
            char to_print = i == board.size.h / 2 ? '-' : '.';
            to_print = j == board.size.w / 2 ? '|' : to_print;
            if (board.bools[i * board.size.w + j])
                printf("\033[41m%c\033[0m", to_print);
            else
                printf("%c", to_print);
        }
        putchar('\n');
    }
}