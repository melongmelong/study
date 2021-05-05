int get_idx(int *nums, int numsSize, int idx){
    int i, nidx=0, ret=0;
    
    for(i=idx+1; i<=idx+nums[idx]; i++){
        if(i < numsSize){
            if(nidx < i + nums[i]){
                nidx = i + nums[i];
                ret = i;
            }
            if(i == numsSize-1){
                return numsSize-1; 
            }
        }
    }
    return ret;
}

int jump(int* nums, int numsSize){
    int ans=0, cidx=0;
    while(cidx != numsSize-1){
        cidx = get_idx(nums, numsSize, cidx);
        ans++;
    }
    return ans;
}
