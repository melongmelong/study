int ans;

void dfs(int **grid, int gridSize, int gridColSize, int visit[][15], int y, int x, int sum){
    if(ans < sum){
        ans = sum;
    }
    if(y<0 || y>=gridSize || x<0 || x>=gridColSize){
        return;
    }
    if(grid[y][x] == 0){
        return;
    }
    if(visit[y][x]){
        return;
    }
    visit[y][x] = 1;
    dfs(grid, gridSize, gridColSize, visit, y-1, x, sum+grid[y][x]);
    dfs(grid, gridSize, gridColSize, visit, y+1, x, sum+grid[y][x]);
    dfs(grid, gridSize, gridColSize, visit, y, x-1, sum+grid[y][x]);
    dfs(grid, gridSize, gridColSize, visit, y, x+1, sum+grid[y][x]);
    visit[y][x] = 0;
}

int getMaximumGold(int** grid, int gridSize, int* gridColSize){
    int i,j,visit[15][15]={0,};
    ans=0;
    for(i=0; i<gridSize; i++){
        for(j=0; j<gridColSize[0]; j++){
            if(grid[i][j]){
                dfs(grid, gridSize, gridColSize[0], visit, i, j, 0);
            }
        }
    }
    return ans;
}
