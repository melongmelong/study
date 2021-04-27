/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct node{
    struct ListNode *val;
    struct node *next;
};

struct stk{
    struct node *top;
};

void init_stk(struct stk *stk){
    stk->top = NULL;
}

void deinit_stk(struct stk *stk){
    struct node *node=stk->top, *del;
    while(node){
        del = node;
        node = node->next;
        free(del);
    }
}

void push(struct stk *stk, struct ListNode *val){
    struct node *node = (struct node*)malloc(sizeof(struct node));
    node->val = val;
    node->next = NULL;
    if(stk->top == NULL){
        stk->top = node;
        return;
    }
    node->next = stk->top;
    stk->top = node;
}

struct node* pop(struct stk *stk){
    struct node *node = stk->top;
    if(node == NULL){
        stk->top = NULL;
    }
    else{
        stk->top = node->next;
    }
    return node;
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct stk stk;
    struct node *node;
    struct ListNode *tmp, *prev, *ans;
    init_stk(&stk);
    tmp = head;
    while(tmp){
        push(&stk, tmp);
        tmp = tmp->next;
    }
    while(n){
        node = pop(&stk);
        tmp = node->val;
        free(node);
        n--;
    }
    node = pop(&stk);
    if(node == NULL){
        ans = head->next;
    }
    else{
        prev = node->val;
        free(node);
        prev->next = tmp->next;
        ans = head;
    }
    deinit_stk(&stk);
    return ans;
}
