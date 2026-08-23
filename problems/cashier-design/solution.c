#include <stdlib.h>

typedef struct {
    int price;
    int paidCashes[5];
} Payment;

int *cashierCheckout(const int initCashes[4], const Payment payments[],
                     int paymentsSize, int *returnSize)
{
    *returnSize = 5;
    int* res = malloc(5*sizeof(int));
    memset(res,0,5*sizeof(int));
    const int units[5] = {1,5,10,50,100};
    for(int i=0;i<4;++i)
    {
        res[i] = initCashes[i];
    }
    for(int i = 0;i<paymentsSize;++i)
    {
        int available[5]={0};
        int total = payments[i].paidCashes[0]*1+
                    payments[i].paidCashes[1]*5+
                    payments[i].paidCashes[2]*10+
                    payments[i].paidCashes[3]*50+
                    payments[i].paidCashes[4]*100;
        int p = total-payments[i].price;
        if(p<0)
            continue;
        for(int j=4;j>=0;--j)
        {
            available[j] = res[j] + payments[i].paidCashes[j];
            int used = p/units[j];
            if(used>available[j])
                used = available[j];
            available[j]-=used;
            p-=used*units[j];
        }
        if(p>0)
            continue;
        for(int k =0;k<5;++k)
        {
            res[k]=available[k];
        }
    }
    return res;
}
