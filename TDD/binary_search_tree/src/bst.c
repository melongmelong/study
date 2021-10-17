#include <stdlib.h>
#include "bst.h"

struct bst_node* create_bst_node(int val)
{
	struct bst_node *node;

	node = (struct bst_node*)malloc(sizeof(struct bst_node));
	node->val = val;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void init_bst(struct bst *bst)
{
	if(bst == NULL){
		return;
	}

	memset(bst, 0, sizeof(*bst));
}

struct bst_node* add_bst_node(struct bst_node **node, int val)
{
	if(*node == NULL){
		*node = create_bst_node(val);
		return *node;
	}

	if((*node)->val > val){
		return add_bst_node(&(*node)->left, val);
	}
	else{
		return add_bst_node(&(*node)->right, val);
	}
}
struct bst_node* add_bst(struct bst *bst, int val)
{
	return add_bst_node(&bst->root, val);
}
