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
    struct TreeNode *key;
    unsigned long long val;
};

void init_list(struct node **head){
    *head = NULL;
}

void deinit_list(struct node **head){
    struct node *tmp, *del;
    
    tmp = *head;
    while(tmp){
        del = tmp;
        tmp = tmp->next;
        free(del);
    }
}

void add_list(struct node **head, struct TreeNode *key, unsigned long long val){
    struct node *node;
    
    node = (struct node*)malloc(sizeof(struct node));
    node->next = NULL;
    node->key = key;
    node->val = val;
    
    if(*head == NULL){
        *head = node;
        return;
    }
    
    node->next = *head;
    *head = node;
}

struct node* search_list(struct node **head, struct TreeNode *key){
    struct node *tmp;
    
    tmp = *head;
    while(tmp){
        if(tmp->key == key){
            return tmp;
        }
        tmp = tmp->next;
    }
    
    return NULL;
}

#define BUCKET 1024

unsigned int hash(unsigned int key){
    return key%BUCKET;
}

unsigned long long sum_tree(struct node **head, struct TreeNode *root){
    unsigned long long sum;
    unsigned int h;
    
    if(root == NULL){
        return 0;
    }
    
    sum = root->val + sum_tree(head, root->left) + sum_tree(head, root->right);
    
    h = hash((unsigned int)root);
    add_list(&head[h], root, sum);
    
    return sum;
}

unsigned long long max;

void dfs(struct node **head, struct TreeNode *ROOT, struct TreeNode *root){
    unsigned long long sum1, sum2;
    unsigned int h;
    struct node *node;
    
    if(root == NULL){
        return;
    }
    
    if(root != ROOT){
        h = hash((unsigned int)root);
        node = search_list(&head[h], root);
        sum1 = node->val;

        h = hash((unsigned int)ROOT);
        node = search_list(&head[h], ROOT);
        sum2 = node->val;
        sum2 -= sum1;
        
        if(sum1*sum2 > max){
            max = sum1*sum2;
        }
    }
    
    dfs(head, ROOT, root->left);
    dfs(head, ROOT, root->right);
}

int maxProduct(struct TreeNode* root){
    struct node *head[BUCKET];
    int i;
    
    for(i=0; i<BUCKET; i++){
        init_list(&head[i]);
    }
    
    sum_tree(head, root);
    
    max = 0;
    dfs(head, root, root);
    
    for(i=0; i<BUCKET; i++){
        deinit_list(&head[i]);
    }
    
    return max%1000000007;
}
