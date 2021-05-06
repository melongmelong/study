/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct node{
    struct node *next;
    int val;
};

struct stk{
    struct node *top;
};

void init_stk(struct stk *stk){
    stk->top = NULL;
}

void deinit_stk(struct stk *stk){
    struct node *node = stk->top, *del;
    while(node){
        del = node;
        node = node->next;
        free(del);
    }
}

void push(struct stk *stk, int val){
    struct node *node = (struct node*)malloc(sizeof(struct node));
    node->next = NULL;
    node->val = val;
    if(stk->top == NULL){
        stk->top = node;
        return;
    }
    node->next = stk->top;
    stk->top = node;
}

struct node* pop(struct stk *stk){
    struct node *node = stk->top;
    stk->top = stk->top->next;
    return node;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct stk stk1, stk2;
    struct node *node1, *node2;
    struct ListNode *ans=NULL, *tmp;
    int c=0, sum; 
    init_stk(&stk1);
    init_stk(&stk2);
    tmp = l1;
    while(tmp){
        push(&stk1, tmp->val);
        tmp = tmp->next;
    }
    tmp = l2;
    while(tmp){
        push(&stk2, tmp->val);
        tmp = tmp->next;
    }
    while(stk1.top!=NULL && stk2.top!=NULL){
        node1 = pop(&stk1);
        node2 = pop(&stk2);
        sum = node1->val + node2->val + c;
        if(sum >= 10){
            c = 1;
            sum -= 10;
        }
        else{
            c = 0;
        }
        tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp->val = sum;
        tmp->next = NULL;
        if(ans == NULL){
            ans = tmp;
        }
        else{
            tmp->next = ans;
            ans = tmp;
        }
        free(node1);
        free(node2);
    }
    while(stk1.top!=NULL){
        node1 = pop(&stk1);
        sum = node1->val + c;
        if(sum >= 10){
            c = 1;
            sum -= 10;
        }
        else{
            c = 0;
        }
        tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp->val = sum;
        tmp->next = NULL;
        if(ans == NULL){
            ans = tmp;
        }
        else{
            tmp->next = ans;
            ans = tmp;
        }
        free(node1);
    }
    while(stk2.top!=NULL){
        node2 = pop(&stk2);
        sum = node2->val + c;
        if(sum >= 10){
            c = 1;
            sum -= 10;
        }
        else{
            c = 0;
        }
        tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp->val = sum;
        tmp->next = NULL;
        if(ans == NULL){
            ans = tmp;
        }
        else{
            tmp->next = ans;
            ans = tmp;
        }
        free(node2);
    }
    if(c){
        tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp->val = c;
        tmp->next = NULL;
        if(ans == NULL){
            ans = tmp;
        }
        else{
            tmp->next = ans;
            ans = tmp;
        }
    }
    return ans;
}
