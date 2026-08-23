#include <stdbool.h>

bool lemonadeChange(int* bills, int billsSize) {
    int cash_5 = 0;
    int cash_10 = 0;
    int cash_20 = 0;
    for(int i = 0;i<billsSize;++i)
    {
        switch(bills[i]){
        case 5:
            cash_5++;
            break;
        case 10:
            cash_5--;
            cash_10++;
            break;
        default:
            break;
        }
        if(bills[i]==20)
        {
            if(cash_5>0&&cash_10>0)
            {
                cash_5--;
                cash_10--;
            }
            else
            {
                cash_5-=3;
            }
        }
        if(cash_5<0||cash_10<0)
        {
            //printf("%d\n",i);
            return false;
        }
    }
    return true;
}
