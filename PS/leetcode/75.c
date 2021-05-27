void sortColors(int* nums, int numsSize){
    int i,j,tmp;
    for(i=numsSize; i>0; i--){
        for(j=0; j<i-1; j++){
            if(nums[j] >= nums[j+1]){
                tmp = nums[j+1];
                nums[j+1] = nums[j];
                nums[j] = tmp;
            }
        }
    }
}
