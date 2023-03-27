#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

static void inorder(struct bst_node *root)
{
	if(root == NULL){
		return;
	}

	inorder(root->left);
	printf("%d\n", root->val);
	inorder(root->right);
}

int main(int argc, char **argv)
{
	struct bst bst;
	int arr[10] = {123, 16, 485, 1238491, 123132, 547457, 890, 0, 987, 7};
	int i;

	init_bst(&bst);

	printf("add\n");
	for(i=0; i<10; i++){
		add_bst(&bst, arr[i]);
	}
	inorder(bst.root);

	printf("search\n");
	for(i=0; i<10; i++){
		printf("search %d, result:%d\n", arr[i], search_bst(&bst, arr[i])->val);
	}

	printf("delete\n");
	for(i=0; i<10; i++){
		delete_bst(&bst, arr[i]);
	}
	inorder(bst.root);

	printf("root : %p\n", bst.root);

	return 0;
}
