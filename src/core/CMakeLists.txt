add_library(beans_core STATIC
    empty.c
)

target_include_directories(beans_core
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)
