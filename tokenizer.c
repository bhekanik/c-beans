#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "owned_string.h"
#include "tokenizer.h"

#define DEBUG 1

token_array token_array_init() {
    const size_t capacity = 8;
    const token_array array = {
        .items = calloc(capacity, sizeof(token)),
        .length = 0,
        .capacity = capacity
    };
    return array;
}

token_array *token_array_append(token_array *array, const token item) {
    if (array == NULL) {
        fprintf(stderr, "Array is null\n");
        exit(1);
    }
    if (array->length == array->capacity) {
        const size_t new_capacity = array->capacity * 2;
        token *temp = realloc(array->items, new_capacity * sizeof(token));
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

token *token_array_get(const token_array *array, const size_t index) {
    if (index >= array->length) {
        fprintf(stderr, "Index out of bounds");
        exit(1);
    }
    return &array->items[index];
}

void token_array_free(const token_array *array) {
    for (size_t i = 0; i < array->length; i++) {
        if (array->items[i].kind == STRING) {
            string_free(&array->items[i].as.text);
        }
        if (array->items[i].kind == KEY) {
            string_free(&array->items[i].as.text);
        }
    }
    free(array->items);
}

token_array tokenize(const string line_str) {
    char *line = line_str.text;
    token_array tokens = token_array_init();

    bool in_array = false;
    size_t length = strlen(line);
    for (int j = 0; j < length; j++) {
        char c = line[j];

        if (isspace((unsigned char) c)) {
            continue;
        } else if (c == '{') {
            if (DEBUG) printf("OPENING BRACE\n");
            token opening_brace = {.kind = OPENING_BRACE};
            token_array_append(&tokens, opening_brace);
        } else if (c == '}') {
            if (DEBUG) printf("CLOSING BRACE\n");
            token closing_brace = {.kind = CLOSING_BRACE};
            token_array_append(&tokens, closing_brace);
        } else if (c == '[') {
            if (DEBUG) printf("OPENING BRACKET\n");
            token opening_bracket = {.kind = OPENING_BRACKET};
            token_array_append(&tokens, opening_bracket);
            in_array = true;
        } else if (c == ']') {
            if (DEBUG) printf("CLOSING BRACKET\n");
            token closing_bracket = {.kind = CLOSING_BRACKET};
            token_array_append(&tokens, closing_bracket);
            in_array = false;
        } else if (c == 'n') {
            int start = j;
            while (
                line[j] != '\0' &&
                line[j] != ',' &&
                line[j] != ']' &&
                line[j] != '}' &&
                !isspace((unsigned char) line[j])) {
                j++;
            }
            string value = string_from_range(&line[start], j - start);
            j--;

            if (strcmp(value.text, "null") == 0) {
                if (DEBUG) printf("NULL\n");
                token null = {.kind = NULL_VALUE};
                token_array_append(&tokens, null);
            }
        } else if (c == 't' || c == 'f') {
            int start = j;
            while (
                line[j] != '\0' &&
                line[j] != ',' &&
                line[j] != ']' &&
                line[j] != '}' &&
                !isspace((unsigned char) line[j])) {
                j++;
            }
            string value = string_from_range(&line[start], j - start);
            j--;

            if (strcmp(value.text, "false") == 0 || strcmp(value.text, "true") == 0) {
                if (DEBUG) printf("BOOLEAN: %s\n", value.text);
                token null = {.kind = BOOLEAN, .as.boolean = (strcmp(value.text, "true") == 0)};
                token_array_append(&tokens, null);
            }
        } else if (c == ',') {
            if (DEBUG) printf("COMMA\n");
            token comma = {.kind = COMMA};
            token_array_append(&tokens, comma);
        } else if (c == ':') {
            if (DEBUG) printf("COLON\n");
            token colon = {.kind = COLON};
            token_array_append(&tokens, colon);
        } else if (isdigit((unsigned char) c) || c == '-') {
            int start = j;
            while (isdigit((unsigned char) line[j]) || line[j] == '.' ||
                   line[j] == 'e' || line[j] == 'E' ||
                   line[j] == '+' || line[j] == '-') {
                j++;
            }
            char *num_str = strndup(&line[start], j - start);
            float value = strtof(num_str, NULL);
            free(num_str);
            j--;

            if (DEBUG) printf("NUMBER: %f\n", value);
            token array = {.kind = NUMBER, .as.number = value};
            token_array_append(&tokens, array);
        } else if (c == '"') {
            // FIXME: Intentionally not handling escapes yet

            if (tokens.length == 0) {
                fprintf(stderr, "Unexpected token");
                exit(1);
            }

            token *tokenBefore = token_array_get(&tokens, tokens.length - 1);

            j++;
            int start = j;
            while (line[j] != '\0' && line[j] != '"') {
                j++;
            }
            string value = string_from_range(&line[start], j - start);

            if (tokenBefore->kind == OPENING_BRACE || (tokenBefore->kind == COMMA && !in_array)) {
                if (DEBUG) printf("KEY: %s\n", value.text);
                token array = {.kind = KEY, .as.text = value};
                token_array_append(&tokens, array);
            } else if (tokenBefore->kind == COLON || tokenBefore->kind == OPENING_BRACKET || (
                           tokenBefore->kind == COMMA && in_array)) {
                if (DEBUG) printf("STRING: %s\n", value.text);
                token string = {.kind = STRING, .as.text = value};
                token_array_append(&tokens, string);
            }
        }
    }

    return tokens;
}
