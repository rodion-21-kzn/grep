//
// Created by Oznak Banshee on 11/6/22.
//

#include "../includes/grep.h"

char *pattern_allocate(char *pattern)
{
    char *str = calloc(strlen(pattern) + 1, sizeof(char));
    strcpy(str, pattern);
    return str;
}

int parser(int argc, char* argv[], Options* opt, char*** template_arr, char** template_files, char** files_arr, int* temp_count, int* files_count)
{
    int error = 1;
    int iteration = 1;
    int template_files_count = 0;
    int memory = argc - 1;
    char** templates_from_file;
    int e_situation = 0; // переменная нужна для случаев -е [template], чтобы следующий argv воспринимался полностью как шаблон и не проходил парсинг
    int f_situation = 0; // переменная нужна для случаев -f [template], чтобы следующий argv воспринимался полностью как шаблон и не проходил парсинг
    while (iteration < argc) {
        e_situation = 0;
        f_situation = 0;
        if (argv[iteration][0] == '-') {
            for (int i = 1; i < (int) strlen(argv[iteration]); i++) {
                int j = 0;
                int f = 0;
                if (argv[iteration][i] == 'e' && i != (int) strlen(argv[iteration]) - 1) {
                    // отработка ситуации -е[template]
                    (*template_arr)[*temp_count] = pattern_allocate(argv[iteration] + i + 1);
                    *temp_count = *temp_count + 1;
                    (*template_arr)[*temp_count] = NULL;
                    opt->e = 1;
                    break;
                }

                if (argv[iteration][i] == 'f' && i != (int) strlen(argv[iteration]) - 1) {
                    // отработка ситуации -f[file name]
                    templates_from_file = get_templates_from_files(argv[iteration] + i + 1, temp_count);

                    if (memory < *temp_count)  {
                        memory *= 3;
                        *template_arr = realloc(*template_arr, memory * sizeof(char*));
                    }
                    template_concatenation(templates_from_file, *template_arr, temp_count);
                    free(templates_from_file);
                    opt->f = 1;
                    break;
                }
                switch (argv[iteration][i]) {
                    case 'e':
                        opt->e = 1;
                        if (i == (int) strlen(argv[iteration]) - 1) { // отработка ситуации -е [template]
                            (*template_arr)[*temp_count] = pattern_allocate(argv[iteration+1]);
                            *temp_count = *temp_count + 1;
                            e_situation = 1;
                        }
                        break;
                    case 'i':
                        opt->i = 1;
                        break;
                    case 'v':
                        opt->v = 1;
                        break;
                    case 'c':
                        opt->c = 1;
                        break;
                    case 'l':
                        opt->l = 1;
                        break;
                    case 'n':
                        opt->n = 1;
                        break;
                    case 'h':
                        opt->h = 1;
                        break;
                    case 's':
                        opt->s = 1;
                        break;
                    case 'f':
                        opt->f = 1;
                        if (i == (int) strlen(argv[iteration]) - 1) { // отработка ситуации -f [template]
                            templates_from_file = get_templates_from_files(argv[iteration+1], temp_count);
                            if (memory < *temp_count)  {
                                memory *= 2;
                                *template_arr = realloc(*template_arr, memory * sizeof(char*));
                            }
                            template_concatenation(templates_from_file, *template_arr, temp_count);
                            free(templates_from_file);
                            f_situation = 1;
                        }
                        break;
                    case 'o':
                        opt->o = 1;
                        break;
                }
            }
        } else {
            files_arr[*files_count] = argv[iteration];
            *files_count = *files_count + 1;
        }
        if (e_situation || f_situation) {
            iteration += 2; // если был случай -е [template], пропускаем следующий argv потому что знаем что это шаблон
        } else {
            iteration++;
        }
    }
    return error;
}

/*
int parser(int argc, char* argv[], Options* opt, char** template_arr, char** template_files, char** files_arr, int* temp_count, int* files_count)
{
    int error = 1;
    int iteration = 1;
    int template_files_count = 0;
    int e_situation = 0; // переменная нужна для случаев -е [template], чтобы следующий argv воспринимался полностью как шаблон и не проходил парсинг
    int f_situation = 0; // переменная нужна для случаев -f [template], чтобы следующий argv воспринимался полностью как шаблон и не проходил парсинг
    while (iteration < argc) {
        e_situation = 0;
        f_situation = 0;
        if (argv[iteration][0] == '-') {
            for (int i = 1; i < (int) strlen(argv[iteration]); i++) {
                int j = 0;
                int f = 0;
                if (argv[iteration][i] == 'e' && i != (int) strlen(argv[iteration]) - 1) {
                    // отработка ситуации -е[template]
                    template_arr[*temp_count] = argv[iteration] + i + 1;
                    *temp_count = *temp_count + 1;
                    opt->e = 1;
                    break;
                }

                if (argv[iteration][i] == 'f' && i != (int) strlen(argv[iteration]) - 1) {
                    // отработка ситуации -f[file name]
                    template_files[template_files_count] = argv[iteration] + i + 1;
                    template_files_count++;
                    opt->f = 1;
                    break;
                }
                switch (argv[iteration][i]) {
                    case 'e':
                        opt->e = 1;
                        if (i == (int) strlen(argv[iteration]) - 1) { // отработка ситуации -е [template]
                            template_arr[*temp_count] = argv[iteration+1];
                            *temp_count = *temp_count + 1;
                            e_situation = 1;
                        }
                        break;
                    case 'i':
                        opt->i = 1;
                        break;
                    case 'v':
                        opt->v = 1;
                        break;
                    case 'c':
                        opt->c = 1;
                        break;
                    case 'l':
                        opt->l = 1;
                        break;
                    case 'n':
                        opt->n = 1;
                        break;
                    case 'h':
                        opt->h = 1;
                        break;
                    case 's':
                        opt->s = 1;
                        break;
                    case 'f':
                        opt->f = 1;
                        if (i == (int) strlen(argv[iteration]) - 1) { // отработка ситуации -f [template]
                            template_files[template_files_count] = argv[iteration+1];
                            template_files_count++;
                            f_situation = 1;
                        }
                        break;
                    case 'o':
                        opt->o = 1;
                        break;
                }
            }
        } else {
            files_arr[*files_count] = argv[iteration];
            *files_count = *files_count + 1;
        }
        if (e_situation || f_situation) {
            iteration += 2; // если был случай -е [template], пропускаем следующий argv потому что знаем что это шаблон
        } else {
            iteration++;
        }
    }
    template_files[template_files_count] = NULL;
    return error;
}
*/