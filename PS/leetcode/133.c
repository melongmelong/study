/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */

void dfs(struct Node *org, struct Node **copy, struct Node **visit){
    int i;
   
    if(visit[org->val]){
        *copy = visit[org->val];
        return;
    }
   
    *copy = (struct Node*)malloc(sizeof(struct Node));
    
    (*copy)->val = org->val;
    
    (*copy)->numNeighbors = org->numNeighbors;
    if((*copy)->numNeighbors > 0){
        (*copy)->neighbors = (struct Node**)malloc(sizeof(struct Node*) * (*copy)->numNeighbors);
    }
    else{
        (*copy)->neighbors = NULL;
    }
    
    visit[org->val] = *copy;
    
    for(i=0; i<org->numNeighbors; i++){
        dfs(org->neighbors[i], &(*copy)->neighbors[i], visit);
    }
}

struct Node *cloneGraph(struct Node *s) {
    struct Node *ans = NULL;
    struct Node *visit[101] = {NULL};
    
    if(s == NULL){
        return NULL;
    }
    
    dfs(s, &ans, visit);
    
    return ans;
}
