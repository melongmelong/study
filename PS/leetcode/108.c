/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void dfs(struct TreeNode **root, int *nums, int start, int end){
    int mid;
    
    if(start > end){
        return;
    }
    
    mid = (start+end)/2;
    
    *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    (*root)->val = nums[mid];
    (*root)->left = NULL;
    (*root)->right = NULL;
    
    dfs(&((*root)->left), nums, start, mid-1);
    dfs(&((*root)->right), nums, mid+1, end);
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    struct TreeNode *ans;
    
    dfs(&ans, nums, 0, numsSize-1);
    
    return ans;
}
