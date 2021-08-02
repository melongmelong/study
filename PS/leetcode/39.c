int tmpans[150][500];
int tmpcnts[150];
int anscnt;

void dfs(int *candidates, int candidatesSize, int target, int idx, int *arr, int cnt, int sum){
    int i;
   
    if(target < sum){
        return;
    }
    
    if(target == sum){
        memcpy(tmpans[anscnt], arr, sizeof(int)*cnt);
        tmpcnts[anscnt] = cnt;
        anscnt++;
        return;
    }
    
    for(i=idx; i<candidatesSize; i++){
        arr[cnt] = candidates[i];
        dfs(candidates, candidatesSize, target, i, arr, cnt+1, sum+candidates[i]);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes){
    int arr[500], **ans, i;
    
    anscnt = 0;
    dfs(candidates, candidatesSize, target, 0, arr, 0, 0);
   
    *returnSize = anscnt;
    *returnColumnSizes = (int*)malloc(sizeof(int)*anscnt);
    for(i=0; i<anscnt; i++){
        (*returnColumnSizes)[i] = tmpcnts[i];
    }
    
    ans = (int**)malloc(sizeof(int*)*anscnt);
    for(i=0; i<anscnt; i++){
        ans[i] = (int*)malloc(sizeof(int)*tmpcnts[i]);
        memcpy(ans[i], tmpans[i], sizeof(int)*tmpcnts[i]);
    }
    
    return ans;
}
