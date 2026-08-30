#include <stdlib.h>

typedef struct {
    int price;
    int paidCashes[5];
} Payment;

int *cashierCheckout(const int initCashes[4], const Payment payments[],
                     int paymentsSize, int *returnSize)
{
    int* res = malloc(5*sizeof(int));
    *returnSize = 5;
    memset(res,0,5*sizeof(int));
    int units[5] = {1,5,10,50,100};
    res[0] = initCashes[0];
    res[1] = initCashes[1];
    res[2] = initCashes[2];
    res[3] = initCashes[3];
    for(int i = 0;i<paymentsSize;++i) {
        int sum = 0;
        for(int j = 0;j<5;++j) {
            sum+=payments[i].paidCashes[j]*units[j];
        }
        if(payments[i].price > sum)
            continue;
        const int* paidCashes = payments[i].paidCashes;
        int temp[5] = {res[0]+paidCashes[0],res[1]+paidCashes[1],res[2]+paidCashes[2],res[3]+paidCashes[3],res[4]+paidCashes[4]};
        int change  = sum-payments[i].price;
        for(int k = 4;k>=0;--k) {
            int num = change/units[k];
            if(num>temp[k])
                num = temp[k];
            temp[k]-=num;
            change-=num*units[k];
        }
        if(change == 0) {
            res[0] = temp[0];
            res[1] = temp[1];
            res[2] = temp[2];
            res[3] = temp[3];
            res[4] = temp[4];
        }
        
    }
    return res;
}
