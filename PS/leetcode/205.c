bool isIsomorphic(char * s, char * t){
    char tbl[256];
    int i;
    
    memset(tbl, -1, sizeof(tbl));
    
    while(*s){
        if(tbl[*s]==-1){
            for(i=0; i<256; i++){
                if(tbl[i] == *t){
                    return false;
                }
            }
            tbl[*s] = *t;
        }
        else{
            if(tbl[*s] != *t){
                return false;
            }
        }
        s++;
        t++;
    }
    
    return true;
}
