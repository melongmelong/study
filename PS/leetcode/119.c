/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* copy_arr(int *arr, int len){
    int *ret;
    
    ret = (int*)malloc(sizeof(int)*len);
    memcpy(ret, arr, sizeof(int)*len);
    
    return ret;
}

int* getRow(int rowIndex, int* returnSize){
    int i,j,triangle[34][34];
    int *ans;
   
    triangle[0][0] = 1;
    triangle[1][0] = triangle[1][1] = 1;
    
    if(rowIndex==0){
        *returnSize = 1;
        ans = copy_arr(triangle[0], *returnSize);
        return ans;
    }
    else if(rowIndex==1){
        *returnSize = 2;
        ans = copy_arr(triangle[1], *returnSize);
        return ans;
    }
    
    for(i=0; i<=rowIndex; i++){
        for(j=0; j<i+1; j++){
            if(j==0 || j==i){
                triangle[i][j] = 1;
            }
            else{
                triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
            }
        }
    }
   
    *returnSize = rowIndex+1;
    ans = copy_arr(triangle[rowIndex], *returnSize);
    return ans;
}
