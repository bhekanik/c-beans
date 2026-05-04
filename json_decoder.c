#include "json_decoder.h"
#include "reader.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

json_object json_object_init() {
  const size_t capacity = 8;
  const json_object array = {.items = calloc(capacity, sizeof(key_value_pair)),
                            .length = 0,
                            .capacity = capacity};
  return array;
}

json_object *json_object_append(json_object *array, const key_value_pair item) {
  if (array == NULL) {
    printf("Array is null\n");
    exit(1);
  }
  if (array->length == array->capacity) {
    size_t new_capacity = array->capacity * 2;
    key_value_pair *temp =
        realloc(array->items, new_capacity * sizeof(key_value_pair));
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

void json_object_free(const json_object *array) {
  for (size_t i = 0; i < array->length; i++) {
    string_free(&array->items[i].key);
    if (array->items[i].value.kind == JSON_ARRAY) {
      string_array_free(&array->items[i].value.as.array_items);
    }
    free(array->items[i].value.as.string.text);
  }
  free(array->items);
}

number_array number_array_init() {
  const size_t capacity = 8;
  const number_array array = {.items = calloc(capacity, sizeof(float)),
                             .length = 0,
                             .capacity = capacity};
  return array;
}

number_array *number_array_append(number_array *array, const float item) {
  if (array == NULL) {
    printf("Array is null\n");
    exit(1);
  }
  if (array->length == array->capacity) {
    size_t new_capacity = array->capacity * 2;
    float *temp = realloc(array->items, new_capacity * sizeof(float));
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

void number_array_free(const number_array *array) { free(array->items); }

json_object create_json_keypairs(token_array *tokens) {
  if (tokens == NULL) {
    exit(1);
  }

  json_object json_object = json_object_init();
  for (size_t i = 0; i < tokens->length; i++) {
    if (tokens->items[i].kind == KEY) {
      if (DEBUG)
        printf("Key: %s\n", tokens->items[i].as.text.text);
      string key = tokens->items[i].as.text;

      i++; // move to COLON
      i++; // move to value

      if (tokens->items[i].kind == STRING) {
        if (DEBUG)
          printf("Value: %s\n\n", tokens->items[i].as.text.text);
        json_value value = {.kind = JSON_STRING,
                           .as.string = tokens->items[i].as.text};

        key_value_pair pair = {.key = key, .value = value};
        json_object_append(&json_object, pair);
      } else if (tokens->items[i].kind == NUMBER) {
        if (DEBUG)
          printf("Value: %f\n\n", tokens->items[i].as.number);
        json_value value = {.kind = JSON_NUMBER,
                           .as.number = tokens->items[i].as.number};

        key_value_pair pair = {.key = key, .value = value};
        json_object_append(&json_object, pair);
      } else if (tokens->items[i].kind == BOOLEAN) {
        if (DEBUG)
          printf("Value: %d\n\n", tokens->items[i].as.boolean);
        json_value value = {.kind = JSON_BOOLEAN,
                           .as.boolean = tokens->items[i].as.boolean};

        key_value_pair pair = {.key = key, .value = value};
        json_object_append(&json_object, pair);
      } else if (tokens->items[i].kind == NULL_VALUE) {
        if (DEBUG)
          printf("Value: NULL\n\n");
        json_value value = {.kind = JSON_NULL_VALUE};

        key_value_pair pair = {.key = key, .value = value};
        json_object_append(&json_object, pair);
      } else if (tokens->items[i].kind == OPENING_BRACKET) {
        if (DEBUG)
          printf("Value: ARRAY\n");
        string_array array_values = string_array_init();
        number_array array_numbers = number_array_init();

        i++; // skip first bracket
        char *strings_or_numbers = "strings";

        while (tokens->items[i].kind != CLOSING_BRACKET) {
          if (tokens->items[i].kind != COMMA) {
            // FIXME: only handling string value on arrays for now
            if (tokens->items[i].kind == STRING) {
              string_array_append(&array_values, tokens->items[i].as.text);
            }
            if (tokens->items[i].kind == NUMBER) {
              strings_or_numbers = "numbers";
              number_array_append(&array_numbers, tokens->items[i].as.number);
            }
          }
          i++;
        }
        if (DEBUG) {
          printf("ArrayValue: ");
          if (strcmp(strings_or_numbers, "numbers") == 0) {
            for (int j = 0; j < array_numbers.length; j++) {
              printf("%f ", array_numbers.items[j]);
            }
            printf("\n");
          } else {
            for (int j = 0; j < array_values.length; j++) {
              printf("%s\n", string_array_get(&array_values, j).text);
            }
          }
          printf("\n");
        }

        json_value value = {.kind = JSON_ARRAY, .as.array_items = array_values};
        if (strcmp(strings_or_numbers, "strings") != 0) {
          value = (json_value){.kind = JSON_ARRAY,
                              .as.array_numbers = array_numbers};
        }
        key_value_pair pair = {.key = key, .value = value};
        json_object_append(&json_object, pair);
      }
    }
  }

  return json_object;
}
