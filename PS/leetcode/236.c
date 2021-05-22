/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int flag = 0;

void dfs(struct TreeNode *root, struct TreeNode *val, int curr, struct TreeNode **preorder, int *level){
    if(root == NULL){
        return;
    }
    if(flag){
        return;
    }
    preorder[curr] = root;
    if(root == val){
        flag = 1;
        *level = curr;
        return;
    }
    dfs(root->left, val, curr+1, preorder, level);
    dfs(root->right, val, curr+1, preorder, level);
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    struct TreeNode *preorder_p[100000], *preorder_q[100000];
    int level_p=0, level_q=0;
    int i;
    flag = 0;
    dfs(root, p, 0, preorder_p, &level_p);
    flag = 0;
    dfs(root, q, 0, preorder_q, &level_q);
    for(i=level_p>level_q?level_q:level_p; i>=0; i--){
        if(preorder_p[i] == preorder_q[i]){
            return preorder_p[i];
        }
    }
    return NULL;
}
