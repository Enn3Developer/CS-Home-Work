#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "board.h"
#include "dict.h"
#include "math.h"
#include "ships.h"
#include "utils.h"

cell_t new_cell(vec2_t start, ship_t ship) {
    cell_t cell = {start, ship};
    return cell;
}

void swap_cells(cell_t *a, cell_t *b) {
    cell_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void remove_cell(cell_t *cells, int *len, int index) {
    for (int i=0; i<*len; i++) {
        if (i > index)
            swap_cells(&cells[i], &cells[i-1]);
    }
    cell_t *tmp = malloc(*len * sizeof(cell_t));
    *len -= 1;
    for (int i=0; i<*len; i++) {
        tmp[i] = cells[i];
    }
    *cells = *tmp;
}

bool_t can_enter(int rows, int columns, int *ship_values[], vec2_t coordinate, vec2_t size) {
    vec2_t end_point = add_vec2(coordinate, size);
    if ((end_point.x >= columns) | (end_point.y >= rows) | (end_point.x < 0) |
        (end_point.y < 0))  // check if it can enter in the board
        return false;
    for (int i = coordinate.y; i < coordinate.y + size.y; i++)
        for (int j = coordinate.x; j < coordinate.x + size.x; j++)
            if (ship_values[i][j])  // 1 and 2 are ships, 0 is sea
                return false;

    return true;
}

vec2_t *get_start_points(int rows, int columns, int *ship_values[], vec2_t size, int *len) {
    *len = 0;
    int max_len = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            max_len += !ship_values[i][j];  // will increment only if the value is sea (0)
    vec2_t *points = malloc((max_len + 1) * sizeof(vec2_t));
    if (!max_len) {  // max_len == 0
        return points;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (!ship_values[i][j]) {
                vec2_t check = new_vec2(j, i);
                if (can_enter(rows, columns, ship_values, check, size)) {
                    points[*len] = check;
                    *len += 1;
                }
            }
        }
    }
    points = realloc(points, (*len + 1) * sizeof(vec2_t));

    return points;
}

void add_ship(int *ship_values[], cell_t *cells, cell_t cell, int *index) {
    cells[*index] = cell;
    *index += 1;
    vec2_t size = get_size_of_ship(cell.ship);
    for (int i = cell.start.y; i < cell.start.y + size.y; i++) {
        for (int j = cell.start.x; j < cell.start.x + size.x; j++) {
            int x = j - cell.start.x;
            int y = i - cell.start.y;
            ship_values[i][j] = dict_find(cell.ship.components, new_vec2(x, y), 0);
        }
    }
}

void add_ship_to_board(int rows, int columns, int *ship_values[], cell_t *cells, ship_t ship, int *index) {
    vec2_t size = get_size_of_ship(ship);
    int len;
    vec2_t *start_points = get_start_points(rows, columns, ship_values, size, &len);
    vec2_t point = start_points[random() % len];  // get a random point from an array of points
    cell_t cell = new_cell(point, ship);
    add_ship(ship_values, cells, cell, index);
}

void
add_all_ship(int rows, int columns, int aircraft, int cruiser, int minesweeper, int *ship_values[], cell_t *cells) {
    int index = 0;
    int i;

    for (i = 0; i < aircraft; i++) {
        reseed();
        direction_t rotation = random() % 4;
        ship_t ship = rotate_ship(new_aircraft_carrier(), rotation);
        add_ship_to_board(rows, columns, ship_values, cells, ship, &index);
    }

    for (i = 0; i < cruiser; i++) {
        reseed();
        direction_t rotation = random() % 4;
        ship_t ship = rotate_ship(new_cruiser(), rotation);
        add_ship_to_board(rows, columns, ship_values, cells, ship, &index);
    }

    for (i = 0; i < minesweeper; i++) {
        reseed();
        direction_t rotation = random() % 4;
        ship_t ship = rotate_ship(new_minesweeper(), rotation);
        add_ship_to_board(rows, columns, ship_values, cells, ship, &index);
    }
}

int fill_board(int rows, int columns, int aircraft, int cruiser, int minesweeper, int *ship_values[], cell_t *cells) {
    int len_cells = aircraft + cruiser + minesweeper;
    cells = malloc((len_cells + 1) * sizeof(cell_t));
    add_all_ship(rows, columns, aircraft, cruiser, minesweeper, ship_values, cells);

    return len_cells;
}

board_t new_board(config_t config) {
    int rows = config.rows, columns = config.columns;
    int aircraft = config.aircraft, cruiser = config.cruiser, minesweeper = config.minesweeper;
    int **ship_values;
    int *tmp;
    ship_values = malloc(rows * sizeof(*ship_values));
    tmp = malloc(rows * columns * sizeof(ship_values[0]));
    for (int i=0; i<rows; i++)
        ship_values[i] = tmp + (i * columns);
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            ship_values[i][j] = 0;
        }
    }
    cell_t *cells = NULL;
    int len_cells = fill_board(rows, columns, aircraft, cruiser, minesweeper, ship_values, cells);
    board_t board = {rows, columns, len_cells, cells, ship_values};
    return board;
}

vec2_t from_board_vec_to_cell_vec(vec2_t vec2, cell_t cell) {
    return sub_vec2(vec2, cell.start);
}

int get_cell_index_from_vec2(board_t board, vec2_t vec) {
    for (int i=0; i<board.len_cells; i++)
        if (is_vec2_inside_area(vec, board.cells[i].start, get_size_of_ship(board.cells[i].ship)))
            return i;

    return -1;
}

bool_t hit_board(player_t hitter, board_t board, vec2_t vec2) {
    if (!board.ship_values[vec2.y][vec2.x]) {
        board.ship_values[vec2.y][vec2.x] += 3;
        return false;
    }
    else {
        int index_cell = get_cell_index_from_vec2(board, vec2);
        board.ship_values[vec2.y][vec2.x] = 4;
        if (index_cell >= 0) {
            vec2_t vec_cell = from_board_vec_to_cell_vec(vec2, board.cells[index_cell]);
            int ship_value = dict_find(board.cells[index_cell].ship.components, vec_cell, 0);
            if ((ship_value == 2) & get_last_two_values_in_ship(board.cells[index_cell].ship)) {
                hitter.points += board.cells[index_cell].ship.points;
                for (int i=0; i<board.cells[index_cell].ship.components->len; i++) {
                    vec2_t vec = add_vec2(board.cells[i].start, board.cells[index_cell].ship.components->entry[i].key);
                    board.ship_values[vec.y][vec.x] = board.ship_values[vec.y][vec.x] == 4 ? 4 : 0;
                }
                remove_cell(board.cells, &board.len_cells, index_cell);
            }
        }
        else {
            exit(1);
        }
        return true;
    }
}

char *board_to_str(board_t board) {
    // simplified by hand
    int size = 2 * (8 + 2 * board.columns + board.rows * (3 + 2 * board.columns));  // the size of the board
    char *str = malloc(size);
    int index = 0;
    for (int i=0; i<3; i++) {
        str[index] = ' ';
        index++;
    }
    for (int i=1; i<=board.columns; i++) {
        char *tmp = malloc(3);
        sprintf(tmp, "%d ", i);
        strcat(str, tmp);
        index += 2;
    }
    index++;
    str[index] = '\n';
    index++;
//  ------------------------------------------------------------------------
//  Print the rows letters + the board
    for (int i=0; i<board.rows; i++) {
        char *tmp = malloc(3);
        sprintf(tmp, "%c: ", int_to_char(i));
        strcat(str, tmp);
        index += 3;
        for (int j=0; j<board.columns; j++) {
            tmp = realloc(tmp, 2);
            sprintf(tmp, "%c ", ship_value_to_char(board.ship_values[i][j], true, false));
            strcat(str, tmp);
            index += 2;
        }
        str[index] = '\n';
        index++;
    }
//  ------------------------------------------------------------------------
    return str;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
bool_t board_test() {
    config_t config = {10, 10, 1, 2, 2};
    board_t board = new_board(config);
    printf("%s\n", board_to_str(board));
    printf("Asking the developer. Is the board right? ");
    bool_t ok;
    scanf("%d", &ok);
    fflush(stdout);
    return ok;
}
#pragma clang diagnostic pop