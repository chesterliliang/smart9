#include "global.h"
#include "net.h"
#include "db.h"
#include "prt.h"
#include "crypto.h"
#include "main.h"

/*
d9main
main service to maintain biz logic of 3308 device
task:
1. check all task status, generate main error code if someone fails.
2. waitng top event like initialize and data exchange and dispatch them to process
3. TBD
*/
const char* server_ip = "121.36.3.243:61613";
int main(int argc, char **argv)
{
    int i = 0;
    if(powerup())
    {
         mprintf(0,"powerup error %d \n");
         return 0;      
    }
    if(selfcheck())
    {
         mprintf(0,"selfcheck error %d \n");
         return 0;      
    }
    if(data_sync())
    {
         mprintf(0,"sync error %d \n");
         return 0;      
    }
    //prt_connect();
    mqtt_init(server_ip);
    //tcp_init("9100");
    while (1)
    {
       // tcp_poll(100);
        mqtt_poll(100);
        i++;
        if(i==10)
          mqtt_publish_sync(MQTT_TOPIC_UPLOAD,"bbb",3);

    }
}