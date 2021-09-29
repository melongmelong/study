/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct ListNode** splitListToParts(struct ListNode* head, int k, int* returnSize){
    int n, q, r;
    int parts_len[50];
    int i,j;
    struct ListNode *tmp, *cur;
    struct ListNode **ans;
    
    n = 0;
    tmp = head;
    while(tmp){
        n++;
        tmp = tmp->next;
    }
    q = n/k;
    r = n%k;
    for(i=0; i<k; i++){
        parts_len[i] = q;
    }
    for(i=0; i<r; i++){
        parts_len[i]++;
    }
    
    *returnSize = k;
    ans = (struct ListNode**)malloc(sizeof(struct ListNode*)*k);
    cur = head;
    for(i=0; i<k; i++){
        ans[i] = NULL;
        if(parts_len[i]>0){
            tmp = cur;
            for(j=0; j<parts_len[i]-1; j++){
                tmp = tmp->next;
            }
            ans[i] = cur;
            cur = tmp->next;
            tmp->next = NULL;
        }
    }
    return ans;
}
