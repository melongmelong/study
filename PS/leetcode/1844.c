#define is_odd(num) (num%2 == 1)
#define to_digit(ch) (ch-'0')

char get_shift(char ch, int digit){
    return ch + digit;
}

char * replaceDigits(char * s){
    int i;
    
    for(i=0; s[i]; i++){
        if(!is_odd(i)){
            continue;
        }
        
        s[i] = get_shift(s[i-1], to_digit(s[i]));
    }
    
    return s;
}
