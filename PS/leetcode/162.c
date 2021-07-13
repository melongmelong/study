
int findPeakElement(int* nums, int numsSize){
    int i;
    
    for(i=0; i<numsSize; i++){
        if(i-1<0 && i+1>=numsSize){
            break;
        }
        else if(i-1<0){
            if(nums[i] > nums[i+1]){
                break;
            }
        }
        else if(i+1>=numsSize){
            if(nums[i] > nums[i-1]){
                break;
            }
        }
        else{
            if(nums[i-1]<nums[i] && nums[i]>nums[i+1]){
                break;
            }
        }
    }
    
    return i;
}
