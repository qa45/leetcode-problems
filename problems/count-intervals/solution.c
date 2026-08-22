#include <stddef.h>

typedef struct {
    int minLen;
    int maxLen;
} LengthRange;

static int CountIntervals(const int *records,
                          size_t recordsSize,
                          LengthRange lengthRange,
                          int threshold)
{
    int res = 0;
    for(int k=lengthRange.minLen;k<=lengthRange.maxLen;++k)
    {
        int sum = 0;
        for(int right = 0;right<recordsSize;++right)
        {
            sum+=records[right];
            int left = right - k+1;
            if(left<0)
                continue;
            if(sum>=k*threshold)
            {
                res++;
                
            }
            sum-=records[left];
        }
    }
    return res;
}
