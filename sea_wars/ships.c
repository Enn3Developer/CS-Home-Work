#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#include <malloc.h>
#include <string.h>
#include "ships.h"
#include "math.h"
#include "utils.h"

ship_t new_ship(int points, direction_t rotation, dict_t components) {
    ship_t new = {points, rotation, components};
    return new;
}

ship_t new_aircraft_carrier() {
    int points = 11;
    dict_t components = dict_new();

    dict_add(components, new_vec2(2, 0), 1);
    dict_add(components, new_vec2(3, 0), 1);
    dict_add(components, new_vec2(0, 1), 1);
    dict_add(components, new_vec2(1, 1), 1);
    dict_add(components, new_vec2(2, 1), 2);
    dict_add(components, new_vec2(3, 1), 2);
    dict_add(components, new_vec2(4, 1), 1);
    dict_add(components, new_vec2(2, 2), 1);
    dict_add(components, new_vec2(3, 2), 1);

    return new_ship(points, left, components);
}

ship_t new_cruiser() {
    int points = 8;
    dict_t components = dict_new();

    dict_add(components, new_vec2(0, 0), 1);
    dict_add(components, new_vec2(1, 0), 2);
    dict_add(components, new_vec2(2, 0), 1);
    dict_add(components, new_vec2(0, 1), 1);
    dict_add(components, new_vec2(1, 1), 2);
    dict_add(components, new_vec2(2, 1), 1);

    return new_ship(points, left, components);
}

ship_t new_minesweeper() {
    int point = 5;
    dict_t components = dict_new();

    dict_add(components, new_vec2(0, 0), 1);
    dict_add(components, new_vec2(1, 0), 1);
    dict_add(components, new_vec2(2, 0), 2);
    dict_add(components, new_vec2(3, 0), 1);

    return new_ship(point, left, components);
}

ship_t rotate_ship(ship_t ship, direction_t rotation) {
    if (rotation == ship.rotation)
        return ship;
    dict_t components = dict_new();
    if (rotation % 2 != ship.rotation % 2)  // i.e. ship_t is left, rotation is up or down
        for (int i = 0; i < ship.components->len; i++)
            dict_add(components, swap_vec2(ship.components->entry[i].key),
                     ship.components->entry[i].value);
    else
        components = dict_copy(ship.components);
    if (get_position_direction(rotation) !=
        get_position_direction(ship.rotation)) {  // i.e. ship_t is left, rotation is right or up
        int max_x = find_max_x(components);
        int max_y = find_max_y(components);
        for (int i = 0; i < components->len; i++) {
            components->entry[i].key.x = max_x - components->entry[i].key.x;
            components->entry[i].key.y = max_y - components->entry[i].key.y;
        }
    }

    return new_ship(ship.points, rotation, components);
}

vec2_t get_size_of_ship(ship_t ship) {
    int x = find_max_x(ship.components) + 1;
    int y = find_max_y(ship.components) + 1;
    return new_vec2(x, y);
}

int get_last_two_values_in_ship(ship_t ship) {
    int counter = 0;
    for (int i=0; i<ship.components->len; i++) {
        counter += ship.components->entry[i].value == 2;
    }

    return counter;
}

char *ship_to_str(ship_t ship, bool_t return_one, bool_t return_space) {
    char *str;
    int max_x = find_max_x(ship.components) + 1;
    int max_y = find_max_y(ship.components) + 1;
    str = malloc((max_x * 2) * max_y);
    for (int i = 0; i < max_y; i++) {
        for (int j = 0; j < max_x; j++) {
            char *element = malloc(2);
            int value = dict_find(ship.components, new_vec2(j, i), 0);
            sprintf(element, "%c ", ship_value_to_char(value, return_one, return_space));
            strcat(str, element);
        }
        str[(i + 1) * max_x * 2 - 1] = '\n';  // terminate each row with a new-line char
    }
    str[(max_y) * max_x * 2 - 1] = '\0';  // terminate the string with a NULL character

    return str;
}

bool_t ship_test() {
    ship_t aircraft = new_aircraft_carrier();
    printf("%s\n", ship_to_str(aircraft, true, false));

    printf("Asking the developer. Is the ship_t right? ");
    bool_t ok;
    scanf("%d", &ok);
    fflush(stdout);
    return ok;
}

bool_t rotation_test() {
    ship_t aircraft = new_aircraft_carrier();
    printf("Left:\n%s\n", ship_to_str(aircraft, true, false));
    printf("Down:\n%s\n", ship_to_str(rotate_ship(aircraft, down), true, false));
    printf("Right:\n%s\n", ship_to_str(rotate_ship(aircraft, right), true, false));
    printf("Up:\n%s\n", ship_to_str(rotate_ship(aircraft, up), true, false));

    printf("Asking the developer. Are the rotations right? ");
    bool_t ok;
    scanf("%d", &ok);
    fflush(stdout);
    return ok;
}