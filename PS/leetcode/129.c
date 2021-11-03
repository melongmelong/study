/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int tbl_10e[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000};
int ans;

int convert_integer(int *arr, int num){
    int i;
    int ret;

    for(i=0; arr[i]==0; i++);
    
    ret = 0;
    for(; i<=num; i++){
        ret += arr[i]*tbl_10e[num-i];
    }
    
    return ret;
}

void dfs(struct TreeNode *root, int *arr, int depth){
    if(root == NULL){
        return;
    }
    
    arr[depth] = root->val;
    
    if(root->left==NULL && root->right==NULL){
        ans += convert_integer(arr, depth);
        return;
    }
    
    dfs(root->left, arr, depth+1);
    dfs(root->right, arr, depth+1);
}

int sumNumbers(struct TreeNode* root){
    int arr[1000];
    
    ans = 0;
    dfs(root, arr, 0);
    
    return ans;
}
