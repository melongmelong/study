int diagonalSum(int** mat, int matSize, int* matColSize){
    int i, ans=0;
    for(i=0; i<matSize; i++){
        ans += mat[i][i];
        mat[i][i] = 0;
    }
    for(i=0; i<matSize; i++){
        ans += mat[i][matSize-1-i];
        mat[i][matSize-1-i] = 0;
    }
    return ans;
}
