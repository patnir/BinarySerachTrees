#include<stdio.h>
#include<stdlib.h>

typedef struct _tnode {

	int label;
	struct _tnode *left;
	struct _tnode *right;
}tnode;

void bst_destroy(tnode *list) 
{
	if (list == NULL) 
		return;
	bst_destroy(list->left);
	bst_destroy(list->right);
	free(list);
}

void postorder (tnode *list) 
{
	if (list == NULL)
		return;
	postorder(list->left);
	postorder(list->right);
	printf("%d ", list->label);
}

void inorder (tnode *list) 
{
	if (list == NULL)
		return;
	inorder(list->left);
	printf("%d ", list->label);
	inorder(list->right);
}

tnode *bst_insert_without_duplicates (tnode **bst, int key)
{
	tnode *new_node = (tnode *)malloc (sizeof(tnode));
	new_node->label = key;
	new_node->right = NULL;
	new_node->left = NULL;
	if (*bst == NULL) {
		*bst = new_node;
		return new_node;
	}
	tnode *curr = *bst;
	while (1) 
	{
		if (curr->label >= key) {
			if (curr->left == NULL) {	
				curr->left = new_node;	
				break;
			}
			curr = curr->left;;
		} else {
			if (curr->right == NULL) {
				curr->right = new_node;
				break;
			}
			curr = curr->right;
		}
	}
	return new_node;
}

tnode *bst_delete(tnode **bst, int key)
{
	tnode *prev = NULL;
	tnode *curr = *bst;
	while (curr != NULL) {
		if (curr->label == key) {
			break;
		}
		prev = curr;
		if (curr->label > key)
			curr = curr->left;
		else 
			curr = curr->right;
		if (curr == NULL)
			return NULL;
	}
	tnode *replacement;
	if (curr->left == NULL) {
		replacement = curr->right;
	}
	else if (curr->right == NULL) {
		replacement = curr->left;
	}
	else {
		tnode *p_replacement;
		p_replacement = curr;
		replacement = curr->left;
		while (replacement->right != NULL) {
			p_replacement = replacement;
			replacement = replacement->right;
		}
		replacement->right = curr->right;
		if (replacement != curr) {
			p_replacement->right = replacement->left;
			replacement->left = curr->left;
		}
	}
	if (prev == NULL) {
		*bst = replacement;
	}
	else if (prev->left == curr) {
		prev->left = replacement;
	}
	else {
		prev->right = replacement;
	}
	curr->left = curr->right = NULL;
	return curr;
}
int main (int argc, char ** argv) 
{
	int sorted_array[] = {10, 20, 140, 30, 80, 200, 70, 90, 50, 60, 100};
	int array_size = sizeof(sorted_array)/sizeof(int);
	tnode *bst = NULL;
	int i;
	for (i = 0; i < array_size; i++)
		bst_insert_without_duplicates(&bst, sorted_array[i]);
	postorder(bst);
	printf("\n");
	inorder(bst);
	printf("\n");
	tnode *deleted_node = bst_delete(&bst, 100);
	inorder(deleted_node);
	printf("\n");
	bst_destroy(deleted_node);
	inorder(bst);
	printf("\n");
	bst_destroy(bst); 
	return EXIT_SUCCESS;
}
