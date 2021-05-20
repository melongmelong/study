/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct node{
    struct TreeNode *val;
    struct node *next;
};

struct queue{
    struct node *head, *tail;
    int cnt;
};

void init_queue(struct queue *q){
    q->head = q->tail = NULL;
    q->cnt = 0;
}

void deinit_queue(struct queue *q){
    struct node *tmp = q->head, *del;
    while(tmp) {
        del = tmp;
        tmp = tmp->next;
        free(del);
    }
}

void enqueue(struct queue *q, struct TreeNode *val){
    struct node *node = (struct node*)malloc(sizeof(struct node));
    node->val = val;
    node->next = NULL;
    q->cnt++;
    if(q->head == NULL){
        q->head = q->tail = node;
        return;
    }
    q->tail->next = node;
    q->tail = node;
}

struct node* dequeue(struct queue *q){
    struct node *node = q->head;
    q->cnt--;
    if(q->head == NULL){
        q->cnt = 0;
        return NULL;
    }
    if(q->head->next == NULL){
        q->head = q->tail = NULL;
    }
    else{
        q->head = q->head->next;
    }
    return node;
}

int max_level;

void dfs(struct TreeNode *root, int level){
    if(root == NULL) {
        return;
    }
    if(max_level < level){
        max_level = level;
    }
    dfs(root->left, level+1);
    dfs(root->right, level+1);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    struct queue q1, q2, *q = &q1, *nq = &q2, *tmpq;
    struct node *node;
    int **ans, level=0, cnt=0;
   
    if(root == NULL){
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    
    max_level = 0;
    dfs(root, 1);
    ans = (int**)malloc(sizeof(int*)*max_level);
    *returnSize = max_level;
    *returnColumnSizes = (int*)malloc(sizeof(int)*max_level);
    init_queue(&q1);
    init_queue(&q2);
    enqueue(q, root);
    while(q->cnt || nq->cnt){
        ans[level] = (int*)malloc(sizeof(int)*q->cnt);
        (*returnColumnSizes)[level] = q->cnt;
        cnt = 0;
        while(node = dequeue(q)){
            ans[level][cnt] = node->val->val;
            cnt++;
            if(node->val->left){
                enqueue(nq, node->val->left);
            }
            if(node->val->right){
                enqueue(nq, node->val->right);
            }
            free(node);
        }
        level++;
        tmpq = q;
        q = nq;
        nq = tmpq;
        deinit_queue(nq);
        init_queue(nq);
    }
    deinit_queue(&q1);
    deinit_queue(&q2);
    return ans;
}
