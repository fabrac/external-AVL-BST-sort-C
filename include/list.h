#include "sort.h"

typedef struct linked_list_s {
    data_t *data;
    struct linked_list_s *next;
} linked_list_t;


int list(FILE *file, char buffer[RAM], int reverse);
void list_save(linked_list_t *list, FILE *f);