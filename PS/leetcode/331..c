struct node{
    struct node *next;
    int cnt;
};

void init_stk(struct node **head){
    *head = NULL;
}

void deinit_stk(struct node **head){
    struct node *tmp, *del;
    
    tmp = *head;
    while(tmp){
        del = tmp;
        tmp = tmp->next;
        free(del);
    }
}

void push(struct node **head, int cnt){
    struct node *node;
    
    node = (struct node*)malloc(sizeof(struct node));
    node->next = NULL;
    node->cnt = cnt;
   
    if(*head == NULL){
        *head = node;
        return;
    }
    
    node->next = *head;
    *head = node;
}

struct node* pop(struct node **head){
    struct node *node = *head;
    
    if(*head == NULL){
        return NULL;
    }
    
    *head = node->next;
    
    return node;
}

struct node* peak(struct node **head){
    return *head;
}

bool isValidSerialization(char * preorder){
    struct node *stk, *node, *node2;
    bool ans;
    char *tok;
    
    init_stk(&stk);
   
    tok = strtok(preorder, ",");
    do{
        if(tok[0] == '#'){
            node = peak(&stk);
            if(node){
                node->cnt--;
            }
        }
        else{
            push(&stk, 2);
        }
      
        while(1){
            node = peak(&stk);
            if(node == NULL){
                break;
            }
            if(node->cnt != 0){
                break;
            }
            
            node = pop(&stk);
            free(node);
            
            node = peak(&stk);
            if(node == NULL){
                break;
            }
            
            node->cnt--;
        }
    }while((tok = strtok(NULL, ",")) && peak(&stk));
    
    if(stk == NULL && tok == NULL){
        ans = true;
    }
    else{
        ans = false;
    }
    
    deinit_stk(&stk);
    
    return ans;
}
