#define SIGN_N -1
#define SIGN_G 0
#define SIGN_L 1

int maxTurbulenceSize(int* arr, int arrSize){
    int sign, len, ans, i, j;
    
    ans = 0;
    
    for(i=0; i<arrSize; i++){
        len = 1;
        sign = SIGN_N;
        
        for(j=i+1; j<arrSize; j++, len++){
            if(sign == SIGN_N){
                if(arr[j-1] > arr[j]){
                    sign = SIGN_G;
                }
                else if(arr[j-1] < arr[j]){
                    sign = SIGN_L;
                }
                else{
                    break;
                }
            }
            else{
                if((arr[j-1] > arr[j]) && (sign == SIGN_L)){
                    sign = SIGN_G;
                }
                else if((arr[j-1] < arr[j]) && (sign == SIGN_G)){
                    sign = SIGN_L;
                }
                else{
                    break;
                }
            }
        }
        
        if(ans < len){
            ans = len;
        }
    }
    
    return ans;
}
