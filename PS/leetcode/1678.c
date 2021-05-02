
enum tableidx{
    IDX_G,
    IDX_PARENTHESS,
    IDX_AL,
};

char *table[] = {
    "G",
    "o",
    "al"
};

enum tableidx parse(char *str){
    enum tableidx tableidx;
    switch(*str){
        case 'G':
            tableidx = IDX_G;
            break;
        case '(':
            if(*(str+1) == ')'){
                tableidx = IDX_PARENTHESS;
            }
            else{
                tableidx = IDX_AL;
            }
            break;
    }
    return tableidx;
}

char * interpret(char * command){
    char *ans = (char*)malloc(sizeof(char)*(strlen(command)+1)), *p, *p2=ans;
    int i;
    enum tableidx tableidx;
    memset(ans, 0, sizeof(char)*(strlen(command)+1));
    p = command;
    while(*p){
        tableidx = parse(p);
        switch(tableidx){
            case IDX_G:
                memcpy(p2, table[IDX_G], strlen(table[IDX_G]));
                p2++;
                p++;
                break;
            case IDX_PARENTHESS:
                memcpy(p2, table[IDX_PARENTHESS], strlen(table[IDX_PARENTHESS]));
                p2++;
                p+=2;
                break;
            case IDX_AL:
                memcpy(p2, table[IDX_AL], strlen(table[IDX_AL]));
                p2+=2;
                p+=4;
                break;
        }
    }
    return ans;
}
