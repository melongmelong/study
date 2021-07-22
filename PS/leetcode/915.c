
int chk(int *arr, int n, int limit, int val){
    int i;
    
    for(i=n-1; i>limit; i--){
        if(arr[i] < val){
            return 1;
        }
    }
    
    return 0;
}

int partitionDisjoint(int* nums, int numsSize){
    int ans, max;
    
    ans = 0;
    max = -1;
    
    while(ans<numsSize){
        if(nums[ans] > max){
            max = nums[ans];
        }
        
        if(!chk(nums, numsSize, ans, max)){
            break;
        }
        
        ans++;
    }
    
    return ans+1;
}
