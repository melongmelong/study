/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int arr[10000];
int arrcnt;

void trav(struct Node *root){
    int i;
    if(root == NULL){
        return;
    }
    arr[arrcnt++] = root->val;
    for(i=0; i<root->numChildren; i++){
        trav(root->children[i]);
    }
}

int* preorder(struct Node* root, int* returnSize) {
    int *ans;
    if(root == NULL){
        *returnSize = 0;
        return NULL;
    }
    arrcnt = 0;
    trav(root);
    *returnSize = arrcnt;
    ans = (int*)malloc(sizeof(int)*arrcnt);
    memcpy(ans, arr, sizeof(int)*arrcnt);
    return ans;
}
