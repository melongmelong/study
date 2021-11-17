
struct pq{
    int arr[100000];
    int cnt;
};

inline void swap(int *a, int *b){
    int tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void init_pq(struct pq *pq){
    memset(pq, 0, sizeof(*pq));
}

void enqueue(struct pq *pq, int val){
    int idx_parent, idx_child;
    
    pq->arr[pq->cnt] = val;
    pq->cnt++;
    
    idx_child = pq->cnt-1;
    idx_parent = (idx_child-1)/2;
    while(idx_child!=0 && pq->arr[idx_child]<pq->arr[idx_parent]){
        swap(&pq->arr[idx_child], &pq->arr[idx_parent]);
        idx_child = idx_parent;
        idx_parent = (idx_child-1)/2;
    }
}

int dequeue(struct pq *pq){
    int ret;
    int idx_parent, idx_child;
    
    if(pq->cnt == 0){
        return -1000000001;
    }
    
    ret = pq->arr[0];
    pq->cnt--;
    
    swap(&pq->arr[0], &pq->arr[pq->cnt]);
    
    idx_parent = 0;
    idx_child = idx_parent*2 + 1;
    while(1){
        if(idx_child >= pq->cnt){
            break;
        }
        else if(idx_child+1 >= pq->cnt){
            if(pq->arr[idx_child] >= pq->arr[idx_parent]){
                break;
            }
            swap(&pq->arr[idx_child], &pq->arr[idx_parent]);
            idx_parent = idx_child;
            idx_child = idx_parent*2 + 1;
        }
        else{
            if(pq->arr[idx_child] < pq->arr[idx_child+1]){
                if(pq->arr[idx_child] >= pq->arr[idx_parent]){
                    break;
                }
                swap(&pq->arr[idx_child], &pq->arr[idx_parent]);
                idx_parent = idx_child;
                idx_child = idx_parent*2 + 1;
            }
            else{
                if(pq->arr[idx_child+1] >= pq->arr[idx_parent]){
                    break;
                }
                swap(&pq->arr[idx_child+1], &pq->arr[idx_parent]);
                idx_parent = idx_child+1;
                idx_child = idx_parent*2 + 1;
            }
        }
    }
    
    return ret;
}

int longestConsecutive(int* nums, int numsSize){
    struct pq pq;
    int i;
    int prev, cur;
    int curlen, ans;
    
    if(numsSize == 0){
        return 0;
    }
    
    init_pq(&pq);
    
    for(i=0; i<numsSize; i++){
        enqueue(&pq, nums[i]);
    }
   
    ans = curlen = 1;
    prev = dequeue(&pq);
    while(pq.cnt){
        cur = dequeue(&pq);
        
        if(cur-prev == 1){
            curlen++;
        }
        else if(cur-prev == 0){
            //nothing;
        }
        else{
            curlen = 1;
        }
        prev = cur;
        
        if(curlen > ans){
            ans = curlen;
        }
    }
    
    return ans; 
}
