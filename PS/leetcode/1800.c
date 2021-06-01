
int maxAscendingSum(int* nums, int numsSize){
    int i,ans=0,sum=0;
    sum = nums[0];
    for(i=1; i<numsSize; i++){
        if(nums[i-1] < nums[i]){
            sum += nums[i];
        }
        else{
            if(sum > ans){
                ans = sum;
            }
            sum = nums[i];
        }
    }
    if(ans < sum){
        ans = sum;
    }
    return ans;
}
