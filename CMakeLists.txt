cmake_minimum_required(VERSION 3.21)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)

link_directories(./includes)

add_executable(untitled1
        srcs/main.c
        includes/grep.h
        srcs/parser.c)
