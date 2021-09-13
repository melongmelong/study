
char shift(char ch, int count){
    int i;
    
    for(i=0; i<count; i++){
        ch++;
        if(ch > 'z'){
            ch = 'a';
        }
    }
    
    return ch;
}

char * shiftingLetters(char * s, int* shifts, int shiftsSize){
    int c, i;
    long long n;
    
    n = 0;
    for(i=0; i<shiftsSize; i++){
        n += shifts[i];
    }
    
    for(i=0; i<shiftsSize; i++){
        c = n%26;
        s[i] = shift(s[i], c);
        n -= shifts[i];
    }
    
    return s; 
}
