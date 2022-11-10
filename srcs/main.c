//
// Created by Oznak Banshee on 11/2/22.
//

#include "../includes/grep.h"

int main (int argc, char* argv[]) {
    Options opt = {0};
    char** template_arr = (char **) calloc(argc - 1, sizeof(char*));
    int true = 0;
    char** files_arr = (char **) calloc(argc - 1, sizeof(char*));
    if (template_arr == NULL) {
        exit(1);
    }
    int temp_count = 0;
    int files_count = 0;
    if (parser(argc, argv, &opt, &template_arr, files_arr, &temp_count, &files_count)) {
        printf("templates %d\n", temp_count);
        for (int i = 0; i < temp_count; i ++) {
            printf("    '%s'\n", template_arr[i]);
        }
        printf("files %d\n", files_count);
        for (int i = 0; i < files_count; i ++) {
            printf("file -    '%s'\n", files_arr[i]);
        }
    } else {
        printf("ERROR");
    }
    for (int i = 0; i < temp_count; i ++) {
        free(template_arr[i]);
    }
    free(template_arr);
    free(files_arr);
}

/* int main (int argc, char* argv[]) {
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
 */

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

