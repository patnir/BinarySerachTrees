#include<stdio.h>
#include<stdlib.h>

#include<string.h>

typedef struct _tnode {
	int label;
	struct _tnode *left;
	struct _tnode *right;

} tnode;

void bst_destroy (tnode *list)
{
	if (list == NULL) 
		return;
	bst_destroy(list->left);
	bst_destroy(list->right);
	free(list);
}

void postorder (tnode *list) {
	if (list == NULL)
		return;
	postorder(list->left);
	postorder(list->right);
	printf("%d ", list->label);
}

void inorder (tnode *list) {
	if (list == NULL)
		return;
	inorder(list->left);
	printf("%d ", list->label);
	inorder(list->right);
}

tnode *bst_insert (tnode **list, int key)
{
	tnode *new_node = (tnode *)malloc(sizeof(tnode));
	new_node->label = key;
	new_node->left = NULL;
	new_node->right = NULL;
	tnode *root = *list;
	if (root == NULL) {
		*list = new_node;
		return new_node;
	}
	tnode *prev = NULL;
	tnode *curr = root;
	while (curr != NULL)
	{
	prev = curr;
		if (curr->label < key) {
			curr = curr->right;
		}
		else {
			curr = curr->left;
		}
	}
	if  (prev->label < key) {
		prev->right = new_node;
	}
	else {
		prev->left = new_node;
	}
	return new_node;
} 

int main (int argc, char **argv) 
{
	int array[] = {50, 20, 100, 10, 140, 110, 90, 80};
	tnode *bst = NULL;
	int i;
	for (i = 0; i < sizeof(array)/sizeof(int); i++) {
		bst_insert(&bst, array[i]);
	}	
	postorder(bst);
	printf("\n");
	inorder(bst);
	printf("\n");
	bst_destroy(bst);
	return EXIT_SUCCESS;
}
