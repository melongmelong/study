/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize){
    int *ans = (int*)malloc(sizeof(int)*2), s=0, e=numsSize-1;
    ans[0] = -1;
    ans[1] = -1;
    *returnSize = 2;
    while(e>=0){
        if(nums[s] == target){
            if(ans[0] == -1){
                ans[0] = s;
            }
        }
        if(nums[e] == target){
            if(ans[1] == -1){
                ans[1] = e;
            }
        }
        s++;
        e--;
    }
    return ans;
}
