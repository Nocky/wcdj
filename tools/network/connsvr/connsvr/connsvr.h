#ifndef CONNSVR_H_H
#define CONNSVR_H_H

#include <sys/resource.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "event.h"
#include "anet.h"
#include "Log.h"

#define MAX_CLIENT_COUNT 50000          //ÿ��������ദ��ͻ�����
#define MAX_BUF_SIZE     4096
#define MAX_TIMEOUT      60000          //���ʱʱ��

typedef struct conn
{
    struct event_base* base;
    struct time_event* tevent;      /*��Ӧ��ʱ�¼�*/

    int fd;
    int plen;                       /*������*/

    char* rbuf;                     /*�洢��������*/
    int   rtotal;                   /*����Buffer�ܳ���*/
    int   rlen;                     /*�������ݳ���*/

    char* sbuf;                     /*�洢��������*/
    int   stotal;                   /*����Buffer�ܳ���*/
    int   slen;                     /*�������ݳ���*/
    int   spos;                     /*�ѷ�������λ��*/

    char ip[64];
    int port;
} conn;

void append_pkt(struct conn* c, int len, char* buf=NULL);
char* resize_rbuf(struct conn* c, int len);
char* resize_sbuf(struct conn* c, int len);
struct event_base* event_base_init(int fd);
int create_server(const char* ip, int port);

#endif

