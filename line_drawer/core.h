#ifndef INFO_CORE_H
#define INFO_CORE_H

typedef enum {
    false, true
} bool_t;

typedef struct vec2 {
    float x, y;
} vec2_t;

typedef struct size {
    int w, h;
} win_size_t;

typedef struct equation {
    float m, q;
} equation_t;

typedef struct board {
    equation_t equation;
    win_size_t size;
    vec2_t *vecs;
    bool_t *bools;
} board_t;

vec2_t new_vec(float x, float y);

win_size_t get_terminal_size();

win_size_t get_win_size();

equation_t get_equation();

win_size_t get_max_win(win_size_t size);

board_t new_board();

void compute_board(board_t board);

void draw_board(board_t board);

#endif