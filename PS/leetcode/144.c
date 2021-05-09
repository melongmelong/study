/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int arr[100];
int idx = 0;

void trav(struct TreeNode *root){
    if(root == NULL){
        return ;
    }
    arr[idx++] = root->val;
    trav(root->left);
    trav(root->right);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int *ans = NULL;
    idx = 0;
    trav(root);
    *returnSize = idx;
    if(idx){
        ans = (int*)malloc(sizeof(int)*idx);
        memcpy(ans, arr, sizeof(int)*idx);
    }
    return ans;
}
