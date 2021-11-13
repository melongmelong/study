struct node{
    int val;
    struct node *next;
};

void init_stk(struct node **stk){
    *stk = NULL;
}

void deinit_stk(struct node **stk){
    struct node *node, *del;
    
    node = *stk;
    while(node){
        del = node;
        node = node->next;
        free(del);
    }
}

void push(struct node **stk, int val){
    struct node *node;
    
    node = (struct node*)malloc(sizeof(struct node));
    node->next = NULL;
    node->val = val;
    
    if(*stk == NULL){
        *stk = node;
        return;
    }
    
    node->next = *stk;
    *stk = node;
}

struct node* pop(struct node **stk){
    struct node *node;
   
    if(*stk == NULL){
        return NULL;
    }
    
    node = *stk;
    *stk = node->next;
    
    return node;
}

struct node* peek(struct node **stk){
    return *stk;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* finalPrices(int* prices, int pricesSize, int* returnSize){
    int i;
    struct node *stk, *node;
    int *ans;
   
    ans = (int*)malloc(sizeof(int)*pricesSize);
    *returnSize = pricesSize;
    
    init_stk(&stk);
    
    for(i=0; i<pricesSize; i++){
        node = peek(&stk);
        if(node == NULL){
            push(&stk, i);
        }
        else{
            if(prices[i] <= prices[node->val]){
                while(node = peek(&stk)){
                    if(prices[node->val] >= prices[i]){
                        ans[node->val] = prices[node->val] - prices[i];
                        pop(&stk);
                    }
                    else{
                        break;
                    }
                }
            }
            push(&stk, i);
        }
    }
    
    while(node = pop(&stk)){
        ans[node->val] = prices[node->val];
    }
    
    deinit_stk(&stk);
    
    return ans;
}
