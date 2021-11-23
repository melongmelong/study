struct node{
    struct node *next;
    int key;
    int val;
};

#define BUCKET 8192
struct hashtbl{
    struct node *bucket[BUCKET];
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
    node->next = NULL;
    node->key = key;
    node->val = val;
    
    if(*head == NULL){
        *head = node;
        return;
    }
    
    node->next = *head;
    *head = node;
}

struct node* search_list(struct node **head, int key){
    struct node *node;
    
    node = *head;
    while(node){
        if(node->key == key){
            return node;
        }
        node = node->next;
    }
    return NULL;
}

unsigned int _hash(int key){
    return (unsigned int)key % BUCKET;
}

void init_hashtbl(struct hashtbl *hashtbl){
    int i;
    
    for(i=0; i<BUCKET; i++){
        init_list(&hashtbl->bucket[i]);
    }
}

void deinit_hashtbl(struct hashtbl *hashtbl){
    int i;
    
    for(i=0; i<BUCKET; i++){
        deinit_list(&hashtbl->bucket[i]);
    }
}

void add_hashtbl(struct hashtbl *hashtbl, int key, int val){
    add_list(&hashtbl->bucket[_hash(key)], key, val);
}

struct node* search_hashtbl(struct hashtbl *hashtbl, int key){
    return search_list(&hashtbl->bucket[_hash(key)], key);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* majorityElement(int* nums, int numsSize, int* returnSize){
    struct hashtbl hashtbl;
    struct node *node;
    int i;
    int tmpans[50000], tmpanscnt=0;
    int *ans;
    
    init_hashtbl(&hashtbl);
    
    for(i=0; i<numsSize; i++){
        node = search_hashtbl(&hashtbl, nums[i]);
        if(node){
            node->val++;
        }
        else{
            add_hashtbl(&hashtbl, nums[i], 1);
        }
    }
    
    for(i=0; i<BUCKET; i++){
        node = hashtbl.bucket[i];
        while(node){
            if(node->val > numsSize/3){
                tmpans[tmpanscnt] = node->key;
                tmpanscnt++;
            }
            node = node->next;
        }
    }
    
    deinit_hashtbl(&hashtbl);
   
    ans = (int*)malloc(sizeof(int) * tmpanscnt);
    memcpy(ans, tmpans, sizeof(int) * tmpanscnt);
    *returnSize = tmpanscnt;
    
    return ans;
}
