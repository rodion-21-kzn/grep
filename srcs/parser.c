//
// Created by Oznak Banshee on 11/6/22.
//

#include "../includes/grep.h"


// срабатывает флаг и мы передаем полученое имя файла, Так же передаем счетчик образцов
int opt_f_func(char* file_name, char **buffer, int* temp_count) {
    int error = 1;
    FILE* f = fopen(file_name, "r");
    if (f == NULL) {
        error = 0;
    } else {
        char* pattern = NULL;
        size_t len = 1024;
        while (getline(&pattern, &len, f) != EOF) {
            pattern[strlen(pattern) - 1]  == '\n' ? pattern[strlen(pattern) - 1]  = '\0' : 0; // для того, чтобы в шаблон не попадал символ переноса строки
            strcpy(buffer[*temp_count], pattern);
            *temp_count = *temp_count + 1;
        }
        free(pattern);
        fclose(f);
    }
    return error;
}


int parser(int argc, char* argv[], Options* opt, char** template_arr,  char** template_files, char** files_arr, int* temp_count, int* files_count)
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


/*
int parser(int argc, char* argv[], Options* opt, char** template_arr, char** files_arr, int* temp_count, int* files_count) {
    int error = 1;
    int iteration = 1;
    int e_situation = 0; // переменная нужна для случаев -е [template], чтобы следующий argv воспринимался полностью как шаблон и не проходил парсинг
    int f_situation = 0; // переменная нужна для случаев -f [template], чтобы следующий argv воспринимался полностью как шаблон и не проходил парсинг
    char buf_temp[100][100];
    char buf_files[100][100];
    while (iteration < argc) {
        e_situation = 0;
        f_situation = 0;
        if (argv[iteration][0] == '-') {
            for (int i = 1; i < (int) strlen(argv[iteration]); i++) {
                int j = 0;
                int f = 0;
                if (argv[iteration][i] == 'e' && i != (int) strlen(argv[iteration]) - 1) { // отработка ситуации -е[template],
                    for (; i + 1 < (int) strlen(argv[iteration]); i++, j++) {
                        buf_temp[*temp_count][j] = argv[iteration][i + 1]; // считываем символы после -е и записываем их в буфер (создаем щаблон)
                    }
                    buf_temp[*temp_count][j] = '\0';
                    template_arr[*temp_count] = buf_temp[*temp_count];
                    *temp_count = *temp_count + 1;
                    opt->e = 1;
                    break;
                }

                if (argv[iteration][i] == 'f' && i != (int) strlen(argv[iteration]) - 1) { // отработка ситуации -f[template],
                    int start = *temp_count;
                    if (opt_f_func(argv[iteration] + 2, buf_temp, temp_count)) {
                        for (int k = start; k < *temp_count; k++) {
                            template_arr[k] = buf_temp[k];
                        }
                    } else {
                        error = 0;
                    }
                    opt->f = 1;
                    break;
                }

                switch (argv[iteration][i]) {
                    case 'e':
                        opt->e = 1;
                        if (i == (int) strlen(argv[iteration]) - 1) { // отработка ситуации -е [template]
                            strcpy(buf_temp [*temp_count],argv[iteration+1]); // записываем шаблон
                            template_arr[*temp_count] = buf_temp[*temp_count];
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
                            int begin = *temp_count;
                            if (opt_f_func(argv[iteration + 1], buf_temp, temp_count)) {
                                for (int k = begin; k < *temp_count; k++) {
                                    template_arr[k] = buf_temp[k];
                                }
                            } else {
                                error = 0;
                            }
                            f_situation = 1;
                        }
                        break;
                    case 'o':
                        opt->o = 1;
                        break;
                }
            }
        } else {
            strcpy(buf_files[*files_count], argv[iteration]);
            files_arr[*files_count] = buf_files[*files_count];
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
 */