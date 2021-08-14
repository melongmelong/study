int climbStairs(int n){
    int tbl[45];
    int i;
    
    tbl[0] = 1;
    tbl[1] = 2;
    
    for(i=2; i<n; i++){
        tbl[i] = tbl[i-1] + tbl[i-2];
    }

    return tbl[n-1];
}
