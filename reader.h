#pragma once

#include "owned_string.h"

typedef struct {
    string *items;
    size_t length;
    size_t capacity;
} string_array;

string_array string_array_init();

string_array *string_array_append(string_array *array, string item);

string string_array_get(const string_array *array, size_t index);

void string_array_free(const string_array *array);

string_array read_file(const char *filename);
