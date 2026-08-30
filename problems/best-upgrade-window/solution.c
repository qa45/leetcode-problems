#include <stddef.h>

typedef struct {
   int start;
   int end;
} Window;

static Window GetBestWindow(int cap, const int *visitCnt, size_t visitCntSize)
{
    Window result = {-1, -1};
    int left = 0;
    int right = 0;
    size_t sum = 0;
    int max = 0;
    while (right < 2 * visitCntSize - 1) {
        sum += visitCnt[right % visitCntSize];
        while (sum > cap && left < visitCntSize) {
            sum -= visitCnt[left];
            left ++;
        }
        if (right - left + 1 > max &&  right - left + 1 <= visitCntSize && sum <= cap) {
            max = right - left + 1;
            result.start = left;
            result.end = right % visitCntSize;
        }
        right ++;
        
    }
    
    
    return result;
}
