int maxDepth(char * s){
    int ans, cnt;
    int i;
    
    ans = cnt = 0;
    for(i=0; s[i]; i++){
        if(s[i] == '('){
            cnt++;
        }
        else if(s[i] == ')'){
            cnt--;
        }   
        
        if(cnt > ans){
            ans = cnt;
        }
    }
    
    return ans;
}
