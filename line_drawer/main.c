#include "core.h"

// create a geogebra-like app that can only draw a straight line (`y=mx+q`)
// added: draw a parabola (`y=ax²+bx+c`)

int main() {
    board_t board = new_board();
    compute_board(board);
    draw_board(board);

    return 0;
}