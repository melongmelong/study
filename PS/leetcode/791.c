char * customSortString(char * S, char * T){
    int tbl_order[26]={0,}, tbl_str[26]={0,}, i, j, cnt;
    char *ans, *p;

    p = S;
    while(*p){
        tbl_order[*p-'a']++;
        p++;
    }
    p = T;
    while(*p){
        tbl_str[*p-'a']++;
        p++;
    }
    
    ans = (char*)malloc(sizeof(char)*(strlen(T)+1));
    memset(ans, 0 , sizeof(char)*(strlen(T)+1));
 
    p = S;
    cnt = 0;
    while(*p){
        if(tbl_order[*p-'a']){
            for(j=0; j<tbl_str[*p-'a']; j++){
                ans[cnt] = *p;
                cnt++;
            }
            tbl_str[*p-'a'] = 0;
        }
        p++;
    }
    for(i=0; i<26; i++){
        for(j=0; j<tbl_str[i]; j++){
            ans[cnt] = i+'a';
            cnt++;
        }
    }
    
    return ans;
}
