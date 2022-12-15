#ifndef INFO_ENEMY_H
#define INFO_ENEMY_H

#include "board.h"
#include "utils.h"

typedef enum {easy, normal, hard} difficulty_t;

typedef struct enemy {
    player_t player;
    difficulty_t difficulty;
    vec2_t *to_hit;
    bool_t previous_hit;
} enemy_t;

#endif //INFO_ENEMY_H