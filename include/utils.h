#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#define MEMORY_ERR() fprintf(stderr, "Malloc error\n")
#define ERROR(format, args) fprintf(stderr, format, args)
#define ERROR_MSG(format) fprintf(stderr, format)

typedef struct data_s {
    char **value;
    double key;
    int nb;
} data_t;

double str_to_double(double *result, const char* str);
data_t *create_data(double key, char *value);
int compare(double a, double b, int reverse);

#endif
