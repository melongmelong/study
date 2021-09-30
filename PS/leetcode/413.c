struct info{
    int idx;
    int len;
    int diff;
};

int numberOfArithmeticSlices(int* nums, int numsSize){
    struct info info1[5000], info2[5000], *pinfo1, *pinfo2, *ptmpinfo;
    int info1_cnt, info2_cnt, *pinfo_cnt1, *pinfo_cnt2, *ptmpinfo_cnt;
    int i, j;
    int ans;
    
    if(numsSize < 3){
        return 0;
    }
    
    ans = 0;
    info1_cnt = info2_cnt = 0;
    pinfo1 = info1;
    pinfo2 = info2;
    pinfo_cnt1 = &info1_cnt;
    pinfo_cnt2 = &info2_cnt;
    for(i=2; i<numsSize; i++) {
        if(nums[i-2]-nums[i-1] == nums[i-1]-nums[i]){
            pinfo1[*pinfo_cnt1].idx = i-2;
            pinfo1[*pinfo_cnt1].len = 3;
            pinfo1[*pinfo_cnt1].diff = nums[i-1]-nums[i];
            (*pinfo_cnt1)++;
            ans++;
        }
    }
    
    while(*pinfo_cnt1){
        for(i=0; i<*pinfo_cnt1; i++){
            if((pinfo1[i].idx+pinfo1[i].len < numsSize) && (nums[pinfo1[i].idx+pinfo1[i].len-1]-nums[pinfo1[i].idx+pinfo1[i].len] == pinfo1[i].diff)){
                pinfo2[*pinfo_cnt2].idx = pinfo1[i].idx;
                pinfo2[*pinfo_cnt2].len = pinfo1[i].len+1;
                pinfo2[*pinfo_cnt2].diff = pinfo1[i].diff;
                (*pinfo_cnt2)++;
                ans++;
            }
        }
        *pinfo_cnt1 = 0;
        
        ptmpinfo = pinfo1;
        pinfo1 = pinfo2;
        pinfo2 = ptmpinfo;
        
        ptmpinfo_cnt = pinfo_cnt1;
        pinfo_cnt1 = pinfo_cnt2;
        pinfo_cnt2 = ptmpinfo_cnt;
    }
    
    return ans;
}
