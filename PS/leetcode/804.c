#define BUCKET_NUM 1024

struct node{
    char val[64];
    struct node* next;
};

void init_list(struct node** head){
    *head = NULL;
}

void deinit_list(struct node** head){
    struct node* cur, *del;
    
    cur = *head;
    while(cur){
        del = cur;
        cur = cur->next;
        free(del);
    }
}

void add_list(struct node** head, char *val){
    struct node* newnode;
    
    newnode = (struct node*)malloc(sizeof(struct node));
    strcpy(newnode->val, val);
    newnode->next = NULL;
    
    newnode->next = *head;
    *head = newnode;
    
    return newnode;
}

struct node* search_list(struct node** head, char *val){
    struct node* cur;
    
    cur = *head;
    while(cur){
        if(strcmp(cur->val, val) == 0){
            return cur;
        }
        cur = cur->next;
    }
    
    return NULL;
}

int _hash(char *val){
    char *ch;
    int h;
   
    ch = val;
    h = 0;
    while(*ch){
        h += *ch;
        ch++;
    }
    
    return h % BUCKET_NUM;
}

char tbl[26][8] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

void convert(char *in, char *out){
    char *ch;
    
    ch = in;
    strcpy(out, tbl[*ch-'a']);
    ch++;
    
    while(*ch){
        strcat(out, tbl[*ch-'a']);
        ch++;
    }
}

int uniqueMorseRepresentations(char ** words, int wordsSize){
    struct node* head[BUCKET_NUM];
    char tmp[64];
    int i;
    int ans;
   
    for(i=0; i<BUCKET_NUM; i++){
        init_list(&head[i]);
    }
    
    ans = 0;
   
    for(i=0; i<wordsSize; i++){
        convert(words[i], tmp);
        
        if(search_list(&head[_hash(tmp)], tmp)){
            continue;
        }
        
        add_list(&head[_hash(tmp)], tmp);
        ans++;
    }
    
    for(i=0; i<BUCKET_NUM; i++){
        deinit_list(&head[i]);
    }
    
    return ans;
}
