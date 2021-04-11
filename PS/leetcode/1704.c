bool halvesAreAlike(char * s){
    int cnt=0, len=strlen(s), half=len/2, i;
    for(i=0; i<len; i++){
        switch(s[i]){
            case 'a':
            case 'A':
            case 'e':
            case 'E':
            case 'i':
            case 'I':
            case 'o':
            case 'O':
            case 'u':
            case 'U':
                if(i < half){
                    cnt++;
                }
                else{
                    cnt--;
                }
                break;
        }
    }
    if(cnt){
        return false;
    }
    return true;
}
