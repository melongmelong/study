char * breakPalindrome(char * palindrome){
    char *p=palindrome;
    int i=0, mid=-1, len=strlen(palindrome);
    
    if(len<=1){
        return "";
    }
    
    if(len%2 == 1){
        mid = strlen(palindrome)/2;
    }
    while(p[i]){
        if(p[i]!='a' && i!=mid){
            p[i] = 'a';
            return palindrome;
        }
        i++;
    }
    p[i-1] = 'b';
    return palindrome;
}
