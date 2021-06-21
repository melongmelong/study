/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes){
    int tmp[30], i, j, cnt, **ans=(int**)malloc(sizeof(int*)*numRows);
    *returnColumnSizes = (int*)malloc(sizeof(int)*numRows);
    *returnSize = numRows;
    if(numRows == 1){
        ans[0] = (int*)malloc(sizeof(int)*1);
        ans[0][0] = 1;
        (*returnColumnSizes)[0] = 1;
    }
    else if(numRows == 2){        
        ans[0] = (int*)malloc(sizeof(int)*1);
        ans[0][0] = 1;
        (*returnColumnSizes)[0] = 1;
        ans[1] = (int*)malloc(sizeof(int)*2);
        ans[1][0] = 1;
        ans[1][1] = 1;
        (*returnColumnSizes)[1] = 2;
    }
    else{
        ans[0] = (int*)malloc(sizeof(int)*1);
        ans[0][0] = 1;
        (*returnColumnSizes)[0] = 1;
        ans[1] = (int*)malloc(sizeof(int)*2);
        ans[1][0] = 1;
        ans[1][1] = 1;
        (*returnColumnSizes)[1] = 2;
        for(i=2;i<numRows;i++){
            ans[i] = (int*)malloc(sizeof(int)*(i+1));
            (*returnColumnSizes)[i] = i+1;
            ans[i][0] = 1;
            for(j=0, cnt=1; j<i-1; j++, cnt++){
                ans[i][cnt] = ans[i-1][j] + ans[i-1][j+1];
            }
            ans[i][i] = 1;
        }
    }
    return ans;
}
