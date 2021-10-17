#ifndef _BST_H_
#define _BST_H_

struct bst_node{
	int val;
	struct bst_node *left;
	struct bst_node *right;
};

struct bst{
	struct bst_node *root;
};

struct bst_node* create_bst_node(int val);
void init_bst(struct bst *bst);
struct bst_node* add_bst(struct bst *bst, int val);

#endif
