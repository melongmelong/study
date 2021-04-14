/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* partition(struct ListNode* head, int x){
    struct ListNode *left_head=NULL, *left_tail=NULL, *prev=NULL, *cur=head;
    if(head == NULL){
        return NULL;
    }
    while(cur){
        if(cur->val < x){
            if(left_head == NULL){
                left_head = left_tail = cur;
            }
            else{
                left_tail->next = cur;
                left_tail = cur;
            }
            if(cur == head){
                head = cur->next;
            }
            else{
                prev->next = cur->next;
            }
            cur = cur->next;
            left_tail->next = NULL;
            continue;
        }
        prev = cur;
        cur = cur->next;
    }
    if(left_tail){
        left_tail->next = head;
        return left_head;
    }
    return head;
}
