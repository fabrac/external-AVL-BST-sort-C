#include "sort.h"

function_pointer_t **get_functions(int nb, ...)
{
    va_list(args);
    va_start(args,nb);  
    function_pointer_t **functions = malloc(sizeof(function_pointer_t *) * (nb / 2 + 1));

    if (functions == NULL)
        return (NULL);
    for (int i = 0; i < nb / 2; i++) {
        functions[i] = malloc(sizeof(function_pointer_t));
        if (functions[i] == NULL)
            return (NULL);
        functions[i]->name = va_arg(args, char *);
        functions[i]->f = va_arg(args, int (*)(FILE *f, char buffer[RAM], int reverse));
    }
    va_end(args);
    functions[nb / 2] = NULL;
    return (functions);
}

void free_functions(function_pointer_t **functions)
{
    for (int i = 0; functions[i] != NULL; i++)
        free(functions[i]);
    free(functions);
}

int functions_contains(function_pointer_t **functions, const char *key)
{
    for (int i = 0; functions[i] != NULL; i++)
        if (!strcmp(functions[i]->name, key))
            return (i);
    return (-1);
}

void free_options(options_t *options)
{
    if (options->input != NULL)
        fclose(options->input);
    if (options->output != NULL)
        fclose(options->output);
    free(options);
}
