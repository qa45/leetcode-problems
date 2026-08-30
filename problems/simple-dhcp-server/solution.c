#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define IP_COUNT 256
#define MAX_RECORD_SIZE 2000

typedef struct {
    bool active;
    int lastIP;
    char mac[13];
}Macrecord;


typedef struct {
    int nextNeverUsed;
    bool occupied[IP_COUNT];
    Macrecord records[MAX_RECORD_SIZE];
    int recordCount;
} DHCPServerSys;


static int findMacRecord(const DHCPServerSys *sys,const char *mac)
{
    for(int i = 0;i<sys->recordCount;++i){
        if(strcmp(sys->records[i].mac,mac)==0)
            return i;
    }
    return -1;
}

static int selectIP(DHCPServerSys *sys) 
{
    if(sys->nextNeverUsed < IP_COUNT) {
        int res = sys->nextNeverUsed;
        sys->nextNeverUsed++;
        sys->occupied[res] = true;
        return res;
    }
    for(int i = 0;i<IP_COUNT;++i) {
        if(sys->occupied[i] == false) {
            sys->occupied[i] = true;
            return i;
        }
    }
    return -1;
}

static char* formatIP(int ip)
{
    char* res = malloc(14);
    snprintf(res,14,"192.168.0.%d",ip);
    return res;
}

static char* formatNA(void){
    char* res = malloc(3);
    snprintf(res,3,"NA");
    return res;
}

static DHCPServerSys *DHCPServerSysCreate(void)
{
    DHCPServerSys *sys = malloc(sizeof(DHCPServerSys));
    sys->nextNeverUsed=0;
    for(int i = 0;i<IP_COUNT;++i){
        sys->occupied[i] = false;
    }
    memset(sys->records,0,sizeof(sys->records));
    for(int i = 0;i<MAX_RECORD_SIZE;++i){
        sys->records[i].lastIP = -1;
    }
    sys->recordCount = 0;
    return sys;
}

static char *DHCPServerSysRequest(DHCPServerSys *sys, const char *mac)
{
    /* TODO: implement */
    int ret = findMacRecord(sys,mac);
    if (ret >= 0) {
        if (sys->records[ret].active == true )
            return formatIP(sys->records[ret].lastIP);
        if(sys->occupied[sys->records[ret].lastIP] == false) {
            sys->records[ret].active = true;
            sys->occupied[sys->records[ret].lastIP] = true;
            return formatIP(sys->records[ret].lastIP);
        }
        int ip = selectIP(sys);
        if(ip == -1)
            return formatNA();
        strcpy(sys->records[sys->recordCount].mac,mac);
        sys->records[sys->recordCount].lastIP = ip;
        sys->records[sys->recordCount].active = true;
        sys->recordCount++; 
        return formatIP(ip);
    }
    else {
        int ip = selectIP(sys);
        if(ip == -1)
            return formatNA();
        strcpy(sys->records[sys->recordCount].mac,mac);
        sys->records[sys->recordCount].lastIP = ip;
        sys->records[sys->recordCount].active = true;
        sys->recordCount++; 
        return formatIP(ip);

    }
    return formatNA();
}

static bool DHCPServerSysRelease(DHCPServerSys *sys, const char *mac)
{
    /* TODO: implement */
    for(int i = 0;i<sys->recordCount;++i){
        if(strcmp(sys->records[i].mac,mac) == 0 && sys->records[i].active == true){
            sys->records[i].active = false;
            sys->occupied[sys->records[i].lastIP] = false;
            return true;
        }
    }
    return false;
}

static void DHCPServerSysFree(DHCPServerSys *sys)
{
    free(sys);
}
