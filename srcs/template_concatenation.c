//
// Created by Oznak Banshee on 11/6/22.
//

#include "../includes/grep.h"

char** template_concatenation(char** files_templates, char** arg_templates, int max_arg_count) {
    int count_files_templates = 0;
    int count_arg_templates = 0;
    while(files_templates[count_files_templates]) {
        count_files_templates++;
    }
    while(arg_templates[count_arg_templates]) {
        count_arg_templates++;
    }
    printf("count_files_templates - %d\n",count_files_templates);
    printf("count_arg_templates - %d",count_arg_templates);
    return arg_templates;
}
