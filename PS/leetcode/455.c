int* merge(int *left, int llen, int *right, int rlen){
    int *ret;
    int i,j,k;

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

int* mergesort(int *arr, int start, int end){
    int *left, *right;
    int mid;
    
    if(start >= end){
        left = (int*)malloc(sizeof(int));
        left[0] = arr[start];
        
        return left;
    }
    
    mid = (start+end)/2;
    
    left = mergesort(arr, start, mid);
    right = mergesort(arr, mid+1, end);
    
    return merge(left, mid-start+1, right, end-mid);
}

int findContentChildren(int* g, int gSize, int* s, int sSize){
    int *sorted_g, *sorted_s;
    int i,j;
    int ans;
  
    if(sSize == 0){
        return 0;
    }
    
    sorted_g = mergesort(g, 0, gSize-1);
    sorted_s = mergesort(s, 0, sSize-1);
 
    ans = 0;
    i = j = 0;
    for(i=0; i<gSize; i++){
        if(j<sSize && sorted_g[i] <= sorted_s[j]){
            ans++;
            j++;
        }
        else{
            for(; j<sSize; j++){
                if(sorted_g[i] <= sorted_s[j]){
                    ans++;
                    j++;
                    break;
                }
            }
        }
    }
    
    free(sorted_g);
    free(sorted_s);
    
    return ans;
}
