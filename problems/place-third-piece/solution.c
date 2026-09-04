#include <stddef.h>
#include <math.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

bool IfOutBorder(int x,int y)
{
    if(x>18||x<0)
        return false;
    if(y>18||y<0)
        return false;
    return true;
}

int* placeThirdPiece(int* point1, int point1Size,
                     int* point2, int point2Size,
                     int* returnSize) {
    int dx = point1[0] - point2[0];
    int dy = point1[1] - point2[1];
    if (returnSize != NULL) {
        *returnSize = 2;
    }
    int* res = malloc(2*sizeof(int));
    res[0] = -1;
    res[1] = -1;
    if(abs(dx) > 2 || abs(dy) > 2 ||!(abs(dx)==0 || abs(dy) == 0||(abs(dx)==1&&abs(dy)==1)||(abs(dx) == 2&&abs(dy)==2))) {
        return res;
    }
    int selPoint1[2] = {0};
    int selPoint2[2] = {0};
    selPoint1[0] = point1[0] + dx;
    selPoint1[1] = point1[1] + dy;

    selPoint2[0] = point2[0] - dx;
    selPoint2[1] = point2[1] - dy;

    if(abs(dx)>1||abs(dy)>1)
    {
        res[0] = (point1[0]+point2[0])/2;
        res[1] = (point1[1]+point2[1])/2;
        return res;
    }
    
    bool outflag1 = IfOutBorder(selPoint1[0],selPoint1[1]);
    bool outflag2 = IfOutBorder(selPoint2[0],selPoint2[1]);

    if(outflag1 ==true && outflag2 == true)
    {
        if(selPoint1[0] < selPoint2[0]) {
            res[0] = selPoint1[0];
            res[1] = selPoint1[1];
        } else if(selPoint1[0] > selPoint2[0]) {
            res[0] = selPoint2[0];
            res[1] = selPoint2[1];
        } else if (selPoint1[1] < selPoint2[1]) {
            res[0] = selPoint1[0];
            res[1] = selPoint1[1];
        } else if(selPoint1[1] > selPoint2[1]) {
            res[0] = selPoint2[0];
            res[1] = selPoint2[1];
        }
        else {
            res[0] = selPoint1[0];
            res[1] = selPoint1[1];
        }
        return res;
    }
    else if(outflag1 == true) {
        res[0] = selPoint1[0];
        res[1] = selPoint1[1];
    }
    else if(outflag2 == true) {
        res[0] = selPoint2[0];
        res[1] = selPoint2[1];
    }

    


    return res;
}
