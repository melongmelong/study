struct node{
    int len;
    int tbl[26];
};

int chk(int *tbl1, int *tbl2){
    int i;
    for(i=0; i<26; i++) {
        if(tbl1[i] && tbl2[i]){
            return 1;
        }
    }
    return 0;
}

int maxProduct(char ** words, int wordsSize){
    struct node node[1000];
    int i,j,ans=0;
    char *p;
    for(i=0; i<wordsSize; i++){
        memset(&node[i], 0, sizeof(struct node));
        p = words[i];
        while(*p){
            node[i].len++;
            node[i] .tbl[*p-'a']++;
            p++;
        }
    }
    for(i=0; i<wordsSize; i++){
        for(j=i+1; j<wordsSize; j++){
            if(node[i].len*node[j].len > ans){
                if(!chk(node[i].tbl, node[j].tbl)){
                    ans = node[i].len*node[j].len;
                }
            }
        }
    }
    return ans;
}
