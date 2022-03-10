struct node{
    int *arr;
    int cnt;
};

struct vector{
    struct node **node;
    int cnt;
    int max;
};

void init_vector(struct vector *v, int max){
    v->node = (struct node**)malloc(sizeof(struct node*) * max);
    v->cnt = 0;
    v->max = max;
}

void add_vector(struct vector *v, struct node *node){
    if(v->cnt+1 > v->max){
        v->max *= 2;
        v->node = (struct node**)realloc(v->node, sizeof(struct node*) * v->max);
    }
    
    v->node[v->cnt] = node;
    v->cnt++;
}

int chk(struct vector *v, int *arr, int cnt){
    int i, j, flag;
    int tbl[51];
    
    for(i=0; i<v->cnt; i++){
        memset(tbl, 0, sizeof(tbl));
      
        for(j=0; j<v->node[i]->cnt; j++){
            tbl[v->node[i]->arr[j]]++;
        }
       
        for(j=0; j<cnt; j++){
            tbl[arr[j]]--;
        }
        
        flag = 1;
        for(j=0; j<=50; j++){
            if(tbl[j]){
                flag = 0;
                break;
            }
        }
        if(flag){
            return 1;
        }
    }
   
    return 0;
}

void dfs(int *candidatestbl, int target_sum, int cur_sum, int idx, int *arr, struct vector *v){
    int i;
    struct node *node;
  
    if(cur_sum == target_sum){
        if(chk(v, arr, idx) == 0){
            node = (struct node*)malloc(sizeof(struct node));
            node->arr = (int*)malloc(sizeof(int) * idx);
            node->cnt = idx;
            memcpy(node->arr, arr, sizeof(int) * idx);
            
            add_vector(v, node);
        }
        return;
    } 
    
    if(cur_sum > target_sum){
        return;
    }
    
    for(i=0; i<=50; i++){
        if(candidatestbl[i] == 0){
            continue;
        }
        
        candidatestbl[i]--;
        
        arr[idx] = i;
        
        dfs(candidatestbl, target_sum, cur_sum + i, idx+1, arr, v);
        
        candidatestbl[i]++;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes){
    struct vector v;
    int candidatestbl[51] = {0,};
    int tmparr[100];
    int i;
    int **ans;
    
    init_vector(&v, 128);
    
    for(i=0; i<candidatesSize; i++){
        candidatestbl[candidates[i]]++;
    }
    
    dfs(candidatestbl, target, 0, 0, tmparr, &v);
    
    *returnSize = v.cnt;
    ans = (int**)malloc(sizeof(int*) * (*returnSize));
    *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));
    for(i=0; i<(*returnSize); i++){
        ans[i] = v.node[i]->arr;
        (*returnColumnSizes)[i] = v.node[i]->cnt;
    }
    
    for(i=0; i<v.cnt; i++){
        free(v.node[i]);
    }
    
    return ans;
}
