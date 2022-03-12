
void fill(int **arr, int n, int sx, int sy, int snum, int *nx, int *ny, int *nnum){
    int i;
    
    for(i=0; i<n; i++){
        arr[sy][i+sx] = snum;
        snum++;
    }
    for(i=0; i<n-1; i++){
        arr[i+sy+1][sx+n-1] = snum;
        snum++;
    }
    for(i=0; i<n-1; i++){
        arr[sy+n-1][sx+n-2-i] = snum;
        snum++;
    }
    for(i=0; i<n-2; i++){
        arr[sy+n-2-i][sx] = snum;
        snum++;
    }
    
    *nx = sx+1;
    *ny = sy+1;
    *nnum = snum;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generateMatrix(int n, int* returnSize, int** returnColumnSizes){
    int nx, ny, nnum;
    int i;
    int **ans;
    
    ans = (int**)malloc(sizeof(int*) * n);
    for(i=0; i<n; i++){
        ans[i] = (int*)malloc(sizeof(int) * n);
    }
    
    *returnColumnSizes = (int*)malloc(sizeof(int) * n);
    for(i=0; i<n; i++){
        (*returnColumnSizes)[i] = n;
    }
    
    *returnSize = n;
   
    nx = ny = 0;
    nnum = 1;
    while(n > 0){
        fill(ans, n, nx, ny, nnum, &nx, &ny, &nnum);
        n -= 2;
    }
    
    return ans;
}
