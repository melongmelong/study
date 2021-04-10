char *map[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
char tmpans[256][5];
int cnt_tmpans;

void rec(char *digits, int n, int idx, char *dst){
    int i;
    
    if(idx == n){
        strcpy(tmpans[cnt_tmpans], dst);
        cnt_tmpans++;
        return;
    }
    for(i=0; i<strlen(map[digits[idx]-'0']); i++){
        dst[idx] = map[digits[idx]-'0'][i];
        rec(digits, n, idx+1, dst);
    }
}

char ** letterCombinations(char * digits, int* returnSize){
    char dst[5] = {0}, **ans;
    int i;
   
    cnt_tmpans = 0;
    *returnSize = 0;
    if(*digits == '\0'){
        return NULL;
    }
    rec(digits, strlen(digits), 0, dst);
    *returnSize = cnt_tmpans;
    ans = (char**)malloc(sizeof(char*)*cnt_tmpans);
    for(i=0; i<*returnSize; i++){
        ans[i] = strdup(tmpans[i]);
    }
    return ans;
}
