
int countTriplets(int* arr, int arrSize){
    int i,j,k,a,b,ans=0;
    for(i=0; i<arrSize; i++){
        a = arr[i];
        for(j=i+1; j<arrSize; j++){
            if(j-1>i){
                a ^= arr[j-1];
            }
            b = arr[j];
            for(k=j; k<arrSize; k++){
                if(k>j){
                    b ^= arr[k];
                }
                if(a == b){
                    ans++;
                }
            }
        }
    }
    return ans;
}
