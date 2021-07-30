#define CHILDCNT 26

struct node{
    int val;
    struct node *node[CHILDCNT];
};

void init(struct node *root){
    memset(root, 0, sizeof(struct node));
}

void deinit(struct node *root){
    int i;
    
    if(root == NULL){
        return;
    }
    
    for(i=0; i<CHILDCNT; i++){
        deinit(root->node[i]);
        free(root->node[i]);
    }
}

void insert(struct node *root, char *key, int val){
    struct node *node;
    char *p;
    
    node = root;
    p = key;
    while(*p){
        if(node->node[*p-'a'] == NULL){
            node->node[*p-'a'] = (struct node*)malloc(sizeof(struct node));
            memset(node->node[*p-'a'], 0, sizeof(struct node));
        }
        node = node->node[*p-'a'];
        p++;
    }
    node->val = val;
}

void __sum(struct node *root, int *ret){
    int i;
    
    if(root == NULL){
        return;
    }
    
    *ret += root->val;
    for(i=0; i<CHILDCNT; i++){
        __sum(root->node[i], ret);
    }
}

int sum(struct node *root, char *prefix){
    struct node *node;
    char *p;
    int ret;
    
    node = root;
    p = prefix;
    while(*p){
        if(node == NULL){
            return 0;
        }
        node = node->node[*p-'a'];
        p++;
    }

    ret = 0;
    __sum(node, &ret);
    
    return ret;
}

typedef struct {
    struct node root;
} MapSum;

/** Initialize your data structure here. */

MapSum* mapSumCreate() {
    MapSum *mapsum;
    
    mapsum = (MapSum*)malloc(sizeof(MapSum));
    
    init(&mapsum->root);
    
    return mapsum;
}

void mapSumInsert(MapSum* obj, char * key, int val) {
    insert(&obj->root, key, val);
}

int mapSumSum(MapSum* obj, char * prefix) {
    return sum(&obj->root, prefix);
}

void mapSumFree(MapSum* obj) {
    deinit(&obj->root);
    free(obj);
}

/**
 * Your MapSum struct will be instantiated and called as such:
 * MapSum* obj = mapSumCreate();
 * mapSumInsert(obj, key, val);
 
 * int param_2 = mapSumSum(obj, prefix);
 
 * mapSumFree(obj);
*/
