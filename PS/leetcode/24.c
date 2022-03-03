/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* getNext(struct ListNode *node){
    int i;
    
    for(i=0; node && i<2; i++, node = node->next);
    
    return node;
}

struct ListNode* swapPairs(struct ListNode* head){
    struct ListNode *left_node, *right_node, *left_next_node, *right_next_node, *tmp_node, *prev_node = NULL;
    
    if(head == NULL){
        return 0;
    }
    
    if(head->next == NULL){
        return head;
    }
    
    left_node = head;
    right_node = left_node->next;
    head = right_node;
    
    while(left_node && right_node){
        left_next_node = getNext(left_node);
        right_next_node = getNext(right_node);

        if(prev_node){
            prev_node->next = right_node;
        }
        
        tmp_node = right_node->next;
        right_node->next = left_node;
        left_node->next = tmp_node;
        
        prev_node = left_node;
        
        left_node = left_next_node;
        right_node = right_next_node;
    }
    
    return head;
}
