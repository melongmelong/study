char *map[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
char gdigits[5];
int len_digits;
char tmpans[1000][1000];
int cnt_tmpans;

void comb(int n, int k, int num, int cur, int idx, char *dst, int dstidx){
    if(idx == 1){
        if(dstidx+1 == len_digits){
            strcpy(tmpans[cnt_tmpans], dst);
            cnt_tmpans++;
        }
        else{
            comb(strlen(map[gdigits[dstidx+1]-'0']), 1, gdigits[dstidx+1]-'0', 0, 0, dst, dstidx+1);
        }
        return;
    }
    if(cur == n){
        return;
    }
    dst[dstidx] = map[num][cur];
    comb(n, k, num, cur+1, idx+1, dst, dstidx);
    comb(n, k, num, cur+1, idx, dst, dstidx);
}

char ** letterCombinations(char * digits, int* returnSize){
    char **ans, dst[5]={0};
    int i;

    if(*digits == '\0'){
        *returnSize = 0;
        return NULL;
    }

    strcpy(gdigits, digits);
    len_digits = strlen(digits);
    cnt_tmpans = 0;
    comb(strlen(map[gdigits[0]-'0']), 1, gdigits[0]-'0', 0, 0, dst, 0);
    *returnSize = cnt_tmpans;
    ans = (char**)malloc(sizeof(char*)*cnt_tmpans);
    for(i=0; i<*returnSize; i++){
        ans[i] = strdup(tmpans[i]);
    }
    return ans;
}
