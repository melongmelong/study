
int chk(char *start, char *end){
    while(start < end){
        if(*start != *end){
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}

char * longestPalindrome(char * s){
    int i=0, j=0, len=0;
    char *p=NULL, *ans=NULL;
    
    len = strlen(s);
    for(i=len-1; i>=0; i--){
        for(j=0; j+i<=len-1; j++){
            if(chk(&s[j], &s[j+i])){
                ans = (char*)malloc(sizeof(char)*(i+1+1));
                memcpy(ans, &s[j], i+1);
                ans[i+1] = '\0';
                return ans;
            }
        }
    }
    return NULL;
}
