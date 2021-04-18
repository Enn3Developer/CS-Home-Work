#ifndef INFO_CORE_H
#define INFO_CORE_H

typedef enum {
    false, true
} bool_t;

typedef enum type {
    line, parable
} equation_type_t;

typedef struct vec2 {
    double x, y;
} vec2_t;

typedef struct size {
    int w, h;
} win_size_t;

typedef struct equation_line {
    double m, q;
} equation_line_t;

typedef struct equation_parable {
    double a, b, c;
} equation_parable_t;

typedef struct equation {
    equation_type_t type;
    equation_line_t eq_l;
    equation_parable_t eq_p;
} equation_t;

typedef struct board {
    equation_t equation;
    win_size_t size;
    bool_t *bools;
} board_t;

vec2_t new_vec(double x, double y);

int vec2_to_index(vec2_t vec2, win_size_t size);

win_size_t get_terminal_size();

win_size_t get_win_size();

equation_type_t get_type();

equation_line_t get_equation_l();

equation_line_t zero_l();

equation_parable_t get_equation_p();

equation_parable_t zero_p();

equation_t get_equation();

win_size_t get_max_win(win_size_t size);

board_t new_board();

void compute_board(board_t board);

void draw_board(board_t board);

#endif