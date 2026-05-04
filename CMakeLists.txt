cmake_minimum_required(VERSION 4.2)
project(c_beans C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(c_beans
        main.c
        json_decoder.c
        owned_string.c
        reader.c
        task_parser.c
        tokenizer.c
        json_decoder.h
)
