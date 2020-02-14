#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <rpc/rpc.h>
#include "date.h"


#define MAX_LEN 100
long get_response(void);

long get_response()
{
    long choice;

    printf("===========================================\n");
    printf("                   Menu: \n");
    printf("-------------------------------------------\n");
    printf("                1. Date\n");
    printf("                2. Time\n");
    printf("                3. Both\n");
    printf("                4. Quit\n");
    printf("-------------------------------------------\n");
    printf("               Choice (1-4):");
    scanf("%ld",&choice);
    printf("===========================================\n");
    return(choice);
}

main(int argc, char **argv)
{
    CLIENT  *cl;        /* RPC handle */
    char    *server;
    char    **sresult;  /* return value from date_1()      */
    char    s[MAX_LEN];    /* character array to hold output */
    long    response;  /* user response                           */
    long    *lresult;    /* pointer to user response          */

    if (argc != 2) {
        fprintf(stderr, "usage: %s hostname\n", argv[0]);
        exit(1);
    }
    server = argv[1];
    lresult = (&response);
    /*
     * Create the client "handle."
     */
    if ( (cl = clnt_create(server, DATE_PROG, DATE_VERS, "udp")) == NULL) {
        clnt_pcreateerror(server);
        exit(2);
    }
    response = get_response();
    while(response != 4) {
        if ((sresult = date_1(lresult, cl)) == NULL) {
            clnt_perror(cl, server);
            exit(3);
        }
	printf("  %s\n", *sresult);
	response = get_response();
    }
    clnt_destroy(cl);		/* done with the handle */
    exit(0);
}


