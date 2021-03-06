#include "var.h"
#include "mongoose.h"

struct mg_mgr m_tcp;
struct mg_mgr m_mqtt;

prt_net_data pn_data;

unsigned char g_net_status;

volatile unsigned char g_timer_flag = 0;
volatile unsigned char g_timer_count = 0;
volatile unsigned char g_add_count = 0;
volatile unsigned char g_offline_flag = 0;
volatile unsigned char g_wait_net_flag = 0;
volatile unsigned char g_overtime_flag = 0;
volatile unsigned char g_net_way = 0;
volatile unsigned char g_net_change_flag = 0;
volatile unsigned char g_tcp_flag = 0;
volatile unsigned char g_net_status_flag = 0;




pthread_mutex_t net_lock;