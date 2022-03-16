
int cmp(char *s1, char *s2){
    char concat1[21], concat2[21];
    char *p1, *p2;
    
    snprintf(concat1, sizeof(concat1), "%s%s", s1, s2);
    snprintf(concat2, sizeof(concat2), "%s%s", s2, s1);
    
    p1 = concat1;
    p2 = concat2;
    
    while(*p1 && *p2){
        if(*p1 > *p2){
            return 1;
        }
        else if(*p1 < *p2){
            return 0;
        }
        
        p1++;
        p2++;
    }
    
    return 0;
}

char** mergesort(char **left, int llen, char **right, int rlen){
    char **ret;
    int i, j, k;
    
    ret = (char**)malloc(sizeof(char*) * (llen+rlen));
    
    i = j = k = 0;
    while(i<llen && j<rlen){
        if(cmp(left[i], right[j])){
            ret[k] = strdup(left[i]);
            i++;
        }
        else{
            ret[k] = strdup(right[j]);
            j++;
        }
        k++;
    }
    
    while(i<llen){
        ret[k] = strdup(left[i]);
        i++;
        k++;
    }
    while(j<rlen){
        ret[k] = strdup(right[j]);
        j++;
        k++;
    }
    
    for(i=0; i<llen; i++){
        free(left[i]);
    }
    free(left);
    for(i=0; i<rlen; i++){
        free(right[i]);
    }
    free(right);
    
    return ret;
}

char** merge(char arr[][11], int l, int r){
    int mid;
    char **left, **right;
    
    if(l >= r){
        left = (char**)malloc(sizeof(char*));
        left[0] = strdup(arr[l]);
        return left;    
    }
    
    mid = (l + r)/2;
    
    left = merge(arr, l, mid);
    right = merge(arr, mid+1, r);
    
    return mergesort(left, mid-l+1, right, r-mid);
}

void int_to_str(int num, char *str){
    int tmp[11];
    int len, i;
    char *p = str;
   
    len = 0;
    do{
        tmp[len] = num%10;
        len++;
    }while(num/=10);
    
    for(i=len-1; i>=0; i--){
        *p = tmp[i] + '0';
        p++;
    }
}

char * largestNumber(int* nums, int numsSize){
    char str_nums[100][11] = {0};
    char **sorted;
    int i;
    int anslen = 0;
    char *ans;
    
    for(i=0; i<numsSize; i++){
        int_to_str(nums[i], str_nums[i]);
        anslen += strlen(str_nums[i]);
    }
 
    sorted = merge(str_nums, 0, numsSize-1);
    
    if(sorted[0][0] == '0'){
        ans = (char*)malloc(2);
        ans[0] = '0';
        ans[1] = '\0';
        for(i=0; i<numsSize; i++){
            free(sorted[i]);
        }
        free(sorted);
        return ans;
    }
   
    ans = (char*)malloc(anslen+1);
    memset(ans, 0, anslen+1);
    strcpy(ans, sorted[0]);
    for(i=1; i<numsSize; i++){
        strcat(ans, sorted[i]);
    }
    
    for(i=0; i<numsSize; i++){
        free(sorted[i]);
    }
    free(sorted);
    
    return ans;
}
