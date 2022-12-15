#ifndef INFO_DICT_H
#define INFO_DICT_H

#include "math.h"

typedef struct dict_entry_s {
    vec2_t key;
    int value;
} dict_entry_s;

typedef struct dict_s {
    int len;
    int cap;
    dict_entry_s *entry;
} dict_s, *dict_t;

int dict_find_index(dict_t dict, vec2_t key);

int dict_find(dict_t dict, vec2_t key, int def);

void dict_add(dict_t dict, vec2_t key, int value);

dict_t dict_new();

dict_t dict_copy(dict_t dict);

void dict_free(dict_t dict);

int find_max_x(dict_t components);

int find_max_y(dict_t components);

char *dict_to_str(dict_t dict);

#endif //INFO_DICT_H