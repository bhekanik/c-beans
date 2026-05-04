#pragma once

#include <stdio.h>

typedef struct {
  char *text;
  size_t length;
  size_t capacity;
} string;

typedef struct {
  char *text;
  size_t length;
} string_slice;

string string_init(const char *input_string);

string string_from_range(const char *ptr, size_t length);

void string_free(const string *input_string);

void string_concat(string *string1, const string *string2);

const char *safe_string(const char *string);
