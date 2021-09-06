char slowestKey(int* releaseTimes, int releaseTimesSize, char * keysPressed){
    int i, max;
    char ans;
    
    max = releaseTimes[0];
    ans = keysPressed[0];
    for(i=1; i<releaseTimesSize; i++){
        if(releaseTimes[i] - releaseTimes[i-1] > max){
            max = releaseTimes[i] - releaseTimes[i-1];
            ans = keysPressed[i];
        }
        else if(releaseTimes[i] - releaseTimes[i-1] == max){
            if(ans < keysPressed[i]){
                ans = keysPressed[i];
            }
        }
    }
    
    return ans;
}
