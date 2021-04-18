/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int arr[100000], i, flag, ans;

void trav(struct TreeNode *root, int depth){
    if(root == NULL){
        return;
    }
    if(depth > 0){
        flag = 1;
        for(i=depth-1; i>=0; i--){
            if(arr[i] > root->val){
                flag = 0;
            }
        }
        if(flag){
            ans++;
        }
    }
    else{
        ans++;
    }
    arr[depth] = root->val;
    trav(root->left, depth+1);
    trav(root->right, depth+1);
}

int goodNodes(struct TreeNode* root){
    ans = 0;
    trav(root, 0);
    return ans;
}
