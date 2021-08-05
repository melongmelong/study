
int** __mergesort(int **left, int llen, int **right, int rlen){
    int i,j,k;
    int **ret;
    
    ret = (int**)malloc(sizeof(int*)*(llen+rlen));
    for(i=0; i<llen+rlen; i++){
        ret[i] = (int*)malloc(sizeof(int)*2);
    }
    
    i = j = k = 0;
    
    while(i<llen && j<rlen){
        if(left[i][0] < right[j][0]){
            ret[k][0] = left[i][0];
            ret[k][1] = left[i][1];
            i++;
        }
        else{   
            ret[k][0] = right[j][0];
            ret[k][1] = right[j][1];
            j++;
        }
        k++;
    }
    
    while(i<llen){
        ret[k][0] = left[i][0];
        ret[k][1] = left[i][1];
        i++;
        k++;
    }
    while(j<rlen){
        ret[k][0] = right[j][0];
        ret[k][1] = right[j][1];
        j++;
        k++;
    }
    
    return ret;
}

int** mergesort(int **arr, int start, int end){
    int mid;
    int **left, **right;
    
    if(start >= end){
        left = (int**)malloc(sizeof(int*));
        left[0] = (int*)malloc(sizeof(int)*2);
        left[0][0] = arr[start][0];
        left[0][1] = arr[start][1];
        
        return left;
    }
    
    mid = (start+end)/2;
    
    left = mergesort(arr, start, mid);
    right = mergesort(arr, mid+1, end);
    
    return __mergesort(left, (mid-start+1), right, (end-mid-1)+1);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    int **sorted_intervals;
    int tmpans[10000][2], tmpansidx, **ans, anscnt;
    int i;
    
    sorted_intervals = mergesort(intervals, 0, intervalsSize-1);
   
    tmpansidx = 0;
    tmpans[tmpansidx][0] = sorted_intervals[0][0];
    tmpans[tmpansidx][1] = sorted_intervals[0][1];
    for(i=1; i<intervalsSize; i++){
        if(tmpans[tmpansidx][0] <= sorted_intervals[i][0] && sorted_intervals[i][0] <= tmpans[tmpansidx][1]){
            if(sorted_intervals[i][1] > tmpans[tmpansidx][1]){
                tmpans[tmpansidx][1] = sorted_intervals[i][1];
            }
        }
        else{
            tmpansidx++;
            tmpans[tmpansidx][0] = sorted_intervals[i][0];
            tmpans[tmpansidx][1] = sorted_intervals[i][1];
        }
    }
    
    anscnt = tmpansidx+1;
    *returnSize = anscnt;
    *returnColumnSizes = (int*)malloc(sizeof(int)*anscnt);
    ans = (int**)malloc(sizeof(int*)*anscnt);
    for(i=0; i<anscnt; i++){
        ans[i] = (int*)malloc(sizeof(int)*2);
        memcpy(ans[i], tmpans[i], sizeof(int)*2);
        (*returnColumnSizes)[i] = 2;
    }
    
    for(i=0; i<intervalsSize; i++){
        free(sorted_intervals[i]);
    }
    free(sorted_intervals);
    
    return ans;
}
