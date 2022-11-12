//
// Created by Oznak Banshee on 11/10/22.
//

#include "../includes/grep.h"

void flag_o_work(regex_t regex, char* scan_line, Options opt, size_t * offset, int count_str, int* same_line, int files_count, char** files_arr, int file) {
    regmatch_t match;
    size_t plus = *offset;
    while(!regexec(&regex, scan_line + plus, 1, &match, 0)) {
        for (size_t i = plus + match.rm_so; i < plus + match.rm_eo; i++) {
            if (files_count > 1 && opt.h == 0 && *same_line == 0) printf("%s:", files_arr[file]);
            if (opt.n == 1 && *same_line == 0) {
                printf("%d:", count_str);
            }
            printf("%c", scan_line[i]);
            *same_line = 1;
        }
        printf("\n");
        plus = *offset + match.rm_eo;
        *offset = *offset + match.rm_eo;
    }
}

int output(int temp_count, int files_count, char** template_arr, char** files_arr, Options opt) {
    regex_t regex;
    FILE *f;
    int count_str = 1;
    int fail = REG_NOMATCH;
    char* scan_line = NULL;
    regmatch_t pmatch[1];
    size_t offset = 0;
    int match = 0;
    int same_line = 0;
    int miss = 0;
    int printed = 0;
    int count_c = 0;
    int count_l = 0;
    size_t len = 1024;
    int reg_flag = REG_EXTENDED;
    opt.i == 1 ? reg_flag = REG_ICASE : 0;
    for (int i = 0; i < files_count; i++) {
        f = fopen(files_arr[i], "r");
        if (f != NULL) {
            while (getline(&scan_line, &len, f) != EOF) {
                for (int k = 0; k < temp_count && match != temp_count && printed == 0; k++) {
                    // scan_line[strlen(scan_line) - 1] == '\n' ? scan_line[strlen(scan_line) - 1] = '\0' : 0;
                    regcomp(&regex, template_arr[k], reg_flag);
                    if (opt.o && !opt.l && !opt.c) {
                        flag_o_work(regex, scan_line, opt, &offset, count_str, &same_line, files_count, files_arr, i);
                    } else {
                        fail = regexec(&regex, scan_line, 0, pmatch, 0);
                        opt.v == 1 ? fail = !(fail) : 0;
                        fail == 0 ? match++ : miss++;
                        if (!fail && opt.l == 0 && opt.c == 0 && match == temp_count && miss == 0 && opt.v) {
                            if (files_count > 1 && opt.h == 0) printf("%s:", files_arr[i]);
                            opt.n == 1 ? printf("%d:", count_str) : 0;
                            printf("%s", scan_line);
                            printed = 1;
                        } else if (!fail && opt.l == 0 && opt.c == 0 && match > 0 && opt.v == 0) {
                            if (files_count > 1 && opt.h == 0) printf("%s:", files_arr[i]);
                            opt.n == 1 ? printf("%d:", count_str) : 0;
                            printf("%s", scan_line);
                            printed = 1;
                        } else if (match == temp_count && miss == 0 && opt.v && !fail) {
                            printed = 1;
                        } else if (!fail && match > 0 && opt.v == 0) {
                            printed = 1;
                        }
                    }
                }
                count_c = count_c + printed;
                count_c > 0 ? count_l = 1 : 0;
                printed = 0;
                miss = 0;
                same_line = 0;
                count_str++;
                fail = REG_NOMATCH;
                offset = 0;
                match = 0;
            }
            if (opt.c && opt.l == 0) {
                if (opt.h == 0 && files_count > 1) {
                    printf("%s:", files_arr[i]);
                    printf("%d\n", count_c);
                } else {
                    printf("%d\n", count_c);
                }
            } else if (opt.c && opt.l) {
                if (opt.h == 0 && files_count > 1) {
                    printf("%s:", files_arr[i]);
                    printf("%d\n", count_l);
                } else {
                    printf("%d\n", count_l);
                }
            }
            if (opt.l && count_l > 0) {
                printf("%s\n", files_arr[i]);
            }
            count_l = 0;
            count_c = 0;
            match = 0;
            count_str = 1;
        }
    }
    return 0;
}

/*
int output(int temp_count, int files_count, char** template_arr, char** files_arr, Options opt) {
    regex_t regex;
    FILE *f;
    int count_str = 1;
    int fail = REG_NOMATCH;
    char* scan_line = NULL;
    regmatch_t pmatch[1];
    size_t offset = 0;
    int stop = 0;
    int match = 0;
    int same_line = 0;
    int miss = 0;
    size_t len = 1024;
    int reg_flag = REG_EXTENDED;
    opt.i == 1 ? reg_flag = REG_ICASE : 0;
    for (int i = 0; i < files_count; i++) {
        f = fopen(files_arr[i], "r");
        if (f != NULL) {
            while (getline(&scan_line, &len, f) != EOF && stop == 0) {
                for (int k = 0; k < temp_count && fail == 1 && stop == 0; k++) {
                    // scan_line[strlen(scan_line) - 1] == '\n' ? scan_line[strlen(scan_line) - 1] = '\0' : 0;
                    regcomp(&regex, template_arr[k], reg_flag);
                    if (opt.o && !opt.l && !opt.c) {
                        flag_o_work(regex, scan_line, opt, &offset, count_str, &same_line);
                    } else {
                        fail = regexec(&regex, scan_line, 0, pmatch, 0);
                        opt.v == 1 ? fail = !(fail) : 0;
                        fail == 0 ? match++ : miss++;
                        if (!fail && opt.l == 0 && opt.c == 0) {
                            if (files_count > 1 && opt.h == 0) printf("%s:", files_arr[i]);
                            opt.n == 1 ? printf("%d:", count_str) : 0;
                            printf("%s", scan_line);
                        } else if (!fail && opt.l == 1) {
                            stop = 1;
                        }
                    }
                }
                same_line = 0;
                count_str++;
                fail = REG_NOMATCH;
                offset = 0;
            }
            if (opt.c) {
                if (opt.h == 0 && files_count > 1) {
                    printf("%s:", files_arr[i]);
                    printf("%d\n", match);
                } else {
                    printf("%d\n", match);
                }
            }
            if (opt.l && match > 0) {
                printf("%s\n", files_arr[i]);
            }
            match = 0;
            stop = 0;
            count_str = 1;
        }
    }
    return 0;
}
*/

/*
int output(int temp_count, int files_count, char** template_arr, char** files_arr, Options opt) {
    regex_t regex;
    FILE *f;
    int count_str = 1;
    int fail = REG_NOMATCH;
    char* scan_line = NULL;
    regmatch_t pmatch[1];
    size_t offset = 0;
    int stop = 0;
    int match = 0;
    int same_line = 0;
    size_t len = 1024;
    int reg_flag = REG_EXTENDED;
    opt.i == 1 ? reg_flag = REG_ICASE : 0;
    for (int i = 0; i < files_count; i++) {
        f = fopen(files_arr[i], "r");
        if (f != NULL) {
            while (getline(&scan_line, &len, f) != EOF && stop == 0) {
                for (int k = 0; k < temp_count && fail == 1 && stop == 0; k++) {
                    // scan_line[strlen(scan_line) - 1] == '\n' ? scan_line[strlen(scan_line) - 1] = '\0' : 0;
                    regcomp(&regex, template_arr[k], reg_flag);
                    if (opt.o && !opt.l && !opt.c) {
                        flag_o_work(regex, scan_line, opt, &offset, count_str, same_line);
                    } else {
                        fail = regexec(&regex, scan_line, 0, pmatch, 0);
                        opt.v == 1 ? fail = !(fail) : 0;
                        fail == 0 ? match++ : 0;
                        if (!fail && opt.l == 0 && opt.c == 0) {
                            if (files_count > 1 && opt.h == 0) printf("%s:", files_arr[i]);
                            opt.n == 1 ? printf("%d:", count_str) : 0;
                            printf("%s", scan_line);
                        } else if (!fail && opt.l == 1) {
                            stop = 1;
                        }
                    }

                }
                same_line = 0;
                count_str++;
                fail = REG_NOMATCH;
                offset = 0;
            }
            if (opt.c) {
                if (opt.h == 0 && files_count > 1) {
                    printf("%s:", files_arr[i]);
                    printf("%d\n", match);
                } else {
                    printf("%d\n", match);
                }
            }
            if (opt.l && match > 0) {
                printf("%s\n", files_arr[i]);
            }
            match = 0;
            stop = 0;
            count_str = 1;
        }
    }
    return 0;
}

*/

/* int output(int temp_count, int files_count, char** template_arr, char** files_arr, Options opt) {
    regex_t regex;
    FILE *f;
    int count_str = 1;
    int fail = REG_NOMATCH;
    char* scan_line = NULL;
    regmatch_t pmatch[1];
    int stop = 0;
    int match = 0;
    size_t len = 1024;
    int reg_flag = REG_EXTENDED;
    opt.i == 1 ? reg_flag = REG_ICASE : 0;
    for (int i = 0; i < files_count; i++) {
        f = fopen(files_arr[i], "r");
        if (f != NULL) {
            while (getline(&scan_line, &len, f) != EOF && stop == 0) {
                for (int k = 0; k < temp_count && fail == 1 && stop == 0; k++) {
                    // scan_line[strlen(scan_line) - 1] == '\n' ? scan_line[strlen(scan_line) - 1] = '\0' : 0;
                    regcomp(&regex, template_arr[k], reg_flag);
                    if (opt.o) flag_o_work(regex, scan_line, opt);
                    fail = regexec(&regex, scan_line, 0, pmatch, 0);
                    opt.v == 1 ? fail = !(fail) : 0;
                    fail == 0 ? match++ : 0;
                    if (!fail && opt.l == 0 && opt.c == 0) {
                        if (files_count > 1 && opt.h == 0) printf("%s:", files_arr[i]);
                        opt.n == 1 ? printf("%d:", count_str) : 0;
                        printf("%s", scan_line);
                    } else if (!fail && opt.l == 1) {
                        stop = 1;
                    }
                }
                count_str++;
                fail = REG_NOMATCH;
            }
            if (opt.c) {
                if (opt.h == 0 && files_count > 1) {
                    printf("%s:", files_arr[i]);
                    printf("%d\n", match);
                } else {
                    printf("%d\n", match);
                }
            }
            if (opt.l && match > 0) {
                printf("%s\n", files_arr[i]);
            }
            match = 0;
            stop = 0;
            count_str = 1;
        }
    }



    return 0;
}
*/