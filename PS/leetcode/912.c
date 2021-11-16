
struct pq{
    int arr[50000];
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
        return -10000000;
    }
   
    ret = pq->arr[0];
    pq->cnt--;
    
    swap(&pq->arr[pq->cnt], &pq->arr[0]);
    
    idx_parent = 0;
    while(1){
        idx_child = 2*idx_parent + 1;
        if(idx_child >= pq->cnt){ //no child
            break;
        }
        else if(idx_child+1 >= pq->cnt){ //one child
            if(pq->arr[idx_parent] <= pq->arr[idx_child]){
                break;
            }
            swap(&pq->arr[idx_parent], &pq->arr[idx_child]);
            idx_parent = idx_child;
        }
        else{ //two child
            if(pq->arr[idx_child] < pq->arr[idx_child+1]){
                if(pq->arr[idx_parent] <= pq->arr[idx_child]){
                    break;
                }
                swap(&pq->arr[idx_parent], &pq->arr[idx_child]);
                idx_parent = idx_child;
            }
            else{
                if(pq->arr[idx_parent] <= pq->arr[idx_child+1]){
                    break;
                }
                swap(&pq->arr[idx_parent], &pq->arr[idx_child+1]);
                idx_parent = idx_child+1;
            }
        }
    }
    
    return ret;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize){
    struct pq pq;
    int i;
    int *ans;
    
    init_pq(&pq);
    for(i=0; i<numsSize; i++){
        enqueue(&pq, nums[i]);
    }
    
    ans = (int*)malloc(sizeof(int) * numsSize);
    *returnSize = numsSize;
    for(i=0; i<numsSize; i++){
        ans[i] = dequeue(&pq);
    }

    return ans;
}
