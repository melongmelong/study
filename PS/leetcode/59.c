

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generateMatrix(int n, int* returnSize, int** returnColumnSizes){
    int tbl[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    int state = 0;
    int num;
    int r, c, i;
    int **ans;
   
    ans = (int**)malloc(sizeof(int*) * n);
    for(i=0; i<n; i++){
        ans[i] = (int*)malloc(sizeof(int) * n);
        memset(ans[i], 0, sizeof(int) * n);
    }
    
    *returnColumnSizes = (int*)malloc(sizeof(int) * n);
    for(i=0; i<n; i++){
        (*returnColumnSizes)[i] = n;
    }
    
    *returnSize = n;
  
    r = c = 0;
    num = 1;
    while(num <= n*n){
        ans[r][c] = num;
        
        if(r+tbl[state][0] >= n || c+tbl[state][1] >= n || r+tbl[state][0] < 0 || c+tbl[state][1] < 0 
           || ans[r+tbl[state][0]][c+tbl[state][1]] != 0){
            state = (state + 1) % 4;
        }
        
        r = r + tbl[state][0];
        c = c + tbl[state][1];
        
        num++;
    }
    
    return ans;
}
