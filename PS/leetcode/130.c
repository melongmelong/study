int arr[40000][2], cnt, flag;

void dfs(char **board, int n, int m, int visit[][200], int x, int y){
    if(x<0 || x>=m || y<0 || y>=n){
        return;
    }
    if(board[y][x]=='X' || visit[y][x]){
        return;
    }
    
    visit[y][x] = 1;
   
    arr[cnt][0] = x;
    arr[cnt][1] = y;
    cnt++;
    
    if(x==0 || x==m-1 || y==0 || y==n-1){
        flag = 1;
    }
    
    dfs(board, n, m, visit, x+1, y);
    dfs(board, n, m, visit, x-1, y);
    dfs(board, n, m, visit, x, y+1);
    dfs(board, n, m, visit, x, y-1);
}

void solve(char** board, int boardSize, int* boardColSize){
    int visit[200][200]={0,}, i=0, j=0, k=0;
   
    for(i=0; i<boardSize; i++){
        for(j=0; j<boardColSize[0]; j++){
            if(visit[i][j] || board[i][j]=='X'){
                continue;
            }
            
            cnt = 0;
            flag = 0;
         
            dfs(board, boardSize, boardColSize[0], visit, j, i);
          
            if(flag){
                continue;
            }
            for(k=0; k<cnt; k++){
                board[arr[k][1]][arr[k][0]] = 'X';
            }
        }
    }
}
