/** Copyright(C)  1998-2014,Tencent Co. Ltd.
* File name:    process.cpp
* @author:      jiwubu
* @version:     V1.0   2014/09/14
* Description: 	�����Э�鴦��
* Log:
*/

#include "process.h"

enum CMD_TYPE
{
    CMD_TEST                      = 0x2900, //����Э��
};

//������ӵ�conn��
void send_client(struct conn* c, struct pbpack* pkt)
{
    PackToStr(pkt);

    append_pkt(c, GetPackLen(pkt) );

    return;
}

int process_test(struct conn* c, struct pbpack* pkt)
{
    const char* rcvbuf = GetDataPos(pkt);
    int size = GetDataSize(pkt);

    //�ӷ��ͻ�������ڴ�
    int length = size + 128;

    //ֱ�ӻ�ȡconn���ͻ����ָ�룬����������ֱ����д��������壬�������ݿ���
    char* sndbuf = resize_sbuf(c, length);

    struct pbpack* rpkt = CreatePack(sndbuf, length);

    SetCmd(rpkt, GetCmd(pkt));
    SetSeq(rpkt, GetSeq(pkt) );

    //�������
    AddAllData(rpkt, rcvbuf, size);

    send_client(c, rpkt);

    Destroy(rpkt);

    return 0;
}

//����ÿ���������͵����ݰ�
int process_packet(struct conn* c, char* buf, int len)
{
    int iret = 0;
    struct pbpack* pkt = StrToPack(buf, len);

    if( NULL == pkt )
    {
        Err("[%s:%d] StrToPack return NULL", c->ip, c->port);

        return -1;
    }

    //��ȡ��������
    unsigned int ulCmd = GetCmd(pkt);

    switch(ulCmd)
    {
        case CMD_TEST:
            iret = process_test(c, pkt);
            break;

        default:
            Err("[%s:%d] unknown protocol [%u]", c->ip, c->port, ulCmd);
            break;
    }

    Destroy(pkt);

    return iret;
}

