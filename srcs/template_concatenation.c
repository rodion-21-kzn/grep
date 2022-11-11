//
// Created by Oznak Banshee on 11/6/22.
//

#include "../includes/grep.h"

void template_concatenation(char** files_templates, char** arg_templates) {
    int count_files_templates = 0;
    int count_arg_templates = 0;
    while(files_templates[count_files_templates]) {
        count_files_templates++;
    }
    while(arg_templates[count_arg_templates]) {
        count_arg_templates++;
    }
    for (int i = 0; i < count_files_templates; i++) {
        arg_templates[count_arg_templates+i] =  files_templates[i];
    }
}

/*
char** template_concatenation(char** files_templates, char** arg_templates, int max_arg_count) {
    int count_files_templates = 0;
    int count_arg_templates = 0;
    int count_all_templates = 0;
    while(files_templates[count_files_templates]) {
        count_files_templates++;
        count_all_templates++;
    }
    while(arg_templates[count_arg_templates]) {
        count_arg_templates++;
        count_all_templates++;
    }
    arg_templates = realloc(arg_templates, count_all_templates*sizeof(char*));
    for (int i = 0; i < count_files_templates; i++) {
        arg_templates[count_arg_templates+i] = files_templates[i];
    }
    for (int i = 0; i < count_all_templates; i++) {
        printf("%s\n", arg_templates[i]);
    }
    printf("count_files_templates - %d\n",count_files_templates);
    printf("count_arg_templates - %d",count_arg_templates);
    return arg_templates;
}
*/