#include <stddef.h>

typedef struct {
    int dataType;
    int index;
    int endFlag;
    int len;
    char *data;
} DataFragment;

char* fail(void)
{
    char* res = malloc(3*sizeof(char));
    if(res!=NULL){
        memcpy(res,"NA",3);
    }
    return res;
}

static char *Recombine(
    const DataFragment *dataFragments,
    size_t dataFragmentsSize,
    int dstType)
{
    DataFragment* arr[100000+1] = {NULL};
    int maxindex = 0;
    /* TODO: implement */
    for(int i = 0;i<dataFragmentsSize;++i)
    {
        if(dataFragments[i].dataType == dstType){
            arr[dataFragments[i].index] = &dataFragments[i];
            if(dataFragments[i].index > maxindex){
                maxindex = dataFragments[i].index;
            }
        }
    }
    if(arr[0] == NULL)
        return fail();
    int len = 0;
    for(int i = 0;i<maxindex;++i){
        if(arr[i] == NULL || arr[i]->endFlag == 1)
            return fail();
        len+=arr[i]->len;
    }
    if(arr[maxindex] == NULL||arr[maxindex]->endFlag == 0)
        return fail();
    len+=arr[maxindex]->len;
    char* res = malloc((len+1)*sizeof(char));
    int pos = 0;
    for(int i = 0;i<=maxindex;i++){
        pos += sprintf(res+pos,"%s",arr[i]->data);
    }
    res[pos] = '\0';

    return res;
}
