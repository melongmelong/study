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

static struct bst_node** find_successor(struct bst_node **cur)
{
	if((*cur)->left==NULL){
		return cur;
	}

	return find_successor(&(*cur)->left);
}
static void delete_bst_node(struct bst_node **cur, int val)
{
	struct bst_node *del, **successor;

	if(*cur == NULL){
		return;
	}

	if((*cur)->val == val){
		if((*cur)->left==NULL && (*cur)->right==NULL){
			free(*cur);
			*cur = NULL;
		}
		else if(((*cur)->left==NULL && (*cur)->right) || ((*cur)->left && (*cur)->right==NULL)){
			if((*cur)->right){
				del = *cur;
				*cur = (*cur)->right;
				free(del);
			}
			else if((*cur)->left){
				del = *cur;
				*cur = (*cur)->left;
				free(del);
			}
		}
		else{
			successor = find_successor(&(*cur)->right);

			(*cur)->val = (*successor)->val;

			delete_bst_node(successor, (*successor)->val);
		}
		return;
	}

	if((*cur)->val < val){
		delete_bst_node(&(*cur)->right, val);
	}
	else{
		delete_bst_node(&(*cur)->left, val);
	}
}
void delete_bst(struct bst *bst, int val)
{
	delete_bst_node(&bst->root, val);
}
