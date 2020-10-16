

#include "mongoose.h"

extern unsigned char g_upload_flag;

//tcp group provice TCP server for RAW printer
uint32_t tcp_init(const char* port);
void tcp_poll(uint32_t i_time);
void tcp_handler(struct mg_connection *nc, int ev, void *p);

//mqtt provide the channel to server
uint32_t mqtt_init(const char* address);
void mqtt_poll(uint32_t i_time);
void mqtt_handler(struct mg_connection *nc, int ev, void *p);
uint32_t mqtt_publish_sync(uint32_t topic, char* data, uint32_t *len);