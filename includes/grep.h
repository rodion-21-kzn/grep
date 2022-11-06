//
// Created by Oznak Banshee on 11/6/22.
//

#ifndef UNTITLED1_GREP_H
#define UNTITLED1_GREP_H

#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

typedef struct Options{
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
}Options;

void print_opt(Options opt);
int parser(int argc, char* argv[], Options* opt, char** template_arr, char** template_files, char** files_arr, int* temp_count, int* files_count);
int opt_f_func(char* file_name, char** buffer, int* temp_count);

#endif //UNTITLED1_GREP_H
