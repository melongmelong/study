#define BUCKET 1024

struct node{
    int num;
    int cnt;
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

struct node* add_list(struct node **head, int val){
    struct node *node;
    
    node = (struct node*)malloc(sizeof(struct node));
    node->num = val;
    node->cnt = 1;
    node->next = NULL;
    
    if(*head == NULL){
        *head = node;
        return node;
    }
    
    node->next = *head;
    *head = node;
    
    return node;
}

struct node* search_list(struct node **head, int val){
    struct node *tmp;
    
    tmp = *head;
    while(tmp){
        if(tmp->num == val){
            return tmp;
        }
        tmp = tmp->next;
    }
    
    return NULL;
}

int hash(int val){
    return val>=0 ? val%1024 : (-1*val)%1024;
}

struct node** merge(struct node **left, int left_len, struct node **right, int right_len){
    int i, j, k;
    struct node **ret;
    
    i = j = k = 0;
    
    ret = (struct node**)malloc(sizeof(struct node*)*(left_len+right_len));
    
    while(i<left_len && j<right_len){
        if(left[i]->cnt > right[j]->cnt){
            ret[k] = left[i];
            i++;
        }
        else{
            ret[k] = right[j];
            j++;
        }
        k++;
    }
    
    while(i<left_len){
        ret[k] = left[i];
        k++;
        i++;
    }
    while(j<right_len){
        ret[k] = right[j];
        k++;
        j++;
    }
    
    free(left);
    free(right);
    
    return ret;
}

struct node** mergesort(struct node **arr, int start, int end){
    struct node **left, **right;
    int mid;
    
    if(start >= end){
        left = (struct node**)malloc(sizeof(struct node*));
        left[0] = arr[start];
        return left;
    }
    
    mid = (start+end)/2;
    
    left = mergesort(arr, start, mid);
    right = mergesort(arr, mid+1, end);
    
    return merge(left, mid-start+1, right, end-(mid+1)+1);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
    struct node *head[BUCKET], *node, *arr[100000], **sorted_arr;
    int i, node_cnt, *ans;
    
    ans = (int*)malloc(sizeof(int)*k);
    *returnSize = k;
    
    for(i=0; i<BUCKET; i++){
        init_list(&head[i]);
    }
   
    node_cnt = 0;
    for(i=0; i<numsSize; i++){
        node = search_list(&head[hash(nums[i])], nums[i]);
        if(node){
            node->cnt++;
        }
        else{
            node = add_list(&head[hash(nums[i])], nums[i]);
            arr[node_cnt] = node;
            node_cnt++;
        }
    }
    
    sorted_arr = mergesort(arr, 0, node_cnt-1);
    for(i=0; i<k; i++) {
        ans[i] = sorted_arr[i]->num;
    }
    free(sorted_arr);
    
    for(i=0; i<BUCKET; i++){
        deinit_list(&head[i]);
    }
    
    return ans;
}
