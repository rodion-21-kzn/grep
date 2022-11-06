//
// Created by Oznak Banshee on 11/2/22.
//

#include "../includes/grep.h"
#define ALLOC_BASE 100

char** get_templates_from_files(char **template_files) {
    int i = 0;
    int template_max_count = ALLOC_BASE;
    int template_count = 0;
    FILE* f;
    char** templates = (char **) calloc (ALLOC_BASE, sizeof(char *));
    char* pattern = NULL;
    size_t len = 1024;
    while(template_files[i]) {
        f = fopen(template_files[i], "r");
        printf("\"%s\" - %p\n", template_files[i], f);
        if (f == NULL) {
            exit(1);
        } else {
            while (getline(&pattern, &len, f) != EOF) {
                pattern[strlen(pattern) - 1]  == '\n' ? pattern[strlen(pattern) - 1]  = '\0' : 0; // для того, чтобы в шаблон не попадал символ переноса строки
                templates[template_count] = pattern;
                template_count++;
                if (template_count >= template_max_count) {
                    template_max_count+= ALLOC_BASE;
                    templates = realloc(templates, template_max_count*sizeof(char *));
                }
            }
        }
        i++;
    }
    templates[template_count] = NULL;
    return templates;
}

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

int main (int argc, char* argv[]) {
    Options opt = {0};
    char** templates_from_file;
    char** template_arr = (char **) calloc(argc - 1, sizeof(char*));
    char** template_files = (char **) calloc(argc - 1, sizeof(char*));
    char** files_arr = (char **) calloc(argc - 1, sizeof(char*));
    if (template_arr == NULL || template_files == NULL || files_arr == NULL) {
        exit(1);
    }
    int temp_count = 0;
    int files_count = 0;
    if (parser(argc, argv, &opt, template_arr, template_files, files_arr, &temp_count, &files_count)) {
        printf("%d\n", temp_count);
        printf("%d\n", files_count);
        for (int i = 0; i < temp_count; i ++) {
           printf("t - %s ", template_arr[i]);
        }
        printf("\n");
        for (int i = 0; i < files_count; i ++) {
           printf("f - %s ", files_arr[i]);
        }
        int i = 0;
        // while (template_files[i]) { printf("   tem-f- %s\n", template_files[i]); i++;}
        templates_from_file = get_templates_from_files(template_files);
        template_arr = template_concatenation(templates_from_file, template_arr, argc - 1);
    } else {
        printf("ERROR");
    }
}
void print_opt(Options opt) {
    printf("e: %d\n", opt.e);
    printf("i: %d\n", opt.i);
    printf("v: %d\n", opt.v);
    printf("c: %d\n", opt.c);
    printf("l: %d\n", opt.l);
    printf("n: %d\n", opt.n);
    printf("c: %d\n", opt.h);
    printf("l: %d\n", opt.s);
    printf("n: %d\n", opt.f);
    printf("n: %d\n", opt.o);
}

