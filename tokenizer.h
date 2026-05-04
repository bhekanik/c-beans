#pragma once

#include <stdbool.h>
#include <stdio.h>
#include "owned_string.h"

typedef enum {
    OPENING_BRACE,
    CLOSING_BRACE,
    OPENING_BRACKET,
    CLOSING_BRACKET,
    COMMA,
    COLON,
    KEY,
    STRING,
    NUMBER,
    BOOLEAN,
    NULL_VALUE,
} token_kind;

typedef struct {
    token_kind kind;

    union {
        string text;
        float number;
        bool boolean;
    } as;
} token;

typedef struct {
    token *items;
    size_t length;
    size_t capacity;
} token_array;

token_array token_array_init();

token_array *token_array_append(token_array *array, token item);

token *token_array_get(const token_array *array, size_t index);

void token_array_free(const token_array *array);

token_array tokenize(string line_str);
