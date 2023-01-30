#include "sort.h"

typedef struct avl_node_s {
	struct avl_node_s *left;
	struct avl_node_s *right;
    data_t *data;
} avl_node_t;

typedef struct avl_tree_s {
	struct avl_node_s *root;
} avl_tree_t;

int avl(FILE *file, char buffer[RAM], int reverse);
int abr(FILE *file, char buffer[RAM], int reverse);