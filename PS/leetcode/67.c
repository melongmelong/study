

char * addBinary(char * a, char * b){
    int tmp_a[10001]={0,}, tmp_b[10001]={0,}, tmp_ans[10001]={0,};
    char *ans, *p;
    int len_a, len_b, len;
    int c;
    int i;
    
    len_a = strlen(a);
    len_b = strlen(b);
    
    for(i=len_a-1; i>=0; i--){
        tmp_a[10000-(len_a-1-i)] = a[i] - '0';
    }
    for(i=len_b-1; i>=0; i--){
        tmp_b[10000-(len_b-1-i)] = b[i] - '0';
    }
  
    c = 0;
    len = len_a > len_b ? len_a : len_b;
    for(i=len-1; i>=0; i--){
        tmp_ans[10000-(len-1-i)] = tmp_a[10000-(len-1-i)] + tmp_b[10000-(len-1-i)] + c;
        if(tmp_ans[10000-(len-1-i)] >= 2){
            tmp_ans[10000-(len-1-i)] -= 2;
            c = 1;
        }
        else{
            c = 0;
        }
    }
    if(c == 1){
        tmp_ans[10000-len] = 1;
    }
    
    ans = (char*)malloc(sizeof(char) * (len+2));
    memset(ans, 0, sizeof(char) * (len+2));
    p = ans;
    for(i=tmp_ans[10000-len]==1 ? 10000-len : 10000-(len-1); i<=10000; i++){
        *p = tmp_ans[i] + '0';
        p++;
    }
    return ans;
}
