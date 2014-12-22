/** Copyright(C)  1998-2014,Tencent Co. Ltd.
* File name:    tcpsvr.cpp
* @author:      jiwubu
* @version:     V1.0   2014/09/14
* Description: 	socket������
* Log:
*/

#include "connsvr.h"
#include "process.h"

static void process_accept(event_base *base, int fd, void *privdata);

//������ջ�����
char* resize_rbuf(struct conn* c, int len)
{
    if( c->rtotal - c->rlen >= len )
    {
        return c->rbuf + c->rlen;
    }

    while( c->rtotal - c->rlen < len )
    {
        c->rtotal *= 2;
    }

    char* p = (char*)malloc(c->rtotal);

    memmove(p, c->rbuf, c->rlen);
    free(c->rbuf);
    c->rbuf = p;

    return c->rbuf + c->rlen;
}

//�����ͻ�����
char* resize_sbuf(struct conn* c, int len)
{
    if( c->stotal - c->slen >= len )
    {
        return c->sbuf + c->slen;
    }

    if( c->stotal - c->slen + c->spos > len )
    {
        memmove(c->sbuf, c->sbuf + c->spos, c->slen - c->spos);

        c->slen -= c->spos;
        c->spos = 0;

        return c->sbuf + c->slen;
    }

    while( (c->stotal - c->slen) < len )
    {
        c->stotal *= 2;
    }

    char* p = (char*)malloc(c->stotal);

    memmove(p, c->sbuf + c->spos, c->slen - c->spos);
    free(c->sbuf);

    c->sbuf = p;
    c->slen -= c->spos;
    c->spos = 0;

    return c->sbuf + c->slen;
}

//�����µ�����
static struct conn* create_conn(event_base* base, int fd, char* ip, int port)
{
    struct conn* c = (struct conn*)malloc(sizeof(struct conn) );

    if( NULL == c )
    {
        Err("malloc conn error: %s", strerror(errno) );

        exit(-1);
    }

    memset(c, 0x00, sizeof(struct conn) );

    c->rtotal = MAX_BUF_SIZE;
    c->stotal = MAX_BUF_SIZE;

    c->rbuf = (char*)malloc( sizeof(char) * c->rtotal);
    c->sbuf = (char*)malloc( sizeof(char) * c->stotal);

    c->base = base;
    c->fd = fd;
    c->port = port;
    memcpy(c->ip, ip, sizeof(c->ip) );

	//��ʼ��ʱ���¼��Ľṹ��
    c->tevent = (struct time_event*)malloc(sizeof(struct time_event));
    time_event_init(c->tevent, NULL, NULL);

    //��ʼ��file_event
    file_event_init(base, c->fd);

    return c;
}

//��������
void destroy_conn(struct conn* c)
{
    struct event_base* base = c->base;

    base->count--;

    Debug("[%d] %s:%d closed, count=%d", getpid(), c->ip, c->port, base->count);

    if( event_del(base, c->fd, AE_READABLE|AE_WRITABLE) != AE_OK )
    {
        Err("event_del failed: %s", strerror(errno) );

        exit(-1);
    }

    close(c->fd);

    unregister_timer(c->base, c->tevent);

    file_event_init(base, c->fd);

    free(c->rbuf);
    free(c->sbuf);
    free(c->tevent);
    free(c);

    return;
}

void conn_timeout(void* arg)
{
    struct conn* c = (struct conn*)arg;

    Warn("[%s:%d] timeout", c->ip, c->port);

    destroy_conn(c);

    return;
}

//���ݽ����¼�������,Ϊ������ܴ˺���ҲЭ����ȫ��ϣ��Ƚ������ݰ�ͷ���ٽ���BODY
static void process_recv(event_base *base, int fd, void *privdata)
{
    struct conn *c = (conn*)privdata;
    int ret = 0;
    int remain_len;
    int len;

    //��������С��HEAD����ʱ����������HEAD���������BODY
    if ( c->rlen < PKG_HEAD_SIZE )
    {
        ret = anetRead(c->fd, c->rbuf + c->rlen, PKG_HEAD_SIZE - c->rlen);

        if( ret <= 0 )
        {
            goto err;
        }

        c->rlen += ret;

        if( c->rlen < PKG_HEAD_SIZE )
        {
            return;
        }

        //����Э������������ĳ���
        c->plen = *((__u32 *) (c->rbuf + PACKAGE_LEN));
        c->plen = (int) ntohl(c->plen);

        if( *c->rbuf != SOH || c->plen <= PACKAGE_BODY )
        {
            Err("[%s:%d] invalid package", c->ip, c->port);

            goto err;
        }

        if( c->plen >= MAX_PKT_SIZE )
        {
            Err("[%s:%d] package too long, len=%d", c->ip, c->port, c->plen);

            goto err;
        }

        resize_rbuf(c, c->plen - PKG_HEAD_SIZE);
    }

    //Ϊ��ֹ����fd����,�������С��4096,�����������������һ��ֻ����4096���ֽ�
    remain_len = c->plen - c->rlen;
    len = remain_len > 4096 ? 4096 : remain_len;

    ret = anetRead(c->fd, c->rbuf + c->rlen, len);

    if( ret <= 0 )
    {
        goto err;
    }

    c->rlen += ret;

    //Ϊ�ﵽһ�����ĳ���ʱ����������
    if( c->rlen < c->plen )
    {
        return;
    }

    //���ô��������д���
    process_packet(c, c->rbuf, c->rlen);

    //����ע�����ӳ�ʱ��ʱ��
    register_timer(base, c->tevent, MAX_TIMEOUT);

    //������һ�����ݰ��󣬻������ֿ����ظ�ʹ����
    c->rlen = 0;
    c->plen = 0;

    return;

err:
    destroy_conn(c);

    return;
}

static void process_send(event_base *base, int fd, void *privdata)
{
    struct conn *c = (conn*)privdata;

    int nbytes = anetWrite(c->fd, c->sbuf, c->slen);

    if ( nbytes >= 0 )
    {
        c->spos += nbytes;
    }
    else
    {
        Err("[%s:%d] write error: %s", c->ip, c->port, strerror(errno));

        destroy_conn(c);

        return;
    }

    //����ȫ���������
    if( c->spos == c->slen )
    {
        if( event_del(base, c->fd, AE_WRITABLE) != AE_OK)
        {
            Err("event_del failed: %s", strerror(errno) );

            exit(-1);
        }
    }

    c->slen = 0;
    c->spos = 0;

    return;
}

//�ͻ��������¼��ص�����
//Ϊ�˷�ֹͬʱ���������������ӣ����Խ�ϵͳ����/proc/sys/net/core/somaxconn���ô��
static void process_accept(event_base *base, int fd, void *privdata)
{
    int cport, cfd;
    char cip[128];
    char error_[1024];

    //�����µĿͻ���
    cfd = anetTcpAccept(error_, fd, cip, &cport);

    if( cfd == AE_ERR )
    {
        if( errno != EAGAIN && errno != EWOULDBLOCK )
        {
            Err("[%d] anetTcpAccept failed: %s", getpid(), strerror(errno) );

            exit(-1);
        }

        return;
    }

    base->count++;

    //����Ϊ������ģʽ
    if( anetNonBlock(error_, cfd) == AE_ERR )
    {
        Err("anetNonBlock failed: %s", error_);

        exit(-1);
    }

    Debug("[%d] %s:%d connected, count=%d", getpid(), cip, cport, base->count);

    struct conn *c = create_conn(base, cfd, cip, cport);

    //ע�����ӳ�ʱ��ʱ��
    time_event_init(c->tevent, conn_timeout, c);
    register_timer(base, c->tevent, MAX_TIMEOUT);

    //ע�������Ӷ�IO�¼����¼����
    if( event_add(base, cfd, AE_READABLE, process_recv, c) == AE_ERR)
    {
        Err("[%d] %s:%d event_add failed, %s", getpid(), cip, cport, strerror(errno) );

        exit(-1);
    }

    return;
}

//��conn������Ҫ���͵İ�,��ע��д��IO�¼�
void append_pkt(struct conn* c, int len, char* buf)
{
    if( buf )
    {
        memcpy(c->sbuf + c->slen, buf, len);
    }

    c->slen += len;

    if( event_add(c->base, c->fd, AE_WRITABLE, process_send, c) == AE_ERR )
    {
        Err("[%d] %s:%d event_add failed, %s", c->ip, c->port, strerror(errno) );

        exit(-1);
    }

    return;
}

//��ʼ���¼�����������listenfd�Ķ�IO�¼���ӵ��¼������У����ûص�����Ϊprocess_accept
struct event_base* event_base_init(int fd)
{
    struct event_base* base = event_base_new(MAX_CLIENT_COUNT);

    if( NULL == base )
    {
        Err("Can't create file_event loop: %s", strerror(errno) );

        return NULL;
    }

    base->fd = fd;

    if ( event_add(base, fd, AE_READABLE, process_accept, NULL) == AE_ERR )
    {
        Err("Can't create file file_event: %s", strerror(errno) );

        return NULL;
    }

    return base;
}

//��½��ط�����
int create_server(const char* ip, int port)
{
    char error[1024] = {0};

    int fd = anetTcpServer(error, port, ip);

    if( fd < 0 )
    {
        Err("Can't create socket: %s", error );

        return -1;
    }

    Info("start to listen %s:%d", ip, port);

    return fd;
}

