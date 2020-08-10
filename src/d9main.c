#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include "net.h"
#include "db.h"
#include "global.h"
#include "prt.h"

/*
d9main
main service to maintain biz logic of 3308 device
task:
1. check all task status, generate main error code if someone fails.
2. waitng top event like initialize and data exchange and dispatch them to process
3. TBD
*/

int main(int argc, char **argv)
{
    int i = 0;
    openlog("D9SMART", LOG_CONS | LOG_PID, 0);  
    prt_connect();
    while (1)
    {
        printf("smart9 main ctl service :%d \n",i);
         syslog(LOG_DEBUG,  
           "This is a syslog test message generated by d9 '%s'\n",  
           argv[0]);  
        i++;
        sleep(5); //2s
    }
    closelog();
}