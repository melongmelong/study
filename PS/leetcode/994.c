struct node{
    struct node *next;
    int x,y;
};

struct queue{
    struct node *head, *tail;
};

void init_queue(struct queue *queue){
    queue->head = queue->tail = NULL;
}

void deinit_queue(struct queue *queue){
    struct node *del, *tmp;
    
    tmp = queue->head;
    while(tmp){
        del = tmp;
        tmp = tmp->next;
        free(del);
    }
}

void enqueue(struct queue *queue, int x, int y){
    struct node *node;
    
    node = (struct node*)malloc(sizeof(struct node));
    node->x = x;
    node->y = y;
    node->next = NULL;
   
    if(queue->head == NULL){
        queue->head = queue->tail = node;
        return;
    }
    
    queue->tail->next = node;
    queue->tail = node;
}

struct node* dequeue(struct queue *queue){
    struct node *node;
    
    node = queue->head;
    
    if(node){
        queue->head = node->next;
    }
    
    return node;
}

int orangesRotting(int** grid, int gridSize, int* gridColSize){
    int i,j, flag;
    int tmpgrid[10][10];
    struct queue queue1, queue2, *pqueue1, *pqueue2, *ptmpqueue;
    struct node *node;
    int ans;
    
    init_queue(&queue1);
    init_queue(&queue2);
    pqueue1 = &queue1;
    pqueue2 = &queue2;
    
    for(i=0; i<gridSize; i++){
        memcpy(tmpgrid[i], grid[i], sizeof(int)*gridColSize[i]);
    }
   
    for(i=0; i<gridSize; i++){
        for(j=0; j<gridColSize[0]; j++){
            if(tmpgrid[i][j] == 2){
                enqueue(pqueue1, j, i);
            }
        }
    }
    
    flag = 0;
    if(pqueue1->head){
        flag = 1;
    }
    
    ans = 0;
    while(pqueue1->head){
        while(node = dequeue(pqueue1)){
            if((node->x-1 >= 0) && tmpgrid[node->y][node->x-1]==1){
                tmpgrid[node->y][node->x-1] = 2;
                enqueue(pqueue2, node->x-1, node->y);
            }
            if((node->x+1 < gridColSize[0]) && tmpgrid[node->y][node->x+1]==1){
                tmpgrid[node->y][node->x+1] = 2;
                enqueue(pqueue2, node->x+1, node->y);
            }
            if((node->y-1 >= 0) && tmpgrid[node->y-1][node->x]==1){
                tmpgrid[node->y-1][node->x] = 2;
                enqueue(pqueue2, node->x, node->y-1);
            }
            if((node->y+1 < gridSize) && tmpgrid[node->y+1][node->x]==1){
                tmpgrid[node->y+1][node->x] = 2;
                enqueue(pqueue2, node->x, node->y+1);
            }
            free(node);
        }
        init_queue(pqueue1);
        ptmpqueue = pqueue1;
        pqueue1 = pqueue2;
        pqueue2 = ptmpqueue;
        
        ans++;
    }
    
    deinit_queue(&queue1);
    deinit_queue(&queue2);
    
    for(i=0; i<gridSize; i++){
        for(j=0; j<gridColSize[0]; j++){
            if(tmpgrid[i][j] == 1){
                return -1;
            }
        }
    }
    
    return flag ? ans-1 : ans;
}
