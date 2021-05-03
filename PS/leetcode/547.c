
void dfs(int **isConnected, int isConnectedSize, int node, int *visit){
    int i;
   
    if(visit[node-1]){
        return;
    }
    
    visit[node-1] = 1;
    
    for(i=0; i<isConnectedSize; i++){
        if(i == node-1){
            continue;
        }
        if(isConnected[node-1][i]){
            dfs(isConnected, isConnectedSize, i+1, visit);
        }
    }
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize){
    int visit[200] = {0}, ans=0, i;
    
    for(i=0; i<isConnectedSize; i++){
        if(visit[i] == 0){
            dfs(isConnected, isConnectedSize, i+1, visit);
            ans++;
        }
    }
    
    return ans;
}
