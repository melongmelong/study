/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* alloc_treenode(int val){
    struct TreeNode *ret = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    ret->val = val;
    ret->left = NULL;
    ret->right = NULL;
    return ret;
}

void bst(struct TreeNode **root, int *arr, int start, int end){
    int mid = (start+end)/2;
    if(start > end){
        return;
    }
    else if(start == end){
        *root = alloc_treenode(arr[mid]);
        return;
    }
    *root = alloc_treenode(arr[mid]);
    bst(&((*root)->left), arr, start, mid-1);
    bst(&((*root)->right), arr, mid+1, end);
}

struct TreeNode* sortedListToBST(struct ListNode* head){
    int arr[20000], i=0;
    struct ListNode *node = head;
    struct TreeNode *root = NULL;
    while(node){
        arr[i++] = node->val;
        node = node->next;
    }
    bst(&root, arr, 0, i-1);
    return root;
}
