
struct node{
    struct node *next;
    int val;
};

struct stk{
    struct node *head;
    struct node *prev_min, *min;
};

void init_stk(struct stk *stk){
    stk->head = NULL;
    stk->prev_min = NULL;
    stk->min = NULL;
}

void deinit_stk(struct stk *stk){
    struct node *del, *tmp;
    
    tmp = stk->head;
    while(tmp){
        del = tmp;
        tmp = tmp->next;
        free(del);
    }
}

void push(struct stk *stk, int val){
    struct node *node;
    
    node = (struct node*)malloc(sizeof(struct node));
    node->next = NULL;
    node->val = val;
    
    if(stk->head == NULL){
        stk->head = node;
        
        stk->prev_min = NULL;
        stk->min = node;
        return;
    }
    
    if(stk->min->val > node->val){
        stk->prev_min = NULL;
        stk->min = node;
    }
    
    node->next = stk->head;
    stk->head = node;
    
    if(node->next == stk->min){
        stk->prev_min = node;
    }
}

struct node* pop(struct stk *stk){
    struct node *node, *tmp, *prev;
   
    if(stk->head == NULL){
        return NULL;
    }
    
    node = stk->head;
    stk->head = node->next;
    
    if(node == stk->min){
        prev = NULL;
        tmp = stk->head;
        stk->prev_min = NULL;
        stk->min = tmp;
        while(tmp){
            if(stk->min->val > tmp->val){
                stk->prev_min = prev;
                stk->min = tmp;
            }
            prev = tmp;
            tmp = tmp->next;
        }
    }
    
    if(node->next == stk->min){
        stk->prev_min = NULL;
    }
    
    return node;
}

typedef struct {
    struct stk stk; 
} MinStack;

/** initialize your data structure here. */

MinStack* minStackCreate() {
    MinStack *stk;
    
    stk = (MinStack*)malloc(sizeof(MinStack));
    init_stk(&stk->stk);
    return stk;
}

void minStackPush(MinStack* obj, int val) {
    push(&obj->stk, val);
}

void minStackPop(MinStack* obj) {
    struct node *node;
    node = pop(&obj->stk);
    free(node);
}

int minStackTop(MinStack* obj) {
    return obj->stk.head->val;
}

int minStackGetMin(MinStack* obj) {
    return obj->stk.min->val;
}

void minStackFree(MinStack* obj) {
    deinit_stk(&obj->stk);
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/
