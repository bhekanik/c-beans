#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "json_decoder.h"
#include "task_parser.h"

task_array task_array_init() {
    const size_t capacity = 8;
    const task_array array = {
        .items = calloc(capacity, sizeof(task)),
        .length = 0,
        .capacity = capacity
    };
    return array;
}

task_array *task_array_append(task_array *array, task item) {
    if (array == NULL) {
        fprintf(stderr, "Array is null\n");
        exit(1);
    }
    if (array->length == array->capacity) {
        const size_t new_capacity = array->capacity * 2;
        task *temp = realloc(array->items, new_capacity * sizeof(task));
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

void task_array_free(const task_array *array) {
    for (size_t i = 0; i < array->length; i++) {
        task_free(&array->items[i]);
    }
    free(array->items);
}

void task_free(const task *task) {
    string_free(&task->id);
    string_free(&task->project);
    string_free(&task->epic);
    string_free(&task->title);
    string_free(&task->description);
    string_free(&task->status);
}

task *parse_task(const string_array *lines, const size_t index) {
    token_array tokens = tokenize(string_array_get(lines, index));
    const json_object json_object = create_json_keypairs(&tokens);

    task *task = malloc(sizeof(task));
    for (size_t i = 0; i < json_object.length; i++) {
        if (strcmp(json_object.items[i].key.text, "id") == 0) {
            task->id = string_init(json_object.items[i].value.as.string.text);
        } else if (strcmp(json_object.items[i].key.text, "project") == 0) {
            task->project = string_init(json_object.items[i].value.as.string.text);
        } else if (strcmp(json_object.items[i].key.text, "epic") == 0) {
            task->epic = string_init(json_object.items[i].value.as.string.text);
        } else if (strcmp(json_object.items[i].key.text, "title") == 0) {
            task->title = string_init(json_object.items[i].value.as.string.text);
        } else if (strcmp(json_object.items[i].key.text, "description") == 0) {
            task->description = string_init(json_object.items[i].value.as.string.text);
        } else if (strcmp(json_object.items[i].key.text, "status") == 0) {
            task->status = string_init(json_object.items[i].value.as.string.text);
        } else if (strcmp(json_object.items[i].key.text, "priority") == 0) {
            task->priority = (int) json_object.items[i].value.as.number;
        } else if (strcmp(json_object.items[i].key.text, "depends_on") == 0) {
            task->depends_on = json_object.items[i].value.as.array_items;
        } else if (strcmp(json_object.items[i].key.text, "tags") == 0) {
            task->tags = json_object.items[i].value.as.array_items;
        } else if (strcmp(json_object.items[i].key.text, "acceptance_criteria") == 0) {
            task->acceptance_criteria = json_object.items[i].value.as.array_items;
        }
    }

    // json_object_free(&json_object);
    return task;
}

task_array read_tasks(const char *filename) {
    const string_array lines = read_file(filename);
    task_array tasks = task_array_init();

    for (size_t i = 0; i < lines.length; i++) {
        const task *task = parse_task(&lines, i);
        task_array_append(&tasks, *task);
    }

    return tasks;
}

char *print_array(string_array array) {
    string string = string_init("[ ");
    for (size_t i = 0; i < array.length; i++) {
        string array_item = string_init(array.items[i].text);
        string_concat(&string, &array_item);
        string_free(&array_item);
        if (i < array.length - 1) {
            string comma = string_init(", ");
            string_concat(&string, &comma);
            string_free(&comma);
        }
    }
    const string close_bracket = string_init(" ]");
    string_concat(&string, &close_bracket);
    string_free(&close_bracket);
    return string.text;
}

void print_task(const task *task) {
    printf("{\n");
    printf("\tid: \"%s\",\n", safe_string(task->id.text));
    printf("\tproject: \"%s\",\n", safe_string(task->project.text));
    printf("\tepic: \"%s\",\n", safe_string(task->epic.text));
    printf("\ttitle: \"%s\",\n", safe_string(task->title.text));
    printf("\tdescription: \"%s\",\n", safe_string(task->description.text));
    printf("\tstatus: \"%s\",\n", safe_string(task->status.text));
    printf("\tpriority: %d,\n", task->priority);
    printf("\tdepends_on: %s,\n", print_array(task->depends_on));
    printf("\ttags: %s,\n", print_array(task->tags));
    printf("\tacceptance_criteria: %s\n", print_array(task->acceptance_criteria));
    printf("}\n");
}

void pretty_print_task(const task *task) {
    printf(
        "\nTask: P%d %s/%s (%s)\n",
        task->priority,
        safe_string(task->epic.text),
        safe_string(task->title.text),
        safe_string(task->status.text)
    );
    printf("project: %s\n", safe_string(task->project.text));
    printf("description: %s\n", safe_string(task->description.text));
    printf("dependencies: %s\n", print_array(task->depends_on));
    printf("tags: %s\n", print_array(task->tags));
    printf("acceptance_criteria: %s\n", print_array(task->acceptance_criteria));
}
