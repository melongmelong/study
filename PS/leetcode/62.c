int uniquePaths(int m, int n){
    int map[100][100] = {0}, i, j;
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            if(i==0 || j==0){
                map[i][j] = 1;
            }
            else{
                map[i][j] = map[i-1][j] + map[i][j-1];
            }
        }
    }
    return map[m-1][n-1];
}
