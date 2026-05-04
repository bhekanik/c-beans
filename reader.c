#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "owned_string.h"
#include "reader.h"

string_array string_array_init() {
    const size_t capacity = 8;
    const string_array array = {
        .items = calloc(capacity, sizeof(string)),
        .length = 0,
        .capacity = capacity
    };
    return array;
}

string_array *string_array_append(string_array *array, const string item) {
    if (array == NULL) {
        fprintf(stderr, "Array is null\n");
        exit(1);
    }
    if (array->length == array->capacity) {
        size_t new_capacity = array->capacity * 2;
        string *temp = realloc(array->items, new_capacity * sizeof(string));
        if (temp == NULL) {
            fprintf(stderr, "Error reallocating memory");
            exit(1);
        }
        array->items = temp;
        array->capacity = new_capacity;
    }
    array->items[array->length] = item;
    array->length++;
    return array;
}

string string_array_get(const string_array *array, const size_t index) {
    if (index >= array->length) {
        perror("Index out of bounds");
        exit(1);
    }
    return array->items[index];
}

void string_array_free(const string_array *array) {
    for (size_t i = 0; i < array->length; i++) {
        string_free(&array->items[i]);
    }
    free(array->items);
};

string_array read_file(const char *filename) {
    FILE *tasks = fopen(filename, "r");

    if (tasks == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;

    string_array lines = string_array_init();

    while (getline(&line, &len, tasks) != -1) {
        const string line_string = string_init(line);
        string_array_append(&lines, line_string);
    }

    free(line);
    fclose(tasks);

    return lines;
}
