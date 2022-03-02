int *tmpans[50000];
int tmpanscnt;

void dfs(int *nums, int numsSize, int *tbl, int tblSize, int idx, int *arr){
    int i;
    
    if(idx == numsSize){
        tmpans[tmpanscnt] = (int*)malloc(sizeof(int) * numsSize);
        memcpy(tmpans[tmpanscnt], arr, sizeof(int) * numsSize);
        tmpanscnt++;
        return;
    }
    
    for(i=0; i<tblSize; i++){
        if(tbl[i] == 0){
            continue;
        }
        
        arr[idx] = i-10;
        tbl[i]--;
        
        dfs(nums, numsSize, tbl, tblSize, idx+1, arr);
        
        tbl[i]++;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int tbl[21] = {0,};
    int arr[10] = {0,};
    int i;
    int **ans;
   
    tmpanscnt = 0;
    
    for(i=0; i<numsSize; i++){
        tbl[nums[i] + 10]++;
    }

    dfs(nums, numsSize, tbl, sizeof(tbl)/sizeof(int), 0, arr);
    
    *returnColumnSizes = (int*)malloc(sizeof(int) * tmpanscnt);
    *returnSize = tmpanscnt;
    ans = (int**)malloc(sizeof(int*) * tmpanscnt);
    for(i=0; i<tmpanscnt; i++){
        ans[i] = tmpans[i];
        (*returnColumnSizes)[i] = numsSize;
    }
    return ans;
}
