int hammingDistance(int x, int y){
    int xor;
    int i;
    int ans;
    
    xor = x ^ y;
    ans = 0;
    for(i=0; i<=31; i++){
        if(xor & 0x00000001){
            ans++;
        }
        
        xor = xor>>1;
    }
    
    return ans;
}
