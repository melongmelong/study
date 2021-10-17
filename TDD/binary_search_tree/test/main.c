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
}

int main(int argc, char *argv)
{
	CU_pSuite suite;
	CU_pRunSummary summary;

	CU_initialize_registry();

	suite = CU_add_suite("suite", NULL, NULL);
	CU_add_test(suite, "test_bst_add", test_bst_add);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();

	return 0;
}
