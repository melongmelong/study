
int get_next(int *nums, int numsSize, int start){
    int i;
    for(i=start+1; i<numsSize; i++){
        if(nums[i] > nums[start]){
            return i;
        }
    }
    for(i=0; i<start; i++){
        if(nums[i] > nums[start]){
            return i;
        }
    }
    return -1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextGreaterElements(int* nums, int numsSize, int* returnSize){
    int i,next,*ans=(int*)malloc(sizeof(int)*numsSize);
    for(i=0; i<numsSize; i++){
        next = get_next(nums, numsSize, i);
        if(next >= 0){
            ans[i] = nums[next];
        }
        else{
            ans[i] = -1;
        }
    }
    *returnSize = numsSize;
    return ans;
}
