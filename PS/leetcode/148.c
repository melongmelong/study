/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct heap{
    #define N 50000
    struct ListNode *arr[N];
    int cnt;
};

void init(struct heap *heap){
    memset(heap, 0, sizeof(*heap));
}

void enqueue(struct heap *heap, struct ListNode *val){
    int cur_idx, parent_idx;
    struct ListNode *tmp_node;
    
    heap->arr[heap->cnt] = val;
    
    cur_idx = heap->cnt;
    while(cur_idx > 0){
        parent_idx = (cur_idx-1)/2;
        
        if(heap->arr[cur_idx]->val <= heap->arr[parent_idx]->val){
            break;
        }
        
        tmp_node = heap->arr[cur_idx];
        heap->arr[cur_idx] = heap->arr[parent_idx];
        heap->arr[parent_idx] = tmp_node;
        
        cur_idx = parent_idx;
    }
    
    heap->cnt++;
}

struct ListNode* dequeue(struct heap *heap){
    int cur_idx, child_idx, tmp_child_idx;
    struct ListNode *tmp_node, *ret_node;
   
    if(heap->cnt <= 0){
        return NULL;
    }
    
    ret_node = heap->arr[0];
   
    heap->arr[0] =  heap->arr[heap->cnt-1];
    
    cur_idx = 0;
    while(1){
        child_idx = cur_idx*2+2;
        
        if(child_idx < heap->cnt-1){ //2-child
            if(heap->arr[child_idx-1]->val > heap->arr[child_idx]->val){
                tmp_child_idx = child_idx-1;
            }
            else{
                tmp_child_idx = child_idx;
            }
        }
        else if(child_idx-1 < heap->cnt-1){ //1-child
            tmp_child_idx = child_idx-1;
        }
        else{ //0-child
            break;
        }
        
        if(heap->arr[tmp_child_idx]->val <= heap->arr[cur_idx]->val){
            break;
        }
       
        tmp_node = heap->arr[cur_idx];
        heap->arr[cur_idx] = heap->arr[tmp_child_idx];
        heap->arr[tmp_child_idx] = tmp_node;
        
        cur_idx = tmp_child_idx;
    }
    
    heap->cnt--;
    
    return ret_node;
}

struct ListNode* sortList(struct ListNode* head){
    struct heap heap;
    struct ListNode *tmp, *ans = NULL;

    init(&heap);
    
    tmp = head;
    while(tmp){
        enqueue(&heap, tmp);
        tmp = tmp->next;
    }
    
    while(tmp = dequeue(&heap)){
        tmp->next = ans;
        ans = tmp;
    }
    
    return ans;
}
