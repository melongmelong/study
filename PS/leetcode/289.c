int chk_neigh(int **board, int n, int m, int live, int x, int y){
    int cnt=0;
    if(x-1>=0 && board[y][x-1]==live){
        cnt++;
    }   
    if(y-1>=0 && board[y-1][x]==live){
        cnt++;
    }
    if(x+1<m && board[y][x+1]==live){
        cnt++;
    }
    if(y+1<n && board[y+1][x]==live){
        cnt++;
    }
    if(x-1>=0 && y-1>=0 && board[y-1][x-1]==live){
        cnt++;
    }
    if(x-1>=0 && y+1<n && board[y+1][x-1]==live){
        cnt++;
    }
    if(x+1<m && y-1>=0 && board[y-1][x+1]==live){
        cnt++;
    }
    if(x+1<m && y+1<n && board[y+1][x+1]==live){
        cnt++;
    }
    return cnt;
}

void next(int **board, int n, int m){
    int nextboard[25][25], i,j,cnt_live, cnt_dead;
    for(i=0; i<n; i++){
        for(j=0; j<m; j++){
            nextboard[i][j] = board[i][j];
            cnt_live = chk_neigh(board, n, m, 1, j, i);
            cnt_dead = chk_neigh(board, n, m, 0, j, i);
            if(board[i][j] == 1){
                if(cnt_live<2){
                    nextboard[i][j] = 0;
                }
                else if(cnt_live<=3){
                    nextboard[i][j] = 1;
                }
                else if(cnt_live>3){
                    nextboard[i][j] = 0;
                }
            }
            else{
                if(cnt_live==3){
                    nextboard[i][j] = 1;
                }
            }
        }
    }
    for(i=0; i<n; i++){
        memcpy(board[i], nextboard[i], sizeof(int)*m);
    }
}

void gameOfLife(int** board, int boardSize, int* boardColSize){
    next(board, boardSize, boardColSize[0]);
}
