#include "owned_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string string_init(const char *input_string) {
  const size_t string_length = strlen(input_string);
  const string string = {.text = calloc(string_length + 1, sizeof(char)),
                         .length = string_length,
                         .capacity = string_length + 1};
  memcpy(string.text, input_string, string_length);
  return string;
}

string string_from_range(const char *ptr, size_t length) {
  const string string = {.text = calloc(length + 1, sizeof(char)),
                         .length = length,
                         .capacity = length + 1};
  memcpy(string.text, ptr, length);
  return string;
}

void string_free(const string *input_string) { free(input_string->text); };

void string_concat(string *string1, const string *string2) {
  if (string1->length + string2->length + 1 > string1->capacity) {
    char *temp = realloc(string1->text, string1->length + string2->length + 1);
    if (temp == NULL) {
      fprintf(stderr, "Error reallocating memory");
      exit(1);
    }
    string1->text = temp;
    string1->capacity = string1->length + string2->length + 1;
  }

  memcpy(string1->text + string1->length, string2->text, string2->length);
  string1->text[string1->length + string2->length] = '\0';
  string1->length += string2->length;
}

const char *safe_string(const char *string) {
  return string == NULL ? "(null)" : string;
}
