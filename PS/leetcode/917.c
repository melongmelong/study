
int is_alpha(char ch){
    if(('a'<=ch && ch<='z') || ('A'<=ch && ch<='Z')){
        return 1;
    }
    
    return 0;
}

int next_idx_start(char *s, int idx){
    idx++;
    while(s[idx]!='\0' && !is_alpha(s[idx])){
        idx++;
    }
    return idx;
}

int next_idx_end(char *s, int idx){
    idx--;
    while(idx>=0 && !is_alpha(s[idx])){
        idx--;
    }
    return idx;
}

char * reverseOnlyLetters(char * s){
    int start, end;
    char ch;
  
    start = next_idx_start(s, -1);
    end = next_idx_end(s, strlen(s));
    
    while(start<end){
        ch = s[start];
        s[start] = s[end];
        s[end] = ch;

        start = next_idx_start(s, start);
        end = next_idx_end(s, end);
    }
    
    return s;
}
