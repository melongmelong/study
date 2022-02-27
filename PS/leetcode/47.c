
int *tmpans[40320];
int tmpanscnt;

int chk(int *arr, int n){
    int i,j;
    int flag;
    
    for(i=0; i<tmpanscnt; i++){
        flag = 1;
        
        for(j=0; j<n; j++){
            if(arr[j] != tmpans[i][j]){
                flag = 0;
                break;
            }
        }
        
        if(flag == 1){
            return 1;
        }
    }
    
    return 0;
}

void perm(int *nums, int n, int idx, int *arr){
    int i, tmp;
    
    if(idx == n){
        if(chk(arr, n) == 0){
            tmpans[tmpanscnt] = (int*)malloc(sizeof(int)*n);
            memcpy(tmpans[tmpanscnt], arr, sizeof(int)*n);
            tmpanscnt++;
        }
        
        return;
    }
    
    for(i=idx; i<n; i++){
        tmp = nums[i];
        nums[i] = nums[idx];
        nums[idx] = tmp;
   
        arr[idx] = nums[idx];
        
        perm(nums, n, idx+1, arr);
        
        tmp = nums[i];
        nums[i] = nums[idx];
        nums[idx] = tmp;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int arr[8];
    int **ans;
    int i;
    
    tmpanscnt = 0;
    perm(nums, numsSize, 0, arr);
    
    *returnSize = tmpanscnt;
    ans = (int**)malloc(sizeof(int*)*(*returnSize));
    *returnColumnSizes = (int*)malloc(sizeof(int)*(*returnSize));
    for(i=0; i<tmpanscnt; i++){
        (*returnColumnSizes)[i] = numsSize;
        ans[i] = (int*)malloc(sizeof(int)*(*returnColumnSizes)[i]);
        memcpy(ans[i], tmpans[i], sizeof(int)*(*returnColumnSizes)[i]);
    }
    
    return ans;
}
