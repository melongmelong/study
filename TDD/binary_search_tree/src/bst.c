#include <stdlib.h>
#include <string.h>
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

static struct bst_node* add_bst_node(struct bst_node **node, int val)
{
	if(*node == NULL){
		*node = create_bst_node(val);
		return *node;
	}

	if((*node)->val > val){
		return add_bst_node(&((*node)->left), val);
	}
	else{
		return add_bst_node(&((*node)->right), val);
	}
}
struct bst_node* add_bst(struct bst *bst, int val)
{
	return add_bst_node(&(bst->root), val);
}

static struct bst_node* search_bst_node(struct bst_node *node, int val)
{
	if(node == NULL){
		return NULL;
	}

	if(node->val == val){
		return node;
	}

	if(node->val < val){
		return search_bst_node(node->right, val);
	}
	else{
		return search_bst_node(node->left, val);
	}

	return NULL; //not reach.
}
struct bst_node* search_bst(struct bst *bst, int val)
{
	return search_bst_node(bst->root, val);
}

static struct bst_node* get_most_left_node(struct bst_node **parent, struct bst_node *node)
{
	if(node->left == NULL){
		return node;
	}

	*parent = node;

	return get_most_left_node(parent, node->left);
}
static struct bst_node* get_node_replaced(struct bst_node **parent, struct bst_node *node)
{
	if(node->left != NULL && node->right == NULL){
		return node->left;
	}
	else if(node->left == NULL && node->right != NULL){
		return node->right;
	}

	return get_most_left_node(parent, node->right);
}
static void delete_bst_node(struct bst_node *parent, struct bst_node **cur, int val)
{
	struct bst_node *replace, *parent_of_replace;

	if(*cur == NULL){
		return;
	}

	if((*cur)->val == val){
		if(parent == NULL){
			*cur = NULL;
		}
		else{
			if((*cur)->left == NULL && (*cur)->right == NULL){
				if(parent->left == *cur){
					parent->left = NULL;
				}
				else if(parent->right == *cur){
					parent->right = NULL;
				}

				free(*cur);
			}
			else if((*cur)->left && (*cur)->right){
				replace = get_node_replaced(&parent_of_replace, *cur);
				(*cur)->val = replace->val;
				delete_bst_node(parent_of_replace, &replace, replace->val);
			}
			else{
				printf("del:%d %p\n", (*cur)->val, *cur);
				printf("parent:%p\n", parent);
				replace = get_node_replaced(NULL, *cur);

				if(parent->left == *cur){
					printf("parent->left:%d %p\n", parent->left->val, parent->left);
					parent->left = replace;
					printf("parent->left:%d %p\n", parent->left->val, parent->left);
				}
				else if(parent->right == *cur){
					parent->right = replace;
				}
				printf("del2:%d %p\n", (*cur)->val, *cur);
		//		free(*cur);
			}
		}
		return;
	}

	if((*cur)->val < val){
		delete_bst_node(*cur, &((*cur)->right), val);
	}
	else{
		delete_bst_node(*cur, &((*cur)->left), val);
	}
}
void delete_bst(struct bst *bst, int val)
{
	printf("root:%p\n", bst->root);
	printf("root->left:%d %p\n", bst->root->left->val, bst->root->left);
	delete_bst_node(NULL, &(bst->root), val);
	printf("root->left:%d %p\n", bst->root->left->val, bst->root->left);
}
