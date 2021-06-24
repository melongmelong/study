struct node{
    int sum, p1, p2;
};

struct heap{
    struct node *arr[10000];
    int num;
};

void init_heap(struct heap *heap){
    memset(heap->arr, 0, sizeof(heap->arr));
    heap->num = -1;
}

void deinit_heap(struct heap *heap){
    int i;
    
    for(i=0; i<=heap->num; i++){
        free(heap->arr[i]);
    }
}

void enqueue(struct heap *heap, struct node *node){
    int p_idx, c_idx;
    struct node *tmp;

    c_idx = heap->num+1;
    heap->arr[c_idx] = node;
    
    while(1){
        p_idx = (c_idx-1)/2;
        
        if(c_idx <= 0){
            break;
        }
        if(heap->arr[c_idx]->sum > heap->arr[p_idx]->sum){
            break;
        }
       
        tmp = heap->arr[c_idx];
        heap->arr[c_idx] = heap->arr[p_idx];
        heap->arr[p_idx] = tmp;
        c_idx = p_idx;
    }
    
    heap->num = heap->num + 1;
}

struct node* dequeue(struct heap *heap){
    struct node *ret, *tmp;
    int p_idx, c_idx;
    
    if(heap->num == -1){
        return NULL;
    }
    
    ret = heap->arr[0];
    heap->arr[0] = heap->arr[heap->num];
    p_idx = 0;
    heap->num = heap->num - 1;
    
    while(1){
        c_idx = (p_idx*2) + 1;
        
        if(c_idx > heap->num){
            break;
        }
        else if(c_idx == heap->num){
            if(heap->arr[p_idx]->sum < heap->arr[c_idx]->sum){
                break;
            }
        }
        else{
            if(heap->arr[c_idx]->sum > heap->arr[c_idx+1]->sum){
                c_idx = c_idx+1;
            }
        }
        
        if(heap->arr[c_idx]->sum > heap->arr[p_idx]->sum){
            break;
        }
        
        tmp = heap->arr[c_idx];
        heap->arr[c_idx] = heap->arr[p_idx];
        heap->arr[p_idx] = tmp;
        p_idx = c_idx;
    }

    return ret;
}

struct node* alloc(int sum, int p1, int p2){
    struct node *node = (struct node*)malloc(sizeof(struct node));
    
    node->sum = sum;
    node->p1 = p1;
    node->p2 = p2;
    
    return node;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kClosest(int** points, int pointsSize, int* pointsColSize, int k, int* returnSize, int** returnColumnSizes){
    int i, **ans;
    struct heap heap;
    struct node *node;
    
    ans=(int**)malloc(sizeof(int*)*k);
    *returnSize = k;
    (*returnColumnSizes) = (int*)malloc(sizeof(int)*k);
    for(i=0; i<k; i++){
        ans[i] = (int*)malloc(sizeof(int)*2);
        (*returnColumnSizes)[i] = 2;
    }
    
    init_heap(&heap);
    
    for(i=0; i<pointsSize; i++){
        enqueue(&heap, alloc(points[i][0]*points[i][0]+points[i][1]*points[i][1], points[i][0], points[i][1]));  
    }
   
    for(i=0; i<k; i++){
        node = dequeue(&heap);
        ans[i][0] = node->p1;
        ans[i][1] = node->p2;
    }
    
    deinit_heap(&heap);
    
    return ans;
}
