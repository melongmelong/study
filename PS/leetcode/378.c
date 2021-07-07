
struct heap{
    int arr[90000];
    int cnt;
};

void init_heap(struct heap *heap){
    heap->cnt = 0;
    return;    
}

void deinit_heap(struct heap *heap){
    heap->cnt = 0;
    return;
}

void enqueue(struct heap *heap, int val){
    int p_idx, c_idx, tmp;
    
    heap->arr[heap->cnt] = val;
    heap->cnt++;
    
    c_idx = heap->cnt-1;
    while(c_idx){
        p_idx = (c_idx-1)/2;
        
        if(heap->arr[c_idx] < heap->arr[p_idx]){
            tmp = heap->arr[c_idx];
            heap->arr[c_idx] = heap->arr[p_idx];
            heap->arr[p_idx] = tmp;
        }
        else{
            break;
        }
        
        c_idx = p_idx;
    }
}

int dequeue(struct heap *heap){
    int p_idx, c_idx, tmp, ret;
    
    if(heap->cnt == 0){
        return 0;
    }
    
    ret = heap->arr[0];
    heap->cnt--;
    heap->arr[0] = heap->arr[heap->cnt];
    
    p_idx = 0;
    while(1){
        c_idx = (p_idx*2)+1;
       
        if((c_idx>=heap->cnt) || (p_idx>=heap->cnt)){
            break;
        }
        
        if(c_idx+1 < heap->cnt){
            if(heap->arr[c_idx] > heap->arr[c_idx+1]){
                c_idx = c_idx+1;
            }
        }
        
        if(heap->arr[c_idx] < heap->arr[p_idx]){
            tmp = heap->arr[c_idx];
            heap->arr[c_idx] = heap->arr[p_idx];
            heap->arr[p_idx] = tmp;
        }
        else{
            break;
        }
        
        p_idx = c_idx;
    }
    
    return ret;
}

int kthSmallest(int** matrix, int matrixSize, int* matrixColSize, int k){
    struct heap heap;
    int i,j,ans;
    
    init_heap(&heap);
    
    for(i=0; i<matrixSize; i++){
        for(j=0; j<matrixSize; j++){
            enqueue(&heap, matrix[i][j]);
        }
    }
    
    for(i=0; i<k; i++){
        ans = dequeue(&heap);
    }
   
    deinit_heap(&heap);
    
    return ans;
}
