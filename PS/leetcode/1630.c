
int* mergesort(int *arr1, int len1, int *arr2, int len2){
    int i1=0, i2=0, i3=0;
    int *ret = (int*)malloc(sizeof(int)*(len1+len2));
    
    while(i1<len1 && i2<len2){
        if(arr1[i1] < arr2[i2]){
            ret[i3] = arr1[i1];
            i1++;
        }
        else{
            ret[i3] = arr2[i2];
            i2++;
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

int *merge(int *arr, int s, int e){
    int m = (s+e)/2;
    int *arr1, *arr2;
    
    if(s == e){
        arr1 = (int*)malloc(sizeof(int));
        *arr1 = arr[s];
        return arr1;
    }
    
    arr1 = merge(arr, s, m);
    arr2 = merge(arr, m+1, e);
    return mergesort(arr1, m-s+1, arr2, e-m);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* checkArithmeticSubarrays(int* nums, int numsSize, int* l, int lSize, int* r, int rSize, int* returnSize){
    int arr[500], i, j, k, diff, *sorted;
    bool *ans = (bool*)malloc(sizeof(bool)*lSize), flag=true;
    *returnSize = 0;
    
    for(i=0; i<lSize; i++){
        k = 0;
        for(j=l[i]; j<=r[i]; j++){
            arr[k] = nums[j];
            k++;
        }
       
        sorted = merge(arr, 0, k-1);
        
        if(k<2){
            ans[*returnSize] = false;
        }
        else{
            flag = true;
            diff = sorted[1] - sorted[0];
            for(j=2; j<k; j++){
                if(sorted[j]-sorted[j-1] != diff){
                    flag = false;
                    break;
                }
            }
            ans[*returnSize] = flag;
        }
        *returnSize = *returnSize + 1;
        free(sorted);
    }
    return ans;
}
