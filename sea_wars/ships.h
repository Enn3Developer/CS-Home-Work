#ifndef INFO_SHIPS_H
#define INFO_SHIPS_H

#include "utils.h"
#include "dict.h"

typedef struct ship {
    int points;
    direction_t rotation;
    dict_t components;
} ship_t;

ship_t new_ship(int points, direction_t rotation, dict_t components);

ship_t new_aircraft_carrier();

ship_t new_cruiser();

ship_t new_minesweeper();

ship_t rotate_ship(ship_t ship, direction_t rotation);

vec2_t get_size_of_ship(ship_t ship);

int get_last_two_values_in_ship(ship_t ship);

char *ship_to_str(ship_t ship, bool_t return_one, bool_t return_space);

// Tests
bool_t ship_test();

bool_t rotation_test();

#endif //INFO_SHIPS_H