#define MIN(x,y) (x>y ? y : x)

int minCostClimbingStairs(int* cost, int costSize){
    int tbl[1002], i;
    
    tbl[1] = MIN(cost[0], 0);
    tbl[2] = MIN(tbl[1]+cost[1], cost[0]);
    
    for(i=3; i<=costSize; i++){
        tbl[i] = MIN(tbl[i-2]+cost[i-2], tbl[i-1]+cost[i-1]);
    }
    
    return tbl[costSize];
}
