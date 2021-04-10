bool isAlienSorted(char ** words, int wordsSize, char * order){
    int tbl_order[27], i, j, flag;
    char *p1,*p2;

    for(i=0; i<26; i++){
        tbl_order[order[i]-'a'] = i;
    }

    i = 0;
    while(i<wordsSize-1){
        flag = 0;           
        p1 = words[i];
        p2 = words[i+1];
        while(*p1 && *p2){
            if(tbl_order[*p1-'a'] < tbl_order[*p2-'a']){
                flag = 1;
                break;
            }
            else if(tbl_order[*p1-'a'] > tbl_order[*p2-'a']){
                flag = 0;
                break;
            }
            p1++;
            p2++;
        }
        if(*p1=='\0' && *p2=='\0'){
            flag = 1;
        }
        else if(*p2 == '\0'){
            flag = 0;
        }
        else if(*p1 == '\0'){
            flag = 1;
        }
        if(flag == 0){
            return false;
        }
        i++;
    }
    
    return true;
}
