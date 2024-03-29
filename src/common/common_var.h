#ifndef _COMMON_VAR_H_
#define _COMMON_VAR_H_

#include "define.h"
#include <pthread.h>

extern char version[];


extern struct mg_mgr m_tcp;
extern struct mg_mgr m_mqtt;

extern prt_net_data pn_data;

extern unsigned char g_net_status;


extern volatile unsigned char g_init_flag;
extern volatile unsigned char g_timer_flag;
extern volatile unsigned char g_timer_count;
extern volatile unsigned char g_add_count;
extern volatile unsigned char g_offline_flag;
extern volatile unsigned char g_wait_net_flag;
extern volatile unsigned char g_overtime_flag;
extern volatile unsigned char g_net_way;
extern volatile unsigned char g_net_change_flag;
extern volatile unsigned char g_tcp_flag;
extern volatile unsigned char g_net_status_flag;
extern volatile unsigned char g_heart_beat_flag;
extern volatile unsigned char g_op_upload_flag;
extern volatile unsigned char g_op_download_flag;
extern volatile unsigned char g_http_cmd_flag;
extern volatile unsigned char g_heart_http_lock;
extern volatile unsigned char g_offline_prt_flag;
extern volatile unsigned char g_downloading_flag;
extern volatile unsigned char g_download_overtime_flag;
extern volatile unsigned char g_uploading_flag;
extern volatile unsigned char g_upload_overtime_flag;
extern volatile unsigned char g_status_print_flag;
extern volatile unsigned char g_unprint_flag;
extern volatile unsigned char g_reconnect_flag;


extern char g_uuid_buff[64];
extern unsigned char g_download_url[64];
extern char g_prt_sn[64];

extern pthread_mutex_t net_lock;

#endif