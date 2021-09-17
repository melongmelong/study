int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    int tbl1[1001]={0,}, tbl2[1001]={0,};
    int i, j, dup; 
    int tmpans[1000], tmpanscnt, *ans;
    
    for(i=0; i<nums1Size; i++){
        tbl1[nums1[i]]++;
    }
    for(i=0; i<nums2Size; i++){
        tbl2[nums2[i]]++;
    }
    
    tmpanscnt = 0;
    for(i=0; i<1001; i++){
        if(tbl1[i]==0 || tbl2[i]==0){
            continue;
        }
        
        dup = tbl1[i] > tbl2[i] ? tbl2[i] : tbl1[i];
        for(j=0; j<dup; j++){
            tmpans[tmpanscnt] = i;
            tmpanscnt++;
        }
    }
    *returnSize = tmpanscnt;
    ans = (int*)malloc(sizeof(int)*tmpanscnt);
    memcpy(ans, tmpans, sizeof(int)*tmpanscnt);
    return ans;
}
