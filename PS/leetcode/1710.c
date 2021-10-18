
int** alloc_boxTypes(int **boxTypes){
    int **ret;
    
    ret = (int**)malloc(sizeof(int*));
    
    ret[0] = (int*)malloc(sizeof(int)*2);
    ret[0][0] = boxTypes[0][0];
    ret[0][1] = boxTypes[0][1];
    
    return ret;
}

int** merge(int **left, int llen, int **right, int rlen){
    int **ret;
    int i,j,k;
    
    ret = (int**)malloc(sizeof(int*)*(llen+rlen));
    for(i=0; i<llen+rlen; i++){
        ret[i] = (int*)malloc(sizeof(int)*2);
    }
    
    i = j = k = 0; 
    while(i<llen && j<rlen){
        if(left[i][1] <= right[j][1]){
            memcpy(ret[k], right[j], sizeof(int)*2);
            j++;
        }
        else{
            memcpy(ret[k], left[i], sizeof(int)*2);
            i++;
        }
        k++;
    }
    while(i<llen){
        memcpy(ret[k], left[i], sizeof(int)*2);
        i++;
        k++;
    }
    while(j<rlen){
        memcpy(ret[k], right[j], sizeof(int)*2);
        j++;
        k++;
    }
    
    return ret;
}

int** mergesort(int **boxTypes, int start, int end){
    int mid;
    int **left, **right;
   
    if(start >= end){
        return alloc_boxTypes(&boxTypes[start]);
    }
    
    mid = (start+end)/2;
    
    left = mergesort(boxTypes, start, mid);
    right = mergesort(boxTypes, mid+1, end);
    
    return merge(left, mid-start+1, right, end-mid);
}

int maximumUnits(int** boxTypes, int boxTypesSize, int* boxTypesColSize, int truckSize){
    int **sorted_boxTypes;
    int i;
    int ans;
    
    sorted_boxTypes = mergesort(boxTypes, 0, boxTypesSize-1);
    
    ans = 0;
    for(i=0; i<boxTypesSize; i++){
        if(truckSize == 0){
            break;
        }
        
        if(sorted_boxTypes[i][0] <= truckSize){
            truckSize -= sorted_boxTypes[i][0];
            ans += sorted_boxTypes[i][0] * sorted_boxTypes[i][1];
        }
        else{
            ans += truckSize * sorted_boxTypes[i][1];
            truckSize = 0;
        }
    }
    
    for(i=0; i<boxTypesSize; i++){
        free(sorted_boxTypes[i]);
    }
    free(sorted_boxTypes);
    
    return ans;
}
