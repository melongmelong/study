struct node{
    int key;
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

void add_list(struct node **head, int key, int val){
    struct node *node;
    
    node = (struct node*)malloc(sizeof(struct node));
    node->key = key;
    node->val = val;
    node->next = NULL;
    
    node->next = *head;
    *head = node;
}

struct node* search_list(struct node **head, int key){
    struct node *tmp;
    
    tmp = *head;
    while(tmp){
        if(tmp->key == key){
            return tmp;
        }
        
        tmp = tmp->next;
    }
    
    return NULL;
}

#define BUCKET 1024
unsigned int _hash(int val){
    return ((unsigned int)val)%BUCKET;
}

bool containsNearbyDuplicate(int* nums, int numsSize, int k){
    struct node *head[BUCKET], *node;
    int i;
    unsigned int h;
    bool ans;
    
    for(i=0; i<BUCKET; i++){
        init_list(&head[i]);
    }
    
    ans = false;
    
    for(i=0; i<numsSize; i++){
        h = _hash(nums[i]);
        
        node = search_list(&head[h], nums[i]);
        
        if(node == NULL){
            add_list(&head[h], nums[i], i);
            continue;
        }
        
        if(i-node->val <= k){
            ans = true;
            break;
        }
        
        node->val = i;
    }
    
    for(i=0; i<BUCKET; i++){
        deinit_list(&head[i]);
    }
    
    return ans;
}
