/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int ans;

void trav(struct TreeNode *root, int max){
    if(root == NULL){
        return;
    }
    if(max <= root->val){
        max = root->val;
        ans++;
    }
    trav(root->left, max);
    trav(root->right, max);
}

int goodNodes(struct TreeNode* root){
    ans = 0;
    trav(root, -100000);
    return ans;
}
