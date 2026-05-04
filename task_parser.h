#pragma once

#include "json_decoder.h"

typedef struct {
    string id;
    string project;
    string epic;
    string title;
    string description;
    string status;
    int priority;
    string_array depends_on;
    string_array tags;
    string_array acceptance_criteria;
} task;

typedef struct {
    task *items;
    size_t length;
    size_t capacity;
} task_array;

task_array task_array_init();

task_array *task_array_append(task_array *array, task item);

void task_array_free(const task_array *array);

void task_free(const task *task);

task *parse_task(const string_array *lines, size_t index);

task_array read_tasks(const char *filename);

char *print_array(string_array array);

void print_task(const task *task);

void pretty_print_task(const task *task);
