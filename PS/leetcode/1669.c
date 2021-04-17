/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeInBetween(struct ListNode* list1, int a, int b, struct ListNode* list2){
    int i=0;
    struct ListNode *prev=NULL, *tmp=list1, *list2_tail;
    list2_tail = list2;
    while(list2_tail->next){
        list2_tail = list2_tail->next;
    }
    while(tmp){
        if(i==a){
            prev->next = list2;
        }
        if(i==b){
            list2_tail->next = tmp->next;
        }
        prev = tmp;
        tmp = tmp->next;
        i++;
    }
    return list1;
}
