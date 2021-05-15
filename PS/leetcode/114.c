/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int cnt;
struct TreeNode *preorder[2000];

void trav(struct TreeNode *root){
    if (root == NULL){
        return;
    }
    
    preorder[cnt++] = root;
    trav(root->left);
    trav(root->right);
}

void flatten(struct TreeNode* root){
    int i;
    cnt = 0;
    trav(root);
    if(cnt == 0){
        return;
    }
    for(i=0; i<cnt-1; i++){
        preorder[i]->left = NULL;
        preorder[i]->right = preorder[i+1];
    }
    preorder[i]->left = NULL;
    preorder[i]->right = NULL; 
}
