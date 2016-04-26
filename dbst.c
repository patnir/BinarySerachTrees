#include<stdio.h>
#include<stdlib.h>

typedef struct _tnode {
	int label;
	struct _tnode *right;
	struct _tnode *left;
}tnode;

typedef struct _lnode {
	tnode *node;
	struct _lnode *next;
}lnode;

void in_order (tnode *head);
void post_order (tnode *head);
lnode *push (lnode **list, tnode *node);

void bst_destroy (tnode *list) 
{
	if (list == NULL) {
		return;
	}
	bst_destroy(list->left);
	bst_destroy(list->right);
	free(list);
	return;
}

tnode *bst_construct (int *array, int lb, int ub)
{
	if (ub < lb) {
		return NULL;
	}	
	tnode *new_node = (tnode *)malloc(sizeof(tnode));
	int median = (ub+lb) / 2;
	new_node->label = array[median];
	new_node->left = bst_construct(array, lb, median - 1);
	new_node->right = bst_construct(array, median + 1, ub);
	return new_node;
}

int main (int argc, char **argv)
{
	int sorted_array[] = {0, 10, 15, 20, 25, 30, 40, 50, 60, 70, 75, 80, 85, 90, 100};
	tnode *head = NULL;
	int size = sizeof(sorted_array) / sizeof (int);
	head = bst_construct(sorted_array, 0, size - 1);
	post_order(head);
	printf("\n");
	in_order(head);
	printf("\n");
	bst_destroy(head);
	return EXIT_SUCCESS;
}

void in_order (tnode *head)
{
	if (head == NULL)
		return;
	in_order(head->left);
	printf("%d ", head->label);
	in_order(head->right);
}

void post_order (tnode *head)
{
	if (head == NULL)
		return;
	post_order(head->left);
	post_order(head->right);
	printf("%d ", head->label);
}

lnode *push (lnode **list, tnode *node)
{
	lnode *new_node = (lnode *)malloc(sizeof(lnode));
	new_node->node = node;
	new_node->next = *list;
	*list = new_node;
	return new_node;
}
