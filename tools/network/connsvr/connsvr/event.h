#ifndef EVENT_H_H__
#define EVENT_H_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/epoll.h>

#include "minheap.h"

#define AE_OK 0
#define AE_ERR -1

#define AE_NONE 0
#define AE_READABLE 1
#define AE_WRITABLE 2

struct event_base;

/* Types and data structures */
typedef void event_proc(struct event_base *base, int fd, void *ptr);

/* File file_event structure */
typedef struct file_event
{
    int mask;            /* one of AE_(READABLE|WRITABLE) */

    event_proc *rproc;   //���¼��ص�����
    event_proc *wproc;   //д�¼��ص�����
    void *arg;
} file_event;

/* State of an file_event based program */
typedef struct event_base
{
    int size;
    int stop;
    int epfd;

    int count;                      /*�ͻ�������*/

    int fd;                         /*������fd*/
    struct epoll_event *eevents;    /*EPOLL�¼�*/
    struct file_event  *fevents;    /*fd�����¼�,ÿ��fd��Ӧһ��*/

    struct min_heap* heap;           /*��ʱ�¼�С����*/
    struct timeval* tv_cache;        /*���浱ǰʱ�䣬��ֹÿ�ε���̫��ϵͳ����*/
} event_base;

struct event_base *event_base_new(int size);

void event_base_del(event_base *base);

int event_add(event_base *base, int fd, int mask,
              event_proc *proc, void *arg);

int event_del(event_base *base, int fd, int mask);

void event_dispatch(event_base *base);

void register_timer(struct event_base* base, struct time_event* ev, int usec);

void unregister_timer(struct event_base* base, struct time_event* ev);

void file_event_init(event_base* base, int fd);

#endif

