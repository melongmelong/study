struct node{
    struct node *next;
    int val;
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
    node->next = NULL;
    node->val = val;
    
    if(*head == NULL){
        *head = node;
        return;
    }
    
    node->next = *head;
    *head = node;
}

int is_cycle;

void dfs(struct node **head, int *cycle_visit, int *visit, int course){
    struct node *tmp;
    
    if(cycle_visit[course]){
        is_cycle = 1;
        return;
    }
    
    if(visit[course]){
        return;
    }
    
    cycle_visit[course] = 1;
    visit[course] = 1;
    
    tmp = head[course];
    while(tmp){
        dfs(head, cycle_visit, visit, tmp->val);
        
        if(is_cycle == 1){
            return;
        }
        
        tmp = tmp->next;
    }
    
    cycle_visit[course] = 0;
}

int check_all_visit(int *visit, int n){
    int i;
    
    for(i=0; i<n; i++){
        if(visit[i] == 0){
            return 0;
        }
    }
    
    return 1;
}

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize){
    struct node *head[100000];
    int visit[100000]={0,};
    int cycle_visit[100000]={0,};
    int i;
    bool ans;
    
    for(i=0; i<numCourses; i++){
        init_list(&head[i]);
    }
    
    for(i=0; i<prerequisitesSize; i++){
        add_list(&head[prerequisites[i][0]], prerequisites[i][1]);
    }
    
    while(1){
        is_cycle = 0; 
        memset(cycle_visit, 0, sizeof(int)*numCourses);
       
        for(i=0; i<numCourses; i++){
            if(visit[i]==1){
                continue;
            }
            
            dfs(head, cycle_visit, visit, i);
            break;
        }
       
        if(is_cycle == 1){
            ans = false;
            break;
        }
        
        for(i=0; i<numCourses; i++){
            if(cycle_visit[i] == 1){
                visit[i] = 1;
            }
        }
        
        if(check_all_visit(visit, numCourses) == 1){
            ans = true;
            break;
        }
    }
    
    for(i=0; i<numCourses; i++){
        deinit_list(&head[i]);
    }
    
    return ans;
}
