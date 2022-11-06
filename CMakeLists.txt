cmake_minimum_required(VERSION 3.21)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)

link_directories(./includes)

add_executable(untitled1
        srcs/main.c
        srcs/parser.c
        srcs/get_templates_from_files.c
        srcs/template_concatenation.c

        includes/grep.h
        )
