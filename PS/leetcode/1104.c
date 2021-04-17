
#define RIGHT 0
#define LEFT 1
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int my_pow(int i){
    int ret=1;
    while(i--){
        ret *= 2;
    }
    return ret;
}
int* pathInZigZagTree(int label, int* returnSize){
    int *ans, tmpans[1000], tmpanscnt=0, level=0, num=1, total=num, cnt=0, idx=0, flag=RIGHT, i, tree[2000000];
    for(i=1; i<label; i++){
        tree[idx] = i;
        if(flag == RIGHT){
            idx++;
            cnt++;
            if(cnt == num){
                flag = LEFT;
                cnt = 0;
                level++;
                num = my_pow(level);
                total += num;
                idx = total -1;
            }
        }
        else{
            idx--;
            cnt++;
            if(cnt == num){
                flag = RIGHT;
                cnt = 0;
                level++;
                num = my_pow(level);
                total += num;
                idx = total - 1 - num + 1;
            }
        }
    }
    tree[idx] = label;
    while(idx){
        tmpans[tmpanscnt++] = tree[idx];
        idx = (idx-1)/2;
    }
    tmpans[tmpanscnt++] = tree[0];
    *returnSize = tmpanscnt;
    ans = (int*)malloc(sizeof(int)*tmpanscnt);
    for(i=tmpanscnt-1; i>=0; i--){
        ans[tmpanscnt-1-i] = tmpans[i];
    }
    return ans;
}
