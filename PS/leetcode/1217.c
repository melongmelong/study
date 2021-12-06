struct node{
    int val;
    struct node *next;
};

void init_list(struct node **head){
    *head = NULL;
}
void deinit_list(struct node **head){
    struct node *tmp, *del;
    
    tmp = *head;
    while(tmp){
        del = tmp;
        tmp = tmp->next;
        free(del);
    }
}
void add_list(struct node **head, int val){
    struct node *node;
    
    node = (struct node*)malloc(sizeof(struct node));
    node->val = val;
    node->next = NULL;
    
    if(*head == NULL){
        *head = node;
        return;
    }
    
    node->next = *head;
    *head = node;
}
struct node* search_list(struct node **head, int val){
    struct node *node;
    
    node = *head;
    while(node){
        if(node->val == val){
            return node;
        }
        node = node->next;
    }
    return NULL;
}

#define BUCKET 1024

struct hashtbl{
    struct node *head[BUCKET];
};

unsigned int _hash(int val){
    return (unsigned int)val % BUCKET;
}
void init_hashtbl(struct hashtbl *hashtbl){
    int i;
    
    for(i=0; i<BUCKET; i++){
        init_list(&hashtbl->head[i]);
    }
}
void deinit_hashtbl(struct hashtbl *hashtbl){
    int i;
    
    for(i=0; i<BUCKET; i++){
        deinit_list(&hashtbl->head[i]);
    }
}
void add_hashtbl(struct hashtbl *hashtbl, int val){
    add_list(&hashtbl->head[_hash(val)], val);
}
struct node* search_hashtbl(struct hashtbl *hashtbl, int val){
    return search_list(&hashtbl->head[_hash(val)], val);
}

int minCostToMoveChips(int* position, int positionSize){
    struct hashtbl hashtbl;
    struct node *node;
    int i, j, cost;
    int sum;
    int ans=1000;
    
    init_hashtbl(&hashtbl);
    
    for(i=0; i<positionSize; i++){
        if(search_hashtbl(&hashtbl, position[i]) == NULL){
            add_hashtbl(&hashtbl, position[i]);
        }
    }
    
    for(i=0; i<BUCKET; i++){
        node = hashtbl.head[i];
        while(node){
            sum = 0;
            for(j=0; j<positionSize; j++){
                cost = node->val>position[j] ? node->val-position[j] : position[j]-node->val;
                cost = cost%2==0 ? 0 : 1;
                sum += cost;
            }
            if(sum < ans){
                ans = sum;
            }
            node = node->next;
        }
    }
    
    deinit_hashtbl(&hashtbl);
    
    return ans;
}
