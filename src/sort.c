#include "avl.h"
#include "utils.h"
#include "list.h"

int get_min(external_t **files, options_t *options)
{
	double min = 0;
	int index = -1;
	int first = 1;

	for (int i = 0; files[i] != NULL; i++)
		if (files[i]->empty == 0 && (first || compare(files[i]->key, min, options->reverse))) {
            first = 0;
            min = files[i]->key;
            index = i;
        }
	return (index);
}

void free_files(external_t **files)
{
    for (int i = 0; files[i] != NULL; i++) {
		free(files[i]->value);
		free(files[i]);
	}
	free(files);
}

external_t **create_files(int file_nb)
{
    external_t *ex;
	char *key_buffer;
	char *value;
	char *line;
    external_t **files = malloc(sizeof(external_t *) * (file_nb + 1));

	if (files == NULL)
		return (NULL);
	for (int i = 0; i < file_nb; i++) {
	    ex = malloc(sizeof(external_t));
		if (ex == NULL)
			return (NULL);
		ex->empty = 0;
		ex->index = i;
		sprintf(ex->filename, "%d", i);
		ex->file = fopen(ex->filename, "r");
		if (ex->file == NULL)
			return (NULL);
		line = NULL;
		getline(&line, &(size_t){0}, ex->file);
		key_buffer = strtok(line, ";");
    	value = strtok(NULL, "");
		str_to_double(&(ex->key), key_buffer);
		ex->value = malloc(sizeof(char) * (strlen(value) + 1));
		if (ex->value == NULL)
			return (NULL);
		strcpy(ex->value, value);
		ex->value[strlen(value)] = '\0';
		files[i] = ex;
		free(line);
	}
	files[file_nb] = NULL;
    return (files);
}

int sort_files(external_t **files, options_t *options)
{
	while (1) {
		int index = get_min(files, options);
		if (index == -1)
			break;
		fprintf(options->output, "%s", files[index]->value);
		char *ss = NULL;
		int uu = getline(&ss, &(size_t){0}, files[index]->file);
		if (uu == -1) {
            remove(files[index]->filename);
			fclose(files[index]->file);
			files[index]->empty = 1;
		}
		else {
			files[index]->key = 0;
			char *key_buffer = strtok(ss, ";");
    		char *value = strtok(NULL, "");
			str_to_double(&(files[index]->key), key_buffer);
			free(files[index]->value);
			files[index]->value = malloc(sizeof(char) * (strlen(value) + 1));
			if (files[index]->value == NULL)
				return (-1);
			strcpy(files[index]->value, value);
			files[index]->value[strlen(value)] = '\0';
		}
		free(ss);
	}
	fclose(options->output);
	return (0);
}

int write_file(char str[10], int *file_nb, char *buffer, options_t *options)
{
    FILE *file;

    sprintf(str, "%d", *file_nb);
    file = fopen(str, "w");
	if (file == NULL)
		return (-1);
    if (options->f(file, buffer, options->reverse) != 0)
		return (-1);
    fclose(file);
    (*file_nb)++;
	return (0);
}

int merge_sort(options_t *options)
{
    int file_nb = 0;
    int c = 1;
    int size;
    char str[10]; 
	char *buffer = NULL;
	char *line = NULL;

	for (int x = 0; c; x = 0) {
		buffer = malloc(sizeof(char));
		if (buffer == NULL)
			return (-1);
		buffer[0] = '\0';
		while (x < RAM) {
			size = getline(&line, &(size_t){0}, options->input);
			if (size == -1) {
                if (x == 0)
				    c = 0;
                free(line);	
				break;
			}
			buffer = realloc(buffer, x + size + 1);
			if (buffer == NULL)
				return (-1);
			strcat(buffer, line);
            free(line);
			x += size;
		}
		if (c == 1)
			if (write_file(str, &file_nb, buffer, options) == -1)
				return (-1);
		free(buffer);
	}
	fclose(options->input);
    return (file_nb);
}