bool judgeCircle(char * moves){
    int x,y;
    char *m;
    
    x = y = 0;
    m = moves;
    while(*m){
        switch(*m){
            case 'U':
                y--;
                break;
            case 'D':
                y++;
                break;
            case 'R':
                x++;
                break;
            case 'L':
                x--;
                break;
        }
        m++;
    }
    
    if(x==0 && y==0){
        return true;
    }
    
    return false;
}
