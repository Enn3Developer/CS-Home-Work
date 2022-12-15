#include "board.h"

player_t new_player(const char *name, board_t board, int points) {
    player_t player = {name, board, points};
    return player;
}

player_t create_player(const char *name, config_t config) {
    board_t board = new_board(config);
    return new_player(name, board, 0);
}