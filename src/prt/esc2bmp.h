#ifndef __LIB_ESC_TO_BMP_H
#define __LIB_ESC_TO_BMP_H

#ifdef __cplusplus
extern "C" {
#endif
#define JCIAI //JUST CALL IT AFTER INITIALIZATION

typedef enum {
    HPRT_LIB_EVENT_STATUS,
    HPRT_LIB_EVENT_CUT,
    HPRT_LIB_EVENT_DRAWER,
    HPRT_LIB_EVENT_ID_RET,
} hprt_lib_event_t;

extern void lib_event_callback(hprt_lib_event_t e, const void *arg, unsigned int size);


typedef struct esc2bmp_handle{
    char            font_path[64];  //�ֿ�·�� ������ʱ��Ĭ�� "/opt/fonts_gb18030.bin"
    unsigned int    paper_width;    //ֽ�ſ�� Ϊ0 ʱĬ��576 ����640ʱȡ640

    unsigned int    option;         //ͼƬ������� 0-��ʱ������ֵʱ ����ʱ���е�����λ������Ũ���ٶȣ���Ĭ��0
    unsigned int    timeout_ms;     //ͼƬ�����ʱʱ�䣬��λ���룬Ĭ��100ms������0ʱ��Ĭ����100��
    char            bmp_path[64];   //�ֿ�·�� ������Ĭ��Ϊ /tmp/esc2bmp.bmp
    void            (*bmp_callback)(const char *bmp_path); //ͼƬ����ص�
    JCIAI int       (*bmp_print)(const char *bmp_path);//ͼƬ��ӡ ��֧��2ֵͼ�� 1bpp/8bpp, idΪ��ͼƬ������ID�� Ϊ0ʱ����Ч

    JCIAI unsigned char (*get_printer_status)(void);    //���踳ֵ����ʼ�������
    /* 
        ���� ����������������������������������������  �������������������������������� ���� ��������������������������������  ������������������������ ���� ����
        |7 |6                   |5               |4 |3                |2           |1 |0 |
        ���� ����������������������������������������  �������������������������������� ���� ��������������������������������  ������������������������ ���� ����
        |1 |��ӡ��״̬ ����0 �쳣1 |ֽ��  ��ֽ0 ��ֽ1 |1 |��ֽ�� ��ס1 �ɿ�0 |�ϸ� ��-1 ��0 |1 |0 |  
        ���� ����������������������������������������  �������������������������������� ���� ��������������������������������  ������������������������ ���� ���� 
    */
    JCIAI void      (*printer_reboot)(void);    //���踳ֵ����ʼ������� ������ӡ��
    JCIAI void      (*printer_cut)(unsigned char len);       //�е�
    JCIAI void      (*printer_drawer)(unsigned char idx);    //Ǯ����������踳ֵ����ʼ������� idx Ϊ��� 0��1
    JCIAI void      (*push_process_id)(unsigned int idx);    //process id ѹջ

    unsigned int            (*usb_data_cb)(void *buff, unsigned int size);  //usb���ݽ��ջص���buffΪ���ݵ�ַ��sizeΪ���ݳ��ȣ�Ϊnullʱ��Ĭ��ָ��esc_2_lib
    JCIAI unsigned int      (*esc_2_prt)(const void *buff, unsigned int size);//����esc���ݡ����踳ֵ����ʼ�������
    JCIAI unsigned int      (*esc_2_lib)(const void *buff, unsigned int size);    //����������������,���踳ֵ����ʼ�������
}esc2bmp_handle_t;

extern int esc2bmp_init(struct esc2bmp_handle *handle);//handleҪ�����������ͷ�
extern void esc2bmp_version_print(void);
extern void set_bmp_abandon_flag(void);//���� bmp_print ��δ����� ��ӡ�������ݲ���
extern void set_esc_abandon_flag(void);//����esc_2_prt ��δ�������ӡ����esc���ݲ���

#ifdef __cplusplus
}
#endif
#endif