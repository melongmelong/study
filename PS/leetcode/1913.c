int* merge(int *left, int llen, int *right, int rlen){
    int i,j,k;
    int *ret;
    
    ret = (int*)malloc(sizeof(int)*(llen+rlen));
    
    i = j = k = 0;
    
    while(i<llen && j<rlen){
        if(left[i] < right[j]){
            ret[k] = left[i];
            i++;
        }
        else{
            ret[k] = right[j];
            j++;
        }
        k++;
    }
    
    while(i<llen){
        ret[k] = left[i];
        i++;
        k++;
    }
    while(j<rlen){
        ret[k] = right[j];
        j++;
        k++;
    }
    
    free(left);
    free(right);
    
    return ret;
}

int* mergesort(int *arr, int lidx, int ridx){
    int *left, *right;
    int midx;
    
    if(lidx == ridx){
        left = (int*)malloc(sizeof(int));
        left[0] = arr[lidx];
        return left;
    }
    
    midx = (lidx+ridx)/2;
    
    left = mergesort(arr, lidx, midx);
    right = mergesort(arr, midx+1, ridx);
    
    return merge(left, midx-lidx+1, right, ridx-midx);
}

int maxProductDifference(int* nums, int numsSize){
    int *sorted_nums;
    int ans;
    
    sorted_nums = mergesort(nums, 0, numsSize-1);
    
    ans = (sorted_nums[numsSize-1]*sorted_nums[numsSize-2]) - (sorted_nums[1]*sorted_nums[0]);
    
    free(sorted_nums);
    
    return ans;
}
