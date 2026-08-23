int calPoints(char** operations, int operationsSize) {
    int nums[1001]={0};
    int index = 0;
    for(int i=0;i<operationsSize;++i)
    {
        char* val = operations[i];
        switch(*val){
        case '+':
            nums[index] = nums[index - 1] + nums[index - 2];
            index++;
            break;
        case 'D':
            nums[index] = nums[index - 1] * 2;
            index++;
            break;
        case 'C':
            index--;
            break;
        default:
            nums[index] = (int)strtol(val,NULL,10);
            //printf("default nums[%d] = %d\n",index,nums[index]);
            index++;
        }
        // if(index>0)
        //printf("nums[%d] = %d\n",index-1,nums[index]);
    }
    int res = 0;
    for(int i=0;i<index;++i)
    {
        res+=nums[i];
    }
    return res;
}
