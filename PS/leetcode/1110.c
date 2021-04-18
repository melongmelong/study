/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void trav(struct TreeNode *parent, struct TreeNode *cur, int *to_delete, int to_deleteSize, struct TreeNode **tbl){
    int i;
    if(cur == NULL){
        return;
    }
    trav(cur, cur->left, to_delete, to_deleteSize, tbl);
    trav(cur, cur->right, to_delete, to_deleteSize, tbl);
    for(i=0; i<to_deleteSize; i++){
        if(cur->val == to_delete[i]){
            tbl[cur->val] = NULL;
            if(cur->left){
                tbl[cur->left->val] = cur->left;
            }
            if(cur->right){
                tbl[cur->right->val] = cur->right;
            }
            if(parent != NULL){
                if(parent->left == cur){
                    parent->left = NULL;
                }
                else{
                    parent->right = NULL;
                }
            }
            break;
        }
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** delNodes(struct TreeNode* root, int* to_delete, int to_deleteSize, int* returnSize){
    struct TreeNode *tbl[1001]={0}, **ans=NULL;
    int i,cnt=0;
    tbl[root->val] = root;
    trav(NULL, root, to_delete, to_deleteSize, tbl);
    *returnSize = 0;
    for(i=1; i<=1000; i++){
        if(tbl[i]){
            *returnSize = *returnSize + 1;
        }
    }
    ans = (struct TreeNode**)malloc(sizeof(struct TreeNode*)*(*returnSize));
    for(i=1; i<=1000; i++){
        if(tbl[i]){
            ans[cnt++] = tbl[i];
        }
    }
    return ans;
}
