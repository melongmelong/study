int maxSubArray(int* nums, int numsSize){
    int i, j, ans, sum;
    
    ans = -1000000;
    sum = 0;
    
    for(i=0; i<numsSize; i++){
        sum = 0;
        
        for(j=0; j<=i; j++){
            sum += nums[j];
        }
        
        if(sum > ans){
            ans = sum;
        }
        
        for(j=i+1; j<numsSize; j++){
            sum = sum + nums[j] - nums[j-(i+1)];
            
            if(sum > ans){
                ans = sum;
            }
        }
    }
    
    return ans;
}
