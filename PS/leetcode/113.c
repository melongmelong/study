/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct node{
    struct node *next;
    int *arr;
    int cnt;
};

void init(struct node **head){
    *head = NULL;
}

void deinit(struct node **head){
   struct node *tmp, *del;
    
    tmp = *head;
    while(tmp){
        del = tmp;
        tmp = tmp->next;
        free(del->arr);
        free(del);
    }
}

void add(struct node **head, int *arr, int cnt){
    struct node *node;
    
    node = (struct nodee*)malloc(sizeof(struct node));
    node->next = NULL;
    node->cnt = cnt;
    node->arr = (int*)malloc(sizeof(int)*cnt);
    memcpy(node->arr, arr, sizeof(int)*cnt);
    
    if(*head == NULL){
        *head = node;
        return;
    }
    
    node->next = *head;
    *head = node;
}

struct node *anslist;
int anscnt;

void dfs(struct TreeNode *root, int targetSum, int *arr, int cnt, int sum){
    if(root == NULL){
        return;
    }
    
    arr[cnt] = root->val;
    
    if(root->left==NULL && root->right==NULL){
        if(sum+root->val == targetSum){
            add(&anslist, arr, cnt+1);
            anscnt++;
        }
        return;
    }
   
    dfs(root->left, targetSum, arr, cnt+1, sum+root->val);
    dfs(root->right, targetSum, arr, cnt+1, sum+root->val);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pathSum(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes){
    int **ans, arr[5000], i;
    struct node *node;
    
    if(root == NULL){
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
  
    init(&anslist);
    anscnt = 0;
    
    dfs(root, targetSum, arr, 0, 0);
    
    ans = (int**)malloc(sizeof(int*)*anscnt);
    *returnSize = anscnt;
    *returnColumnSizes = (int*)malloc(sizeof(int)*anscnt);
    
    i = 0;
    node = anslist;
    while(node){
        ans[i] = (int*)malloc(sizeof(int)*node->cnt);
        memcpy(ans[i], node->arr, sizeof(int)*node->cnt);
        (*returnColumnSizes)[i] = node->cnt;
        
        i++; 
        node = node->next;
    }
   
    deinit(&anslist);
   
    return ans;
}
