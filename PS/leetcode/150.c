struct node{
    struct node *next;
    int val;
};

void init_stk(struct node **stk){
    *stk = NULL;
}

void deinit_stk(struct node **stk){
    struct node *tmp = *stk, *del;
    while(tmp){
        del = tmp;
        tmp = tmp->next;
        free(del);
   }
}

void push(struct node **stk, int val){
    struct node *node = (struct node*)malloc(sizeof(struct node));
    node->val = val;
    node->next = NULL;
    if(*stk == NULL){
        *stk = node;
        return;
    }
    node->next = *stk;
    *stk = node;
}

struct node* pop(struct node **stk){
    struct node *node = *stk;
    if(node == NULL){
        return NULL;
    }
    *stk = node->next;
    return node;
}

int evalRPN(char ** tokens, int tokensSize){
    int i, ans, val1, val2;
    struct node *stk, *tmp;
    init_stk(&stk);
    for(i=0; i<tokensSize; i++){
        if(tokens[i][0]=='+' || (tokens[i][0]=='-' && tokens[i][1]=='\0') || tokens[i][0]=='*' || tokens[i][0]=='/'){
            tmp = pop(&stk);
            val1 = tmp->val;
            free(tmp);
            tmp = pop(&stk);
            val2 = tmp->val;
            free(tmp);
            switch(tokens[i][0]){
                case '+':
                    push(&stk, val1+val2);
                    break;
                case '-':
                    push(&stk, val2-val1);
                    break;
                case '*':
                    push(&stk, val1*val2);
                    break;
                case '/':
                    push(&stk, val2/val1);
                    break;
            }
        }
        else{
            push(&stk, atoi(tokens[i]));
        }
    }
    tmp = pop(&stk);
    ans = tmp->val;
    free(tmp);
    deinit_stk(&stk);
    return ans;
}
