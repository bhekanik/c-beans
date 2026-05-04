#include "task_parser.h"

int main() {
    const task_array tasks = read_tasks("../tasks.jsonl");

    for (size_t i = 0; i < tasks.length; i++) {
        print_task(&tasks.items[i]);
        // pretty_print_task(&tasks.items[i]);
    }

    task_array_free(&tasks);

    return 0;
}
