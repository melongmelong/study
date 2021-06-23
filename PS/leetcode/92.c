/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct node{
    struct node *next;
    struct ListNode *val;
};

void init_stk(struct node **head){
    *head=NULL;
}

void deinit_stk(struct node **head){
    struct node *tmp, *del;
    tmp=*head;
    while(tmp){
        del=tmp;
        tmp=tmp->next;
        free(del);
    }
}

void push(struct node **head, struct ListNode *val){
    struct node *node=(struct node*)malloc(sizeof(struct node));
    node->next=NULL;
    node->val=val;
    if(*head==NULL){
        *head=node;
        return;
    }
    node->next=*head;
    *head=node;
}

struct node* pop(struct node **head){
    struct node *node=*head;
    if(node==NULL){
        *head=NULL;
    }
    else{
        *head=node->next;
    }
    return node;
}

struct ListNode* reverseBetween(struct ListNode* head, int left, int right){
    int idx=1;
    struct ListNode *tmp=head, *prev=NULL, *next=NULL, *ans=head;
    struct node *stk=NULL, *tmp2=NULL;
    init_stk(&stk);
    while(idx<=right){
        if(left<=idx && idx<=right){
            push(&stk, tmp);
        }
        else{
            prev=tmp;
        }
        idx++;
        tmp=tmp->next;
    }
    next=tmp;
    while(tmp2=pop(&stk)){
        if(prev==NULL){
            prev=tmp2->val;
            ans=prev;
        }
        prev->next=tmp2->val;
        prev=tmp2->val;
    }
    prev->next=next;
    deinit_stk(&stk);
    return ans;
}
