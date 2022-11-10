//
// Created by Oznak Banshee on 11/2/22.
//

#include "../includes/grep.h"

void print_opt(Options opt);

int main(int argc, char *argv[]) {
    Options opt = {0};
    char** template_arr = (char **) calloc(argc - 1, sizeof(char*));
    int true = 0;
    char** files_arr = (char **) calloc(argc - 1, sizeof(char*));
    if (template_arr == NULL || files_arr == NULL) {
        exit(1);
    }
    int temp_count = 0;
    int files_count = 0;
    if (parser(argc, argv, &opt, &template_arr, files_arr, &temp_count, &files_count)) {
        output(temp_count, files_count, template_arr, files_arr, opt);

                /* printf("templates %d\n", temp_count);
                for (int i = 0; i < temp_count; i ++) {
                    printf("    '%s'\n", template_arr[i]);
                }
                printf("files %d\n", files_count);
                for (int i = 0; i < files_count; i ++) {
                    printf("file -    '%s'\n", files_arr[i]);
                } */
    } else {
        printf("ERROR");
    }
    for (int i = 0; i < temp_count; i ++) {
        free(template_arr[i]);
    }
    free(template_arr);
    free(files_arr);
}


void print_opt(Options opt) {
    printf("e: %d\n", opt.e);
    printf("i: %d\n", opt.i);
    printf("v: %d\n", opt.v);
    printf("c: %d\n", opt.c);
    printf("l: %d\n", opt.l);
    printf("n: %d\n", opt.n);
    printf("h: %d\n", opt.h);
    printf("s: %d\n", opt.s);
    printf("f: %d\n", opt.f);
    printf("o: %d\n", opt.o);
}

