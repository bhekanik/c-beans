#pragma once
#include <stdbool.h>
#include "tokenizer.h"
#include "reader.h"

typedef enum {
    JSON_STRING,
    JSON_NUMBER,
    JSON_BOOLEAN,
    JSON_NULL_VALUE,
    JSON_ARRAY,
} json_value_kind;

typedef struct {
    float *items;
    size_t length;
    size_t capacity;
} number_array;

typedef struct {
    json_value_kind kind;

    union {
        string string;
        double number;
        bool boolean;
        string_array array_items;
        number_array array_numbers;
    } as;
} json_value;

typedef struct {
    string key;
    json_value value;
} key_value_pair;

typedef struct {
    key_value_pair *items;
    size_t length;
    size_t capacity;
} json_object;

json_object json_object_init(void);

json_object *json_object_append(json_object *array, key_value_pair item);

void json_object_free(const json_object *array);

number_array number_array_init(void);

number_array *number_array_append(number_array *array, float item);

void number_array_free(const number_array *array);

json_object create_json_keypairs(token_array *tokens);
