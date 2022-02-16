int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    static int powtbl[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int tmparr[10], tmparrcnt;
    int **ans;
    int i, j;
   
    ans = (int**)malloc(sizeof(int*)*powtbl[numsSize]);
    *returnSize = powtbl[numsSize];
    *returnColumnSizes = (int*)malloc(sizeof(int)*powtbl[numsSize]);
   
    for(i=0; i<powtbl[numsSize]; i++){
        tmparrcnt = 0;
        
        for(j=0; j<numsSize; j++){
            if((i>>j) & 1){
                tmparr[tmparrcnt] = nums[j];
                tmparrcnt++;
            }
        }
       
        ans[i] = (int*)malloc(sizeof(int)*tmparrcnt);
        (*returnColumnSizes)[i] = tmparrcnt;
        memcpy(ans[i], tmparr, sizeof(int)*tmparrcnt);
    }
    
    return ans;
}
