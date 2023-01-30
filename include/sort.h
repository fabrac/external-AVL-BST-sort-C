#ifndef __METEO_H_
#define __METEO_H_

#include "utils.h"  

#define RAM 200000

typedef struct external_s {
    FILE *file;
    char filename[10];
    int index;
    char *value;
    double key;
    int empty;
    int nb;
} external_t;

typedef struct options_s {
    FILE *input;
    FILE *output;
    int (*f)(FILE  *file, char buffer[RAM], int reverse);
    int reverse;
} options_t;

typedef struct function_pointer_s {
    const char *name;
    int (*f)(FILE  *file, char buffer[RAM], int reverse);
} function_pointer_t;


void free_options(options_t *options);
int functions_contains(function_pointer_t **functions, const char *key);
void free_functions(function_pointer_t **functions);
function_pointer_t **get_functions(int nb, ...);

int merge_sort(options_t *options);
int sort_files(external_t **files, options_t *options);
external_t **create_files(int file_nb);
void free_files(external_t **files);

#endif