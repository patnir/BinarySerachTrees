#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct _tnode {
	int label;
	struct _tnode *right;
	struct _tnode *left;
} tnode;

typedef struct _lnode {
	tnode *tree;
	struct _lnode *next;
} lnode;

lnode *push_construct (tnode *node)
{
	lnode *ret_node = (lnode *) malloc (sizeof(lnode));
	ret_node->tree = node;
	ret_node->next = NULL;
	return ret_node;
}

lnode *push (lnode **list, tnode *node) 
{
	lnode *new_node = push_construct(node);
	
	new_node->next = *list;
	*list = new_node;
	return new_node;	
}

lnode *pop (lnode **list) 
{
	lnode *ret_node;
	ret_node = *list;
	*list = ret_node->next;
	ret_node->next = NULL;
	return ret_node;
}

int peek (lnode *list)
{
	if (list == NULL) 
		return INT_MIN;
	return list->tree->label;
}

tnode *bst_construct (int *array, int lb, int ub)
{
	if (ub < lb) {
		return NULL;
	}
	tnode *ret_tree = (tnode *) malloc (sizeof(tnode));
	int median = (ub + lb) / 2;
	ret_tree->label = array[median];
	ret_tree->left = bst_construct(array, lb, median - 1);
	ret_tree->right = bst_construct(array, median + 1, ub);
	
	return ret_tree;
}

void bst_destroy (tnode *bst)
{
	if (bst == NULL) {
		return;
	}
	bst_destroy(bst->left);
	bst_destroy(bst->right);

	free(bst);
}

void print_inorder (tnode *bst) {
	if (bst == NULL) 
	{
		return;
	}
	print_inorder (bst->left);
	printf("%d ", bst->label);
	print_inorder (bst->right);
}
void print_pre (tnode *bst) {
	if (bst == NULL) 
	{
		return;
	}
	printf("%d ", bst->label);
	print_pre (bst->left);
	print_pre (bst->right);
}
void print_post (tnode *bst) {
	if (bst == NULL) 
	{
		return;
	}
	print_post (bst->left);
	print_post (bst->right);
	printf("%d ", bst->label);
}

int postorder_collect (tnode *bst, int *array, int index)
{
	if (bst == NULL) 
		return index;
	index = postorder_collect(bst->left, array, index);
	index = postorder_collect(bst->right, array, index);
	array[index] = bst->label;
	return index + 1;
}


tnode * construct_from_postorder(int * array, int lb, int ub) 
{
	if (ub < lb)
		return NULL;
	tnode *new_tnode = (tnode*) malloc (sizeof(tnode));
	new_tnode->label = array[ub];
	int median = ub - 1;
	while (array[median] > new_tnode->label)
		median --;
	new_tnode->right =  construct_from_postorder(array, median + 1, ub - 1);
	new_tnode->left = construct_from_postorder(array, lb, median);
	return new_tnode;
}


int main (int argc, char ** argv) 
{	
	int sorted_array[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140};
	int array_size = sizeof(sorted_array)/ sizeof(int);
	tnode *bst = bst_construct(sorted_array, 0, array_size - 1);
	print_inorder(bst);
	printf("\n");
	print_pre(bst);
	printf("\n");
	print_post(bst);
	printf("\n");
	postorder_collect(bst, sorted_array, 0);
	int i;
	for (i = 0; i < array_size; i++) {
		printf("%d ", sorted_array[i]);
	}
	printf("\n");
	
	///////////////////////// creating the tree from post order ////////////////////////////
	lnode *stack = NULL;
	
	for (i = 0; i < array_size; i++) {
		tnode *new_tnode = (tnode *)malloc(sizeof(tnode));
		new_tnode->label = sorted_array[i];
		if (new_tnode->label > peek(stack)) {
			new_tnode->left = NULL;
			new_tnode->right = NULL;
		} else {
			lnode *right_lnode = pop(&stack);
			lnode *left_lnode = pop(&stack);
			new_tnode->right = right_lnode->tree;
			new_tnode->left = left_lnode->tree;
			free(right_lnode);
			free(left_lnode);
		}
		push(&stack, new_tnode);
	}
	
	print_inorder(stack->tree);
	printf("\n");
	print_pre(stack->tree);
	printf("\n");
	print_post(stack->tree);
	printf("\n");
	
	bst_destroy(stack->tree);
	free(stack);
	
	tnode *new_bst = construct_from_postorder(sorted_array, 0, array_size - 1);
	
	print_inorder(new_bst);
	printf("\n");
	print_pre(new_bst);
	printf("\n");
	print_post(new_bst);
	printf("\n");
	bst_destroy(new_bst);
	bst_destroy(bst);
	return EXIT_SUCCESS;
}
