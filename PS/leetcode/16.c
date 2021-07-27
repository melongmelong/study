#define DIFF(x,y) x>y ? x-y : y-x

int ans;

void comb(int *nums, int numsSize, int k, int target, int cur, int idx, int sum){
    if(cur == k){
        if((DIFF(sum, target)) < (DIFF(ans, target))){
            ans = sum;
        }
        return;
    }
    if(idx == numsSize){
        return;
    }
    
    comb(nums, numsSize, k, target, cur+1, idx+1, sum+nums[idx]);
    comb(nums, numsSize, k, target, cur, idx+1, sum);
}

int threeSumClosest(int* nums, int numsSize, int target){
    ans = 200000000;
    
    comb(nums, numsSize, 3, target, 0, 0, 0);
    
    return ans;
}
