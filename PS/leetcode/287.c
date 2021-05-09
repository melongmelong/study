int findDuplicate(int* nums, int numsSize){
    int tbl[100001] = {0,}, i;
    for(i=0; i<numsSize; i++){
        if(tbl[nums[i]]){
            return nums[i];
        }
        tbl[nums[i]]++;
    }
    return -1;
}
