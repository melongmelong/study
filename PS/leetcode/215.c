
int* mergesort(int *arr1, int len1, int *arr2, int len2){
    int i1=0, i2=0, i3=0;
    int *ret = (int*)malloc(sizeof(int)*(len1+len2));
    while(i1<len1 && i2<len2){
        if(arr1[i1] < arr2[i2]){
            ret[i3] = arr2[i2];
            i2++;
        }
        else{
            ret[i3] = arr1[i1];
            i1++;
        }
        i3++;
    }
    while(i1<len1){
        ret[i3] = arr1[i1];
        i1++;
        i3++;
    }
    while(i2<len2){
        ret[i3] = arr2[i2];
        i2++;
        i3++;
    }
    free(arr1);
    free(arr2);
    return ret;
}

int* merge(int *arr, int start, int end){
    int mid = (start+end)/2;
    int *ret1, *ret2;
    if(start == end){
        ret1 = (int*)malloc(sizeof(int));
        ret1[0] = arr[start];
        return ret1;
    }
    ret1 = merge(arr, start, mid);
    ret2 = merge(arr, mid+1, end);
    return mergesort(ret1, mid-start+1, ret2, end-mid);
}

int findKthLargest(int* nums, int numsSize, int k){
    int *sorted = merge(nums, 0, numsSize-1);
    int ans = sorted[k-1];
    free(sorted);
    return ans;
}
