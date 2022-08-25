#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "../src/bst.h"

void test_is_left_less(void)
{
	struct bst_node *root;

	root = create_bst_node(5);
	root->left = create_bst_node(3);

	CU_ASSERT_EQUAL_FATAL(root->val > root->left->val, 1);
	CU_ASSERT_EQUAL_FATAL(root->val < root->left->val, 0);
}

void test_is_right_greater(void)
{
	struct bst_node *root;

	root = create_bst_node(5);
	root->right = create_bst_node(6);

	CU_ASSERT_EQUAL_FATAL(root->val <= root->right->val, 1);
	CU_ASSERT_EQUAL_FATAL(root->val > root->right->val, 0);
}

void test_is_right_equal(void)
{
	struct bst_node *root;

	root = create_bst_node(5);
	root->right = create_bst_node(5);

	CU_ASSERT_EQUAL_FATAL(root->val == root->right->val, 1);
}

void __test_bst_inorder(struct bst_node *root, int *arr, int *len)
{
	if(root == NULL){
		return;
	}

	__test_bst_inorder(root->left, arr, len);

	arr[*len] = root->val;
	*len = *len + 1;	

	__test_bst_inorder(root->right, arr, len);
}
void test_bst_inorder(struct bst *bst)
{
	int arr[16], len=0;
	int i;

	__test_bst_inorder(bst->root, arr, &len);

	for(i=1; i<len; i++){
		CU_ASSERT_EQUAL_FATAL(arr[i-1] <= arr[i], 1);
	}
}

void __test_bst_add(struct bst_node *root, struct bst_node *parent, struct bst_node *node)
{
	if(root == NULL){
		return;
	}

	if(root == node){
		CU_ASSERT_EQUAL_FATAL(node == root, 1);

		if(parent){
			if(parent->val > node->val){
				CU_ASSERT_EQUAL_FATAL(parent->left == node, 1);
			}
			else{
				CU_ASSERT_EQUAL_FATAL(parent->right == node, 1);
			}
		}
	}

	__test_bst_add(root->left, root, node);
	__test_bst_add(root->right, root, node);
}
void test_bst_add(void)
{
	struct bst bst;
	struct bst_node *node;

	init_bst(&bst);

	node = add_bst(&bst, 5);
	__test_bst_add(bst.root, NULL, node);

	node = add_bst(&bst, 4);
	__test_bst_add(bst.root, NULL, node);

	node = add_bst(&bst, 3);
	__test_bst_add(bst.root, NULL, node);

	node = add_bst(&bst, 6);
	__test_bst_add(bst.root, NULL, node);

	test_bst_inorder(&bst);
}

void test_bst_search(void)
{
	struct bst bst;
	struct bst_node *node;

	init_bst(&bst);
	
	node = search_bst(&bst, 5);
	CU_ASSERT_EQUAL_FATAL(node == NULL, 1);

	node = add_bst(&bst, 5);
	node = add_bst(&bst, 4);
	node = add_bst(&bst, 3);
	node = add_bst(&bst, 6);

	node = search_bst(&bst, 10);
	CU_ASSERT_EQUAL_FATAL(node == NULL, 1);

	node = search_bst(&bst, 5);
	CU_ASSERT_EQUAL_FATAL(node != NULL, 1);
	CU_ASSERT_EQUAL_FATAL(node->val == 5, 1);

	node = search_bst(&bst, 4);
	CU_ASSERT_EQUAL_FATAL(node != NULL, 1);
	CU_ASSERT_EQUAL_FATAL(node->val == 4, 1);
}

void __test_bst_delete_leaf(void)
{
	struct bst bst;
	struct bst_node *node;

	init_bst(&bst);
	node = add_bst(&bst, 5);
	node = add_bst(&bst, 4);
	node = add_bst(&bst, 3);
	node = add_bst(&bst, 6);

	delete_bst(&bst, 6);
	node = search_bst(&bst, 6);
	CU_ASSERT_EQUAL_FATAL(node == NULL, 1);
	test_bst_inorder(&bst);
}
void __test_bst_delete_leaf_root(void)
{
	struct bst bst;
	struct bst_node *node;

	init_bst(&bst);
	node = add_bst(&bst, 5);
	delete_bst(&bst, 5);
	node = search_bst(&bst, 5);
	CU_ASSERT_EQUAL_FATAL(node == NULL, 1);
	CU_ASSERT_EQUAL_FATAL(bst.root == NULL, 1);
	test_bst_inorder(&bst);
}
void __test_bst_delete_nonleaf_1child(void)
{
	struct bst bst;
	struct bst_node *node;

	init_bst(&bst);
	node = add_bst(&bst, 5);
	node = add_bst(&bst, 4);
	node = add_bst(&bst, 3);
	node = add_bst(&bst, 6);

	delete_bst(&bst, 4);
	node = search_bst(&bst, 4);
	CU_ASSERT_EQUAL_FATAL(node == NULL, 1);
	test_bst_inorder(&bst);
}
void __test_bst_delete_nonleaf_2child(void)
{
	struct bst bst;
	struct bst_node *node;

	init_bst(&bst);
	node = add_bst(&bst, 5);
	node = add_bst(&bst, 4);
	node = add_bst(&bst, 3);
	node = add_bst(&bst, 6);

	delete_bst(&bst, 5);
	node = search_bst(&bst, 5);
	CU_ASSERT_EQUAL_FATAL(node == NULL, 1);
	test_bst_inorder(&bst);
}
void test_bst_delete(void)
{
	printf("delete_leaf\n");
	__test_bst_delete_leaf();
	printf("delete_leaf_root\n");
	__test_bst_delete_leaf_root();
	printf("delete_nonleaf_1child\n");
	__test_bst_delete_nonleaf_1child();
	printf("delete_nonleaf_2child\n");
	__test_bst_delete_nonleaf_2child();
}

int main(int argc, char *argv)
{
	CU_pSuite suite;
	CU_pRunSummary summary;

	CU_initialize_registry();

	suite = CU_add_suite("suite", NULL, NULL);
	CU_add_test(suite, "test_bst_add", test_bst_add);
	CU_add_test(suite, "test_bst_search", test_bst_search);
	CU_add_test(suite, "test_bst_delete", test_bst_delete);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();

	return 0;
}
