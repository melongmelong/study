

char * reverseWords(char * s){
    char word[10000]={0,};
    int wordidx=0;
    int i;
    char *p;
    char *ans;
    int ansidx=0;
    
    ans = (char*)malloc(strlen(s)+2);
    memset(ans, 0, strlen(s)+2);
    
    p = s+strlen(s)-1;
    while(p >= s){
        if(*p == ' '){
            if(word[0]){
                for(i=wordidx-1; i>=0; i--){
                    ans[ansidx] = word[i];
                    ansidx++;
                }
                ans[ansidx] = ' ';
                ansidx++;
                
                word[0] = '\0';
                wordidx = 0;
            }
        }
        else{
            word[wordidx] = *p;
            wordidx++;
        }
        p--;
    }
    if(word[0]){
        for(i=wordidx-1; i>=0; i--){
            ans[ansidx] = word[i];
            ansidx++;
        }
        ans[ansidx] = ' ';
        ansidx++;

        word[0] = '\0';
        wordidx = 0;
    }
    ans[ansidx-1] = '\0';
    
    return ans;
}
