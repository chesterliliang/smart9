#include "global.h"
#include "powerup.h"
#include "cJSON.h"
//#include "hafs.h"
#include <string.h>
#include "net.h"


int g_usb_fd;
char server_ip[64] = {0};

uint32_t powerup(void)
{
    usleep(100000);
    mprintf(0,"powerup: device init ok \n");
    usleep(100000);
    mprintf(0,"powerup: no ukey connected \n");

    g_net_status = check_net_init();
    var_init();
    return D9_OK;
}

uint32_t var_init(void)
{
    uint32_t ret = 0;
    ret = config_init();

    return D9_OK;
}

uint32_t config_init(void)
{
    int i;
    FILE *h_file = NULL;
    long len = 0;
    char *content = NULL;
    cJSON *json, *json_ip;

    h_file = fopen("./smart9_scheme.json", "rb+");
    fseek(h_file, 0, SEEK_END);
    len = ftell(h_file);
    content = (char*)malloc(len + 1);
    fseek(h_file, 0, SEEK_SET);
    fread(content, 1, len, h_file);
    fclose(h_file);

    printf("addr = %p, str = %s\n", content, content);

    json = cJSON_Parse(content);
    if(!json)
    {
        printf("ERROR before: [%s]\n", cJSON_GetErrorPtr());
    }
    char *str = cJSON_Print(json);

    json_ip = cJSON_GetObjectItem(json, "config");
    json_ip = cJSON_GetObjectItem(json_ip, "network");
    json_ip = cJSON_GetObjectItem(json_ip, "priority");
    //json_ip = cJSON_GetArrayItem(json_ip, 0);

    if(strcmp(json_ip->valuestring, "cellar") == 0)
    {
        // system("route add -net 203.207.198.0 netmask 255.255.255.0 dev usb0");
        // printf("change network to 4G\n");
        // system("ifconfig wlan0 down");
        // system("ifconfig usb0 up");
        // sleep(1);
        // system("echo -e \"AT^NDISDUP=1,1\r\n\" > /dev/ttyUSB0");
        // sleep(1);
        // system("udhcpc -i usb0");
    }
    else
    {
        //tcp_init("9100");
    }
    
    free(content);
    cJSON_free(json);
    cJSON_free(json_ip);
    return D9_OK;
}


#define  PROCBUFSIZ                  1024
#define _PATH_PROC_NET_DEV          "/proc/net/dev"

static char * interface_name_cut(char *buf, char **name)
{
	char *stat;
	/* Skip white space.  Line will include header spaces. */
	while (*buf == ' ')
	buf++;
	*name = buf;
	/* Cut interface name. */
	stat = strrchr (buf, ':');
	*stat++ = '\0';
	return stat;
}

static int check_interface_fromproc(char *interface)
{
  FILE *fp;
  char buf[PROCBUFSIZ];
  struct interface *ifp;
  char *name;

  /* Open /proc/net/dev. */
  fp = fopen (_PATH_PROC_NET_DEV, "r");
  if (fp == NULL)
  {
      printf("open proc file error\n");
      return -1;
   }

  /* Drop header lines. */
  fgets (buf, PROCBUFSIZ, fp);
  fgets (buf, PROCBUFSIZ, fp);

  /* Only allocate interface structure.  Other jobs will be done in if_ioctl.c. */
  while (fgets (buf, PROCBUFSIZ, fp) != NULL)
    {
      interface_name_cut (buf, &name);
      if(strcmp(interface, name) == 0)
          return 1;
    }
  fclose(fp);
  return 0;
}


unsigned char usb_read(int usb_fd, unsigned char *rec_buff)
{
    int count = 1000;
    int fd;
    int nread, i;
    unsigned char tmp[1024] = {0};
    unsigned char tmp_buff[1024] = {0};


        nread = read(usb_fd, tmp_buff, sizeof(tmp_buff));
        printf("first read nread = %d\n", nread);            
        printf("rec %d byte : \n", nread);
        for(i = 0; i < nread; i++)
        {
            printf("%c", tmp_buff[i]);
        }
        printf("\n");
        memcpy(rec_buff, tmp_buff, nread);


        usleep(1 * 1000);

        
    return 0;
}

unsigned char check_celler(void)
{
    int count = 30;    
    int fd;
    int ret;
    int nread, i;
    unsigned char rec_buff[1024];
    unsigned char tmp[1024];


    while(count--)
    {
        printf("check USB0 node...count = %d\n", (30 - count));
        ret = check_interface_fromproc("usb0");
        printf("check_interface_fromproc ret = %d\n", ret);
        if(ret == 1)
            break;
        else
        {
            sleep(1);
        }
    }
    if(count == 0x00)
        return 1;

    fd = open ("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) {
        printf ("\n Open Error \n");
        return 0;
    }

    // ret = write(fd, " AT^CURC\r\n", strlen(" AT^CURC\r\n") + 1);
    // printf("AT^CURC write ret = %d\n", ret);
    // memset(rec_buff, 0x00, sizeof(rec_buff));
    // usleep(100 * 1000);
    // ret = usb_read(fd, rec_buff);
    // if(ret != 0)
    // {
    //     printf("CURC_REC len = %d----->:%s\n", ret, rec_buff);
    // }
    // else
    // {
    //     printf("AT_REC Faild\n");
    // }

    // ret = write(fd, " AT+CPIN?\r\n", strlen(" AT+CPIN?\r\n") + 1);
    // printf("CPINusb write ret = %d\n", ret);
    // memset(rec_buff, 0x00, sizeof(rec_buff));
    // usleep(100 * 1000);
    // ret = usb_read(fd, rec_buff);
    // if(ret != 0)
    // {
    //     printf("CPIN_REC len = %d----->:%s\n", ret, rec_buff);
    // }
    // else
    // {
    //     printf("AT_REC Faild\n");
    // }

    // ret = write(fd, " AT+CPIN?\r\n", strlen(" AT+CPIN?\r\n") + 1);
    // printf("CPINusb write ret = %d\n", ret);
    // memset(rec_buff, 0x00, sizeof(rec_buff));
    // usleep(100 * 1000);
    // ret = usb_read(fd, rec_buff);
    // if(ret != 0)
    // {
    //     printf("CPIN_REC len = %d----->:%s\n", ret, rec_buff);
    // }
    // else
    // {
    //     printf("AT_REC Faild\n");
    // }

    ret = write(fd, " AT^NDISDUP=1,1\r\n", strlen(" AT^NDISDUP=1,1\r\n") + 1);
    printf("usb write ret = %d\n", ret);
    memset(rec_buff, 0x00, sizeof(rec_buff));
    usleep(10 * 1000);
    // ret = usb_read(fd, rec_buff);
    // if(ret == 0)
    // {
    //     printf("NDISDUPAT_REC----->:%s\n", rec_buff);
    // }
    // else
    // {
    //     printf("AT_REC Faild\n");
    // }
    popen("udhcpc -i usb0", "r");

    return 0;    
}

void check_net_thread(void)
{
    unsigned int time_count = 0;
    int ret=NET_FAILD, status = 0, count = 10, latency = 0;
    FILE* fp = NULL;
    char get_way[32] = {0};
    char *set_route_head = "route add -host 203.207.198.134 gw ";
    char set_route[128] = {0};
    const char* ifList[] = {"wlan0", "usb0"};

    while(ret)
    {
        ret = PXAT_NS_Initialize(ifList, 2, "203.207.198.134", TYPE_IP_ADDRESS, 61613, "203.207.198.134", TYPE_IP_ADDRESS, 61613, 6000, 10000);
        printf("while------Initialize return %X\n", ret);
        usleep(1000 * 1000);
    }
    printf("Initialize return %X\n", ret);
    
    while(1) 
    {
        printf("---------count = %d -----------\n", time_count);
        if(time_count == 20)
        {
            time_count = 30;
            printf("g_net_status_flag == %d\n", g_net_status_flag);
            if(g_net_status_flag == 0)
                g_net_status_flag = 2;
        }
        ret = PXAT_NS_GetNetStatus("wlan0", &status, &latency);
        printf("PXAT_NS_GetNetStatus return %X, status is %X, latency is %dms--g_net_status_flag = %d g_net_way = %d g_net_change_flag = %d\n", ret, status, latency, g_net_status_flag, g_net_way, g_net_change_flag);
        if(ret == 0)
        {
            if((status & 0x01) == 0x01)
            {
                if(g_tcp_flag == 0x00)
                    g_tcp_flag = 1;
            }
        }
        if(ret == 0 && status == 0x07 && (latency < 3000))
        {
            if(g_net_way != NET_WAY_WIFI)
            {
                //pthread_mutex_lock(&net_lock);
                g_net_way = NET_WAY_WIFI;
                fp = popen( "netstat -r|grep wlan0|cut -f 10 -d ' '", "r" );
                memset( get_way, 0, sizeof(get_way) );
                while ( NULL != fgets(get_way, sizeof(get_way), fp ))
                {
                    printf("gateway=%s\n",get_way);
                    break;
                }

                count = strlen(get_way);
                get_way[count - 1] = ' ';
                memset(set_route, 0, sizeof(set_route));
                strcat(set_route, set_route_head);
                strcat(set_route, get_way);
                strcat(set_route, "dev wlan0");
                printf("set_route---->:%s\n", set_route);
                fp = popen("route del -host 203.207.198.134", "r" );
                fp = popen(set_route, "r" );
                g_offline_flag = 0;
                //sleep(1);
                //mqtt_free(&m_mqtt);
                sleep(2);
                g_net_change_flag = 1;
                //mqtt_init("203.207.198.134:61613");
            }

        }
        else
        {
            ret = PXAT_NS_GetNetStatus("usb0", &status, &latency);
            printf("usb0PXAT_NS_GetNetStatus return %X, status is %X, latency is %dms\n", ret, status, latency);
            if(ret == 0 && status == 0x07 && (latency < 3000))
            {
                if(g_net_way != NET_WAY_CELL)
                {
                    //pthread_mutex_lock(&net_lock);
                    g_net_way = NET_WAY_CELL;
                    fp = popen( "netstat -r|grep usb0|cut -f 10 -d ' '", "r" );
                    memset( get_way, 0, sizeof(get_way) );
                    while ( NULL != fgets(get_way, sizeof(get_way), fp ))
                    {
                        printf("gateway=%s\n",get_way);
                        break;
                    }

                    count = strlen(get_way);
                    get_way[count - 1] = ' ';
                    memset(set_route, 0, sizeof(set_route));
                    strcat(set_route, set_route_head);
                    strcat(set_route, get_way);
                    strcat(set_route, "dev usb0");
                    printf("set_route---->:%s\n", set_route);
                    fp = popen("route del -host 203.207.198.134", "r" );
                    fp = popen(set_route, "r" );
                    g_offline_flag = 0;
                    //sleep(1);
                    //mqtt_free(&m_mqtt);
                    sleep(2);
                    g_net_change_flag = 1;
                    //mqtt_init("203.207.198.134:61613");
                }
            }    
            else
            {
                g_offline_flag = 1;
                g_net_status_flag = 0;
                g_net_way = NET_WAY_NULL;
            }
                    
        }
        usleep(1000 * 1000);
        if(time_count < 25)
            time_count++;
    }   

}

unsigned char check_net_init(void)
{

    pthread_t p_check_net;
    int celler_ret;

    celler_ret = check_celler();

    pthread_mutex_init(&net_lock, NULL);
    g_offline_flag = 1;
    pthread_create(&p_check_net, NULL, check_net_thread, NULL);
    pthread_detach(p_check_net);
}
