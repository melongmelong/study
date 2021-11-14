struct node{
    char *str;
    struct node *next;
};

struct list{
    struct node *head, *tail;
};

void init_list(struct list *list){
    list->head = list->tail = NULL;
}

void deinit_list(struct list *list){
    struct node *tmp, *del;
    
    tmp = list->head;
    while(tmp){
        del = tmp;
        tmp = tmp->next;
        free(del->str);
        free(del);
    }
}

void add_list(struct list *list, char *str){
    struct node *node;
    
    node = (struct node*)malloc(sizeof(struct node));
    node->str = strdup(str);
    node->next = NULL;
    
    if(list->head == NULL){
        list->head = list->tail = node;
        return;
    }
    
    list->tail->next = node;
    list->tail = node;
}

void comb(char *str, int n, int k, char *arr, int curr, int idx, struct list *list){
    if(idx == k){
        arr[idx] = '\0';
        add_list(list, arr);
        return;
    }
    if(curr == n){
        return;
    }
    
    arr[idx] = str[curr];
    comb(str, n, k, arr, curr+1, idx+1, list);
    comb(str, n, k, arr, curr+1, idx, list);
}

typedef struct {
    struct list list;
    struct node *cursor;
} CombinationIterator;


CombinationIterator* combinationIteratorCreate(char * characters, int combinationLength) {
    CombinationIterator *comb_iter;
    char arr[16];
    
    comb_iter = (CombinationIterator*)malloc(sizeof(CombinationIterator));
    
    init_list(&comb_iter->list);
    comb(characters, strlen(characters), combinationLength, arr, 0, 0, &comb_iter->list);
    comb_iter->cursor = comb_iter->list.head;
    
    return comb_iter;
}

char * combinationIteratorNext(CombinationIterator* obj) {
    char *ret = "";
    
    if(obj->cursor){
        ret = obj->cursor->str;
        obj->cursor = obj->cursor->next;
    }
    
    return ret;
}

bool combinationIteratorHasNext(CombinationIterator* obj) {
    if(obj->cursor){
        return true;
    }
    
    return false;
}

void combinationIteratorFree(CombinationIterator* obj) {
    deinit_list(&obj->list);
    free(obj);
}

/**
 * Your CombinationIterator struct will be instantiated and called as such:
 * CombinationIterator* obj = combinationIteratorCreate(characters, combinationLength);
 * char * param_1 = combinationIteratorNext(obj);
 
 * bool param_2 = combinationIteratorHasNext(obj);
 
 * combinationIteratorFree(obj);
*/
