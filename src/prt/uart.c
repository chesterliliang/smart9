#include <stdio.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */
#include <errno.h>   /* ERROR Number Definitions           */
#include "uart.h"
#include "net.h"
#include "var.h"
#include "dbg.h"


int g_dev = 0;
int g_ble_uart_dev = 0;
unsigned char g_ble_data[1024 * 20];

int ble_uart_init(void)
{
    int fd;
    //fd = open ("/dev/ttyS4", O_RDWR | O_NOCTTY | O_NONBLOCK);
    fd = open ("/dev/ttyS4", O_RDWR | O_NOCTTY );
    if (fd < 0) {
        printf ("\n Open Ble Uart Error \n");
        return 1;
    }
    /*RX init*/
    struct termios SerialPortSettings; /* Create the structure                          */
    tcgetattr (fd, &SerialPortSettings); /* Get the current attributes of the Serial port */
    /* Setting the Baud rate */
    cfsetispeed (&SerialPortSettings, B115200);                     
    cfsetospeed (&SerialPortSettings, B115200); 
    /* 8N1 Mode */
    SerialPortSettings.c_cflag &= ~PARENB; /* Disables the Parity Enable bit(PARENB),So No Parity   */
    SerialPortSettings.c_cflag &= ~CSTOPB; /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
    SerialPortSettings.c_cflag &= ~CSIZE;  /* Clears the mask for setting the data size             */
    SerialPortSettings.c_cflag |= CS8;     /* Set the data bits = 8                                 */

    SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
    //SerialPortSettings.c_cflag |= CRTSCTS;       /* Hardware flow Control                         */

    SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */

    SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);         /* Disable XON/XOFF flow control both i/p and o/p */
    SerialPortSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); /* Non Cannonical mode                            */

    SerialPortSettings.c_oflag &= ~OPOST; /*No Output Processing   raw  format  output*/

    SerialPortSettings.c_iflag &= ~ICRNL;

    /* Setting Time outs */
    SerialPortSettings.c_cc[VMIN] = 1;  /* Read at least 10 characters */
    SerialPortSettings.c_cc[VTIME] = 0; /* Wait indefinetly   */

    if ((tcsetattr (fd, TCSANOW, &SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
    {
        printf ("\n  ERROR ! in Setting attributes");
        return 1;
    }
        
    tcflush (fd, TCIFLUSH); /* Discards old data in the rx buffer            */
    g_ble_uart_dev = fd;
    return 0;


}

int uart_init (int *dev){
    int fd;
    int flag;
    //fd = open ("/dev/ttyS1", O_RDWR | O_NOCTTY | O_NONBLOCK);
    fd = open ("/dev/ttyS1", O_RDWR | O_NOCTTY);
    if (fd < 0) {
        printf ("\n Open Error \n");
        return 0;
    }


    flag = fcntl(fd, F_GETFL, 0);
    printf("flag befor:%08X\n", flag);
    if (fcntl(fd, F_SETFL, 0) < 0)
    {
        printf("fcntl failed!\n");
    }
    flag = fcntl(fd, F_GETFL, 0);
    printf("flag after:%08X\n", flag);
   
    // if (isatty(STDIN_FILENO) == 0)
    // {
    //     printf("standard input is not a terminal device\n");
    // }
    /*RX init*/
    struct termios SerialPortSettings; /* Create the structure                          */
    bzero(&SerialPortSettings, sizeof(SerialPortSettings));
    tcgetattr (fd, &SerialPortSettings); /* Get the current attributes of the Serial port */
    /* Setting the Baud rate */
    cfsetispeed (&SerialPortSettings, B115200);                     
    /* 8N1 Mode */
    SerialPortSettings.c_cflag &= ~PARENB; /* Disables the Parity Enable bit(PARENB),So No Parity   */
    SerialPortSettings.c_cflag &= ~CSTOPB; /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
    SerialPortSettings.c_cflag &= ~CSIZE;  /* Clears the mask for setting the data size             */
    SerialPortSettings.c_cflag |= CS8;     /* Set the data bits = 8                                 */

    //SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
    SerialPortSettings.c_cflag |= CRTSCTS;       /* No Hardware flow Control                         */

    SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */

    //SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);         /* Disable XON/XOFF flow control both i/p and o/p */
    //SerialPortSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); /* Non Cannonical mode                            */

    //SerialPortSettings.c_oflag &= ~OPOST; /*No Output Processing   raw  format  output*/

    //SerialPortSettings.c_iflag &= ~ICRNL;

    /* Setting Time outs */
    SerialPortSettings.c_cc[VMIN] = 0;  /* Read at least 10 characters */
    SerialPortSettings.c_cc[VTIME] = 0; /* Wait indefinetly   */

    if ((tcsetattr (fd, TCSANOW, &SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
        printf ("\n  ERROR ! in Setting attributes");
    tcflush (fd, TCIFLUSH); /* Discards old data in the rx buffer            */
    *dev = fd;
    return 1;
}

int ble_write(unsigned char *data, int len)
{
    int rv = 0;
    int i;
    printf("write len %d, data is:%s\n", len, data);


    rv = write (g_ble_uart_dev, data, len);
    printf("write ret = %d\n", rv);
    return rv;

}

int uart_write (unsigned char *data, int len)
{
    int rv = 0;
    int i = 0;
    unsigned char leave = 0;
    unsigned char time = 0;
    if (g_dev == 0 || g_dev < 0){
        rv = uart_init (&g_dev);
        if (rv == 0){
            return 0;
        }
    }

    // time = len / 512;
    // leave = len % 512; 

    // for(i = 0; i < time; i++)
    // {
    //     rv = write (g_dev, &data[i * 512], 512);
    //         usleep(200000);
    // }

    // rv = write (g_dev, &data[time * 512], leave);
    rv = write (g_dev, data, len);
    return rv;
}

int ble_at_read(unsigned char* data, int *len)
{
    int rv = 0;
    int i = 0;
    rv = ble_read(data, 3);
    printf("rec %d %d %d\n", data[0], data[1], data[2]);
    while(1)
    {
        rv = ble_read(&data[3 + i], 1);
        printf(" i  = %d, for read : %d\n", i, data[3 + i]);
        if(data[3 + i] == '\r')
        {
            rv = ble_read(&data[3 + i + 1], 1);
            if(data[3 + i + 1] == '\n')
                break;
        }
        else
        {
            i++;
        }
        
    }
    *len = i + 5;
}

int ble_read(unsigned char *data, int len)
{
    int rv = 0;
    rv = read (g_ble_uart_dev, data, len);
    if (rv < 0)
        return rv;
    return rv;  
}

int uart_read (unsigned char *data, int len){
    int rv = 0;

    int len_get = 0;
    int counter = 0;
    if (g_dev == 0 || g_dev < 0){
        rv = uart_init (&g_dev);
        if (rv == 0){
            printf ("---------init- fail-g_dev=%d------\n", g_dev);
            return 0;
        }
    }
    rv = read (g_dev, data, len);
    if (rv < 0)
        return rv;
    return rv;
}

int uart_close (){
    close (g_dev);
    return 0;
}

void uart_test(void)
{
    int rv = 0;
    rv = uart_init (&g_dev);
    if (rv == 0){
        printf ("---------init- fail-g_dev=%d------\n", g_dev);
    }
    while(1)
    {

        usleep(1000);
    }

}

void *ble_read_thread(void *arg)
{
    int bp, bp1;
    unsigned char tmp_data = 0;
    int i = 0;
    pthread_t p_test;

    printf("ble read pthread creat success!\n");
    while(1)
    {
        ble_read(&tmp_data, 1);
        if(tmp_data== 0x1b)
        {
            g_ble_data[i] = tmp_data;
            i++;
            ble_read(&tmp_data, 1);
            if(tmp_data = 0x40)
            {
                g_ble_data[i] = tmp_data;
                i++;
                while(1)
                {
                    ble_read(&g_ble_data[i], 1);
                    i++;
                    if(g_ble_data[i - 1] == 0x69 && g_ble_data[i - 2] == 0x1b)
                    {
                        break;                        
                    }
                }
                printf("data len = %d, data is:\n", i);
                print_array(g_ble_data, i);

                // bp = easy_serial_open("/dev/ttyS1", "115200");
                // printf("\nhandle = %08x\n", bp);
                // printf("1111socket handle = %08x\n", m_mqtt.active_connections->sock);
                // bp1 = 1;
                // printf("bp = %d\n", bp1);
                // if (esc2bmp_init(&prt_handle, bp1)) {
                //     printf("Initial failed!!!\n");
                //     exit(1);
                // }
                // printf("init success!\n");
                
                
                
                memcpy(pn_data.data, g_ble_data, i - 2);
                pn_data.len = i - 2;
                //uart_write (g_ble_data, i);
                //system("rm ./escode/100000000018330045_100000000018330045_0017.bmp");
                system("rm ./escode/code.bin");
                dump_data("./escode/code.bin", g_ble_data, i);
                //prt_handle.esc_2_lib(g_ble_data, i);
                system("rm ./escode/upload.zip");
                system("zip -r ./escode/upload.zip ./escode/*");
                i = 0;
                g_upload_flag = 1;
                printf("end\n");
            }

        }   
        usleep(1000);     
    }



}

