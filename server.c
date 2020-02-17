#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <rpc/rpc.h>    /* standard RPC include file */
#include <time.h>
#include <sys/types.h>
#include <malloc.h>
#include <sys/sysinfo.h>
#include "date.h"       /* this file is generated by rpcgen */

#define MAX_LEN 100
/*
 *  * Return the binary date and time.
 *   */
char ** date_1(long *option)
{
    //printf("here2\n");
    struct tm *timeptr; /* Pointer to time structure      */
    time_t clock;       /* Clock value (in secs)          */
    static char *ptr;   /* Return string                  */
    static char err[] = "Invalid Response \0";
    static char s[MAX_LEN];
    struct sysinfo mysys;
    static long CPUinfo;
    struct mallinfo myMallInfo;
    int pagesize;
    int physPages;
    int maxNumForProc = 6;
    double loadavg[3];


    clock = time(0);
    timeptr = localtime(&clock);

    switch(*option)
        {
        case 1: strftime(s,MAX_LEN,"%A, %B %d, %Y",timeptr);
                ptr=s;
                break;

        case 2: strftime(s,MAX_LEN,"%T",timeptr);
                ptr=s;
                break;

        case 3: strftime(s,MAX_LEN,"%A, %B %d, %Y - %T",timeptr);
                ptr=s;
                break;
        case 4: sysinfo(&mysys);
                CPUinfo = mysys.loads[0];
                sprintf(s,"CPU usage: %ld\n", CPUinfo);
                ptr = s;
                break;

        case 5: myMallInfo = mallinfo();
                pagesize = getpagesize();
                physPages = get_phys_pages();
                sprintf(s,"Page Size: %d\nPhysical Pages: %d\nTotal free space: %d\nTotal Allocated Spage: %d\n ", pagesize, physPages, myMallInfo.fordblks, myMallInfo.uordblks);
                ptr = s;
                break;

        case 6: getloadavg(loadavg, maxNumForProc);
                sprintf(s,"Load Processes per \n   1 min: %d\n   5 min: %d\n   15 min: %d\n", loadavg[0], loadavg[1], loadavg[2]);
                ptr = s;
                break;

        default: ptr=err;
                 break;
        }
    return(&ptr);
}