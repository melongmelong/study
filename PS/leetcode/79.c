bool ans;

void dfs(char **board, int boardSize, int boardColSize, int visit[][6], char *word, int idx, int x, int y){
    if(word[idx] == '\0'){
        ans = true;
        return;
    }
    if(x<0 || x>=boardColSize || y<0 || y>=boardSize){
        return;
    }
    if(visit[y][x] == 1){
        return;
    }
    if(board[y][x] != word[idx]){
        return;
    }
   
    visit[y][x] = 1;
    
    dfs(board, boardSize, boardColSize, visit, word, idx+1, x+1, y);
    dfs(board, boardSize, boardColSize, visit, word, idx+1, x-1, y);
    dfs(board, boardSize, boardColSize, visit, word, idx+1, x, y+1);
    dfs(board, boardSize, boardColSize, visit, word, idx+1, x, y-1);
    
    visit[y][x] = 0;
}

bool exist(char** board, int boardSize, int* boardColSize, char * word){
    int i,j,visit[6][6];
   
    ans = false;
    memset(visit, 0, sizeof(visit));
    
    for(i=0; i<boardSize; i++){
        for(j=0; j<boardColSize[0]; j++){
            dfs(board, boardSize, boardColSize[0], visit, word, 0, j, i);
        }
    }
    
    return ans;
}
