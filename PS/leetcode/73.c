
struct node{
    struct node *next;
    int x,y;
};

struct queue{
    struct node *head, *tail;
};

void init_queue(struct queue *q){
    q->head = q->tail = NULL;
}

void deinit_queue(struct queue *q){
    struct node *tmp, *del;
    
    tmp = q->head;
    while(tmp){
        del = tmp;
        tmp = tmp->next;
        free(del);
    }
}

void enqueue(struct queue *q, int x, int y){
    struct node *node;
    
    node = (struct node*)malloc(sizeof(struct node));
    node->next = NULL;
    node->x = x;
    node->y = y;
    
    if(q->head == NULL){
        q->head = q->tail = node;
        return;
    }
    
    q->tail->next = node;
    q->tail = node;
}

struct node* dequeue(struct queue *q){
    struct node *node;
    
    if(q->head == NULL){
        return NULL;
    }
    
    node = q->head;
    
    q->head = q->head->next;
    if(q->head == NULL){
        q->head = q->tail = NULL;     
    }
    
    return node;
}

void set0(int **matrix, int matrixSize, int matrixColSize, int x, int y){
    int i;
    
    for(i=0; i<matrixSize; i++){
        matrix[i][x] = 0;
    }
    for(i=0; i<matrixColSize; i++){
        matrix[y][i] = 0;
    }
}

void setZeroes(int** matrix, int matrixSize, int* matrixColSize){
    struct queue q;
    struct node *node;
    int i,j;
    
    init_queue(&q);
    
    for(i=0; i<matrixSize; i++){
        for(j=0; j<matrixColSize[0]; j++){
            if(matrix[i][j] == 0){
                enqueue(&q, j, i);
            }
        }
    }
    
    while(node = dequeue(&q)){
        set0(matrix, matrixSize, matrixColSize[0], node->x, node->y);
        free(node);
    }
    
    deinit_queue(&q);
}
