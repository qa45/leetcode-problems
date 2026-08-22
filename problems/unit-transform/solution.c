#include <stdlib.h>

static char *UnitTransform(const char *inputStr)
{
    long long value = 0;
    char unit[20];
    sscanf(inputStr,"%lld %s",&value,unit);
    char* units[6]={"year","month","day","hour","minute","second"};
    long long unitSecond[6] = {22ll * 31 * 24 * 60 * 60,
                            31ll * 24 * 60 *60,
                            24ll * 60 * 60,
                            60ll * 60,
                            60ll,
                            1};
    int index = 0;
    for(int i = 0; i < 6;++i)
    {
        if(strcmp(unit,units[i])==0)
        {
            index = i;
            break;
        }
    }
    long long totalsecond = unitSecond[index] * value;
    int pos = 0;
    char * result = malloc(200);
    for(int i = 0; i < 6;++i)
    {
        long long num = totalsecond/unitSecond[i];
        if(num!=0)
        {
            pos+=sprintf(result+pos,"%lld %s ",num,units[i]);
        }
        totalsecond%=unitSecond[i];
    }
    if(pos>0)
    {
        result[pos-1]='\0';
    }
    return result;
}
