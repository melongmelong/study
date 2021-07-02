
struct node{
    int num;
    int diff;
};

struct node* merge(struct node *left, int llen, struct node *right, int rlen){
    int l,r,i;
    struct node *ret;
    
    ret = (struct node*)malloc(sizeof(struct node)*(llen+rlen));
    l = r = i = 0;
    
    while(l<llen && r<rlen){
        if(left[l].diff < right[r].diff){
            ret[i] = left[l];
            l++;
        }
        else if(left[l].diff > right[r].diff){
            ret[i] = right[r];
            r++;
        }
        else{
            if(left[l].num < right[r].num){
                ret[i] = left[l];
                l++;
            }
            else{
                ret[i] = right[r];
                r++;
            }
        }
        i++;
    }
    
    while(l<llen){
        ret[i] = left[l];
        l++;
        i++;
    }
    while(r<rlen){
        ret[i] = right[r];
        r++;
        i++;
    }
    
    return ret;
}

struct node* mergesort(struct node *arr, int start, int end){
    int mid;
    struct node *left, *right;
    
    if(start >= end){
        left = (struct node*)malloc(sizeof(struct node));
        left[0].num = arr[start].num;
        left[0].diff = arr[start].diff;
        return left;
    }
    
    mid = (start+end)/2;
    left = mergesort(arr, start, mid);
    right = mergesort(arr, mid+1, end);
    return merge(left, mid-start+1, right, end-(mid+1)+1);
}

int* merge2(int *left, int llen, int *right, int rlen){
    int l,r,i;
    int *ret;
    
    ret = (int*)malloc(sizeof(int)*(llen+rlen));
    l = r = i = 0;
    
    while(l<llen && r<rlen){
        if(left[l] < right[r]){
            ret[i] = left[l];
            l++;
        }
        else{
            ret[i] = right[r];
            r++;
        }
        i++;
    }
    
    while(l<llen){
        ret[i] = left[l];
        l++;
        i++;
    }
    while(r<rlen){
        ret[i] = right[r];
        r++;
        i++;
    }
    
    return ret;
}

int* mergesort2(int *arr, int start, int end){
    int mid;
    int *left, *right;
    
    if(start >= end){
        left = (int*)malloc(sizeof(int));
        left[0] = arr[start];
        return left;
    }
    
    mid = (start+end)/2;
    left = mergesort2(arr, start, mid);
    right = mergesort2(arr, mid+1, end);
    return merge2(left, mid-start+1, right, end-(mid+1)+1);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize){
    struct node tmparr[10000], *sorted_arr;
    int tmpans[10000], *ans, i;
    
    ans = (int*)malloc(sizeof(int)*k);
    *returnSize = k;
    
    for(i=0; i<arrSize; i++){
        tmparr[i].num = arr[i];
        tmparr[i].diff = x>arr[i] ? x-arr[i] : arr[i]-x;
    }
    
    sorted_arr = mergesort(tmparr, 0, arrSize-1);
    for(i=0; i<k; i++){
        tmpans[i] = sorted_arr[i].num;
    }
    free(sorted_arr);
    
    ans = mergesort2(tmpans, 0, k-1);
    
    return ans;
}
