#ifndef INFO_BOARD_H
#define INFO_BOARD_H

#include "math.h"
#include "ships.h"

typedef struct config {
    int rows, columns;
    int aircraft, cruiser, minesweeper;
} config_t;

typedef struct cell {
    vec2_t start;
    ship_t ship;
} cell_t;

typedef struct board {
    int rows, columns;
    int len_cells;
    cell_t *cells;
    int **ship_values;
} board_t;

typedef struct player {
    const char *name;
    board_t board;
    int points;
} player_t;

player_t new_player(const char *name, board_t board, int points);

player_t create_player(const char *name, config_t config);

cell_t new_cell(vec2_t start, ship_t ship);

void swap_cells(cell_t *a, cell_t *b);

void remove_cell(cell_t *cells, int *len, int index);

bool_t can_enter(int rows, int columns, int *ship_values[], vec2_t coordinate, vec2_t size);

vec2_t *get_start_points(int rows, int columns, int *ship_values[], vec2_t size, int *len);

void add_ship(int *ship_values[], cell_t *cells, cell_t cell, int *index);

void add_ship_to_board(int rows, int columns, int *ship_values[], cell_t *cells, ship_t ship, int *index);

void add_all_ship(int rows, int columns, int aircraft, int cruiser, int minesweeper, int *ship_values[], cell_t *cells);

int fill_board(int rows, int columns, int aircraft, int cruiser, int minesweeper, int *ship_values[], cell_t *cells);

board_t new_board(config_t config);

vec2_t from_board_vec_to_cell_vec(vec2_t vec2, cell_t cell);

int get_cell_index_from_vec2(board_t board, vec2_t vec);

bool_t hit_board(player_t hitter, board_t board, vec2_t vec2);

char *board_to_str(board_t board);

// Tests
bool_t board_test();

#endif //INFO_BOARD_H