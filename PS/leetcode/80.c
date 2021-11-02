
inline static void swap(int *a, int *b){
    int tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int removeDuplicates(int* nums, int numsSize){
    int i, j;
    int candidate, cnt;
    int numslen;
    
    numslen = numsSize;
    candidate = nums[0];
    cnt = 0;
    
    for(i=0; i<numslen; i++){
        if(nums[i] == candidate){
            cnt++;
            if(cnt > 2){
                for(j=i; j<numslen-1; j++){
                    swap(&nums[j], &nums[j+1]);
                }
                i--;
                numslen--;
            }
        }
        else{
            candidate = nums[i];
            cnt = 1;
        }
    }
    
    return numslen;
}
