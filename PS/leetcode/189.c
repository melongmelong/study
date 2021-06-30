void rotate(int* nums, int numsSize, int k){
    int ans[100000], i, j;
    
    for(i=0; i<numsSize; i++){
        ans[(i+k)%numsSize] = nums[i];
    }
    
    memcpy(nums, ans, sizeof(int)*numsSize);
}
