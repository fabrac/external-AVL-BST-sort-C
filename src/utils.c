#include "utils.h"

double str_to_double(double *result, const char* str)
{
    char *endPtr;
    long value = strtod(str, &endPtr);

    if (strcmp(endPtr, ""))
        return (0);
    if (value > __DBL_MAX__ || value < __DBL_MIN__)
        return (0);
    *result = value;
    return (1);
}

int compare(double a, double b, int reverse)
{
    if (reverse)
        return (a > b);
    return (a < b);
}