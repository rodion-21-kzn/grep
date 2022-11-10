//
// Created by Oznak Banshee on 11/6/22.
//


#include "../includes/grep.h"

char** get_templates_from_files(char *file_name, int *temp_count) {
    int i = 0;
    int template_max_count = ALLOC_BASE;
    int template_count = 0;
    char *pattern_alloc = NULL;
    FILE* f;
    char **templates = (char **) calloc(ALLOC_BASE, sizeof(char *));
    char *pattern = NULL;
    size_t len = 1024;
    f = fopen(file_name, "r");
    if (f == NULL) {
        exit(1);
    }
    while (getline(&pattern, &len, f) != EOF) {
        if (pattern[0] == '\n') {
            continue;
        }
        pattern[strlen(pattern) - 1] == '\n' ? pattern[strlen(pattern) - 1] = '\0'
                                             : 0; // для того, чтобы в шаблон не попадал символ переноса строки
        pattern_alloc = calloc(strlen(pattern) + 1, sizeof(char));
        if (pattern_alloc == NULL) {
            printf("error", stderr); // марат (я) не рекомендует
            exit(1);
        }
        strcpy(pattern_alloc, pattern);
        templates[template_count] = pattern_alloc;
        template_count++;
        *temp_count = *temp_count + 1;
        if (template_count >= template_max_count) {
            template_max_count += ALLOC_BASE;
            templates = realloc(templates, template_max_count * sizeof(char *));
            if (templates == NULL) {
                exit(1);
            }
        }
    }
    free(pattern);
    fclose(f);
    templates[template_count] = NULL;
    return templates;
}

/*
char** get_templates_from_files(char **template_files) {
    int i = 0;
    int template_max_count = ALLOC_BASE;
    int template_count = 0;
    char *pattern_alloc;
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
                if (pattern[0] == '\n') {
                    continue;
                }
                pattern[strlen(pattern) - 1]  == '\n' ? pattern[strlen(pattern) - 1]  = '\0' : 0; // для того, чтобы в шаблон не попадал символ переноса строки
                pattern_alloc = calloc(strlen(pattern), sizeof(char));
                if (pattern_alloc == NULL) {
                    printf("error", stderr); // марат (я) не рекомендует
                    exit(1);
                }
                strcpy(pattern_alloc, pattern);
                templates[template_count] = pattern_alloc;
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
*/