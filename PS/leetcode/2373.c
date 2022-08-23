
int find_max(int **grid, int x, int y){
    int i, j;
    int ret;
    
    ret = 0;
    
    for(i=y; i<y+3; i++){
        for(j=x; j<x+3; j++){
            if(grid[i][j] > ret){
                ret = grid[i][j];
            }
        }
    }
    
    return ret;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** largestLocal(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes){
    int i, j;
    int** ans;
    
    ans = (int**)malloc(sizeof(int*) * (gridSize-2));
    *returnSize = gridSize-2;
    *returnColumnSizes = (int*)malloc(sizeof(int) * (gridSize-2));
    for(i=0; i<gridSize-2; i++){
        ans[i] = (int*)malloc(sizeof(int) * (gridSize-2));
        (*returnColumnSizes)[i] = gridSize-2;
    }
    
    for(i=0; i<gridSize-2; i++){
        for(j=0; j<gridSize-2; j++){
            ans[i][j] = find_max(grid, j, i);
        }
    }
    
    return ans;
}
