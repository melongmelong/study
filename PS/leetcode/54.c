int visit[10][10], dir;
int tmpans[100];
int tmpanscnt;

int next_dir(int dir){
    switch(dir){
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            return 3;
        case 3:
            return 0;
    }
    
    return -1;
}

void dfs(int **matrix, int matrixSize, int matrixColSize, int x, int y){
    if(x<0 || x>=matrixColSize || y<0 || y>=matrixSize){
        dir = next_dir(dir);
        return;
    }
    
    if(visit[y][x]){
        dir = next_dir(dir);
        return;
    }
    visit[y][x] = 1;
    
    tmpans[tmpanscnt] = matrix[y][x];
    tmpanscnt++;

    if(dir == 0){
        dfs(matrix, matrixSize, matrixColSize, x+1, y);
    }
    if(dir == 1){
        dfs(matrix, matrixSize, matrixColSize, x, y+1);
    }
    if(dir == 2){
        dfs(matrix, matrixSize, matrixColSize, x-1, y);
    }
    if(dir == 3){
        dfs(matrix, matrixSize, matrixColSize, x, y-1);
    }
    if(dir == 0){
        dfs(matrix, matrixSize, matrixColSize, x+1, y);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize){
    int *ans;
    
    dir = 0;
    memset(visit, 0, sizeof(visit));
    tmpanscnt = 0;
    
    dfs(matrix, matrixSize, matrixColSize[0], 0, 0);
    
    *returnSize = tmpanscnt;
    ans = (int*)malloc(sizeof(int)*tmpanscnt);
    memcpy(ans, tmpans, sizeof(int)*tmpanscnt);
    return ans;
}
