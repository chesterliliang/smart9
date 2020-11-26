#include "global.h"
#include "uart.h"
#include "prt.h"
#include <string.h>

//unsigned char test_cmd[] = { 0x1b,0x53, 0x50, 0x72, 0x69, 0x6e, 0x74, 0x65, 0x72, 0x20, 0x54, 0x65, 0x78, 0x74, 0x20, 0x54, 0x65, 0x73, 0x74, 0x0d,0x0a, 0x0d,0x0a,0x0d,0x0a };
unsigned char test_cmd[] = { 0x1b, 0x1b, 0x52, 0x45, 0x43, 0x45, 0x49, 0x56, 0x45, 0x0d, 0x0a, 0x55, 0x49, 0x44, 0x3a, 0x31, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31, 0x38, 0x33, 0x33, 0x30, 0x30, 0x30, 0x32, 0x0d, 0x0a, 0x50, 0x49, 0x44, 0x3a, 0x5b, 0x31, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31, 0x38, 0x33, 0x33, 0x30, 0x30, 0x30, 0x32, 0x5d, 0x0d, 0x0a, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x5f, 0x69, 0x64, 0x78, 0x3a, 0x30, 0x30, 0x30, 0x31, 0x0d, 0x0a, 0x1b, 0x40, 0x1b, 0x70, 0x00, 0x32, 0x7d, 0x1d, 0x21, 0x00, 0x1b, 0x61, 0x01, 0x1b, 0x33, 0x1e, 0x1b, 0x61, 0x01, 0x49, 0x6e, 0x64, 0x6f, 0x63, 0x68, 0x61, 0x74, 0x0a, 0x0a, 0x1b, 0x61, 0x00, 0x44, 0x69, 0x6e, 0x65, 0x20, 0x49, 0x6e, 0x0a, 0x54, 0x61, 0x62, 0x6c, 0x65, 0x20, 0x74, 0x61, 0x62, 0x6c, 0x65, 0x31, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x47, 0x75, 0x65, 0x73, 0x74, 0x20, 0x31, 0x0a, 0x52, 0x65, 0x63, 0x65, 0x69, 0x70, 0x74, 0x20, 0x23, 0x20, 0x3a, 0x20, 0x32, 0x30, 0x30, 0x39, 0x30, 0x30, 0x30, 0x30, 0x30, 0x33, 0x0a, 0x44, 0x61, 0x74, 0x65, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3a, 0x20, 0x32, 0x30, 0x32, 0x30, 0x2d, 0x30, 0x39, 0x2d, 0x30, 0x32, 0x20, 0x31, 0x36, 0x3a, 0x32, 0x34, 0x3a, 0x34, 0x31, 0x0a, 0x53, 0x74, 0x61, 0x66, 0x66, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3a, 0x20, 0x4d, 0x61, 0x6e, 0x61, 0x67, 0x65, 0x72, 0x0a, 0x1d, 0x21, 0x01, 0x1b, 0x61, 0x01, 0x43, 0x4f, 0x50, 0x59, 0x20, 0x52, 0x45, 0x43, 0x45, 0x49, 0x50, 0x54, 0x1d, 0x21, 0x00, 0x0a, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x0a, 0x1b, 0x33, 0x1e, 0x1b, 0x61, 0x00, 0x33, 0x20, 0x78, 0x20, 0x35, 0x30, 0x2c, 0x30, 0x30, 0x30, 0x0a, 0x6b, 0x6f, 0x70, 0x69, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x31, 0x35, 0x30, 0x2c, 0x30, 0x30, 0x30, 0x0a, 0x0a, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x0a, 0x1b, 0x33, 0x1e, 0x53, 0x55, 0x42, 0x54, 0x4f, 0x54, 0x41, 0x4c, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x31, 0x35, 0x30, 0x2e, 0x30, 0x30, 0x30, 0x0a, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20, 0x43, 0x68, 0x61, 0x72, 0x67, 0x65, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x0a, 0x54, 0x41, 0x58, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x31, 0x35, 0x2e, 0x30, 0x30, 0x30, 0x0a, 0x52, 0x6f, 0x75, 0x6e, 0x64, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x0a, 0x1d, 0x21, 0x01, 0x54, 0x4f, 0x54, 0x41, 0x4c, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x31, 0x36, 0x35, 0x2e, 0x30, 0x30, 0x30, 0x0a, 0x1d, 0x21, 0x00, 0x50, 0x61, 0x79, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x28, 0x43, 0x61, 0x73, 0x68, 0x29, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x31, 0x36, 0x35, 0x2e, 0x30, 0x30, 0x30, 0x0a, 0x43, 0x68, 0x61, 0x6e, 0x67, 0x65, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x0a, 0x1b, 0x61, 0x01, 0x1b, 0x61, 0x01, 0x0a, 0x54, 0x68, 0x61, 0x6e, 0x6b, 0x20, 0x79, 0x6f, 0x75, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x79, 0x6f, 0x75, 0x72, 0x20, 0x76, 0x69, 0x73, 0x69, 0x74, 0x0a, 0x0a, 0x1b, 0x61, 0x01, 0x50, 0x6f, 0x77, 0x65, 0x72, 0x65, 0x64, 0x20, 0x62, 0x79, 0x20, 0x77, 0x77, 0x77, 0x2e, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x62, 0x69, 0x6c, 0x6c, 0x2e, 0x69, 0x64, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x1b, 0x69, 0x1b, 0x1b, 0x52, 0x45, 0x43, 0x45, 0x4e, 0x44, 0x0d, 0x0a};
void prt_connect (void)
{
    mprintf (0, "prt_connect \n");
    uart_write (test_cmd, sizeof (test_cmd));
}

void prt_print (unsigned char* data, int len)
{
   printf ("start prt_print! \n");
   uart_write (data, len);
}

int escpos_printer_feed( const int lines)
{


    char buffer[3];
    strncpy(buffer, ESCPOS_CMD_FEED, 2);
    buffer[2] = lines;
    uart_write (buffer, sizeof(buffer));
    return 0;
}

int escpos_printer_cut(const int lines)
{
    char buffer[4];
    strncpy(buffer, ESCPOS_CMD_CUT, 3);
    buffer[3] = lines;
    uart_write (buffer, sizeof(buffer));
    return 0;
}




