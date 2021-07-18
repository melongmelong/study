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

void init_stk(struct node **stk){
    *stk = NULL;
}

void deinit_stk(struct node **stk){
    struct node *tmp, *del;
    
    tmp = *stk;
    while(tmp){
        del = tmp;
        tmp = tmp->next;
        free(del);
    }
}

void push(struct node **stk, struct ListNode *val){
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
    struct node *ret;
    
    if(*stk == NULL){
        return NULL;
    }
    
    ret = *stk;
    
    *stk = (*stk)->next;
    if(*stk == NULL){
        *stk = NULL;
    }
    
    return ret;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k){
    int i;
    struct ListNode *org_list, *tmp_list,  *cur_list, *nxt_list, *ans;
    struct node *stk, *tmp_stk;
   
    init_stk(&stk);
    ans = NULL;
    nxt_list = tmp_list = head;
    
    while(nxt_list){
        org_list = nxt_list;
        tmp_list = nxt_list;
        for(i=0; tmp_list && i<k; i++){
            push(&stk, tmp_list);
            tmp_list = tmp_list->next;
        }
        nxt_list = tmp_list;
        
        if(i==k){
            while(tmp_stk = pop(&stk)){
                if(ans == NULL){
                    ans = tmp_stk->val;
                    cur_list = ans;
                    cur_list->next = NULL;
                }
                else{
                    cur_list->next = tmp_stk->val;
                    cur_list = tmp_stk->val;
                    cur_list->next = NULL;
                }
                free(tmp_stk);
            }
        }
        else{
            cur_list->next = org_list;
            cur_list = org_list;
            break;
        }
    }
    
    deinit_stk(&stk);
    
    return ans;
}
