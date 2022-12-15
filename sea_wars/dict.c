#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "math.h"
#include "dict.h"

int dict_find_index(dict_t dict, vec2_t key) {
    for (int i = 0; i < dict->len; i++) {
        if (is_equal_vec2(dict->entry[i].key, key)) {
            return i;
        }
    }
    return -1;
}

int dict_find(dict_t dict, vec2_t key, int def) {
    int idx = dict_find_index(dict, key);
    return idx == -1 ? def : dict->entry[idx].value;
}

void dict_add(dict_t dict, vec2_t key, int value) {
    int idx = dict_find_index(dict, key);
    if (idx != -1) {
        dict->entry[idx].value = value;
        return;
    }
    if (dict->len == dict->cap) {
        dict->cap *= 2;
        dict->entry = realloc(dict->entry, dict->cap * sizeof(dict_entry_s));
    }
    dict->entry[dict->len].key = key;
    dict->entry[dict->len].value = value;
    dict->len++;
}

dict_t dict_new() {
    dict_s proto = {0, 10, malloc(10 * sizeof(dict_entry_s))};
    dict_t d = malloc(sizeof(dict_s));
    *d = proto;
    return d;
}

dict_t dict_copy(dict_t dict) {
    dict_t copy = dict_new();
    for (int i = 0; i < dict->len; i++)
        dict_add(copy, dict->entry[i].key, dict->entry[i].value);

    return copy;
}

void dict_free(dict_t dict) {
    for (int i = 0; i < dict->len; i++) {
        free(&dict->entry[i].key);
    }
    free(dict->entry);
    free(dict);
}

int find_max_x(dict_t components) {
    int max_x = components->entry[0].key.x;
    for (int i = 0; i < components->len; i++) {
        max_x = max_x >= components->entry[i].key.x ? max_x : components->entry[i].key.x;
    }
    return max_x;
}

int find_max_y(dict_t components) {
    int max_y = components->entry[0].key.y;
    for (int i = 0; i < components->len; i++) {
        max_y = max_y >= components->entry[i].key.y ? max_y : components->entry[i].key.y;
    }
    return max_y;
}

char *dict_to_str(dict_t dict) {
    char *str;
    int space_left = 99;
    int total_size = space_left + 3;
    str = malloc(total_size);
    str[0] = '{';
    for (int i = 0; i < dict->len; i++) {
        char *vec_str = vec2_to_str(dict->entry[i].key);
        char *value_str = malloc(6);
        sprintf(value_str, " = %d, ", dict->entry[i].value);
        int size_vec = (int) strlen(vec_str);
        check_space:
        {
            if (space_left >= size_vec + 5) {  // 5 because above (without the last space)
                strcat(str, vec_str);
                strcat(str, value_str);
                space_left -= size_vec + 5;
            } else {
                char *tmp_str = realloc(str, total_size + (size_vec + 5 - space_left));
                total_size += (size_vec + 5 - space_left);
                space_left = 0;
                str = tmp_str;
                goto check_space;
            }
        }
    }
    clean_str:
    {
        if (!space_left) {
            str[total_size - 3] = '}';
            str[total_size - 2] = '\0';
            // the str is NULL-terminated, so I can't modify the last char
        } else {
            char *tmp_str = realloc(str, total_size - space_left);
            total_size -= space_left;
            space_left = 0;
            str = tmp_str;
            goto clean_str;
        }
    }

    return str;
}