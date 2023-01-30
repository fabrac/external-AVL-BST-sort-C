#include "sort.h"
#include "list.h"
#include "avl.h"

int main(int argc, const char **argv)
{
    int file_nb;
    external_t **files;
    int f;
    options_t *options;
    function_pointer_t **functions = get_functions(6, "--abr", &abr, "--avl", &avl, "--tab", &list);

    if (functions == NULL)
        return (4);
    options = malloc(sizeof(options_t));
    if (options == NULL)
        return (4);
    options->input = NULL;
    options->output = NULL;
    options->reverse = 0;
    options->f = NULL;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
            printf("Usage: ./external_sort -f <input_file> -o <output_file> [--tab/--abr/--avl]\n");
            free_options(options);
            return (0);
        }
        if (!strcmp(argv[i], "-r"))
            options->reverse = 1;
        else if (!strcmp("-f", argv[i]) && i < argc - 1) {
            options->input = fopen(argv[i + 1], "r");
            if (options->input == NULL) {
                free_options(options);
                return (2);
            }
            i++;
        }
        else if (!strcmp("-o", argv[i]) && i < argc - 1) {
            options->output = fopen(argv[i + 1], "w");
            if (options->output == NULL) {
                free_options(options);
                return (3);
            }
            i++;
        }
        else {
            f = functions_contains(functions, argv[i]);
            if (f != -1 &&  options->f != NULL) {
                free_functions(functions);
                free_options(options);
                return (1);
            }
            if (f != -1)
                options->f = functions[f]->f;
            else {
                free_functions(functions);
                free_options(options);
                return (1);
            }
        }
    }
    if (options->f == NULL)
        options->f = &avl;
    if (options->input == NULL || options->output == NULL) {
        printf("Usage: ./external_sort -f <input_file> -o <output_file> [--tab/--abr/--avl]\n");
        free_functions(functions);
        free_options(options);
        return (1);
    }
    file_nb = merge_sort(options);
    if (file_nb == -1) {
        return (4);
    }
	files = create_files(file_nb);
    if (files == NULL)
        return (4);
    if (sort_files(files, options) == -1)
        return (4);
    free_functions(functions);
	free_files(files);
    free(options);
	return (0);
}
