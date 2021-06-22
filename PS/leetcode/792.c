struct node{
    int idx;
    struct node *next;
};

struct list{
    struct node *head, *tail;
};

void init_list(struct list *list){
    list->head=list->tail=NULL;
}

void deinit_list(struct list *list){
    struct node *del, *tmp;
    tmp=list->head;
    while(tmp){
        del=tmp;
        tmp=tmp->next;
        free(del);
    }
}

void add_list(struct list *list, int idx){
    struct node *node=(struct node*)malloc(sizeof(struct node));
    node->idx=idx;
    node->next=NULL;
    if(list->head==NULL){
        list->head=list->tail=node;
        return;
    }
    list->tail->next=node;
    list->tail=node;
}

int numMatchingSubseq(char * s, char ** words, int wordsSize){
    struct list list[27];
    struct node *tmp;
    int i=0,j,prev,flag,flag2,ans=0;
    for(i=0; i<27; i++){
        init_list(&list[i]);
    }
    i=0;
    while(s[i]){
        add_list(&list[s[i]-'a'], i);
        i++;
    }
    for(i=0; i<wordsSize; i++){
        flag=1;
        prev=-1;
        j=0;
        while(words[i][j]){
            tmp=list[words[i][j]-'a'].head;
            flag2=0;
            while(tmp){
                if(tmp->idx > prev){
                    prev = tmp->idx;
                    flag2=1;
                    break;
                }
                tmp = tmp->next;
            }
            if(!flag2){
                flag=0;
                break;
            }
            j++;
        }
        if(flag){
            ans++;
        }
    }
    for(i=0; i<27; i++){
        deinit_list(&list[i]);
    }
    return ans;
}
