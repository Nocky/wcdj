#ifndef PACKAGE_H_H
#define PACKAGE_H_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

typedef unsigned char   BYTE;
typedef unsigned int   __u32;
typedef unsigned short __u16;

#define PKG_HEAD_SIZE  5
#define MAX_PKT_SIZE   (1024 * 1024)

/*
 ******   Э���ʽ    *********
 * unsigned char  SOH;     ��ͷ
 * unsigned int   len;     ����
 * unsigned int   cmd;     �����
 * unsigned int   seq;     ���к�
 * unsigned char  body[n]; �䳤�İ���
 * unsigned char  EOT;     ��β

   1     4    4    4    n      1
   SOH  len  cmd  seq  body    EOT
*/

//��ͷ�Ͱ�β
#define SOH              0x28
#define EOT              0x29

//���и����ֶε�λ��
#define PACKAGE_SOH      0
#define PACKAGE_LEN      1
#define PACKAGE_CMD      5
#define PACKAGE_SEQ      9
#define PACKAGE_BODY     13

//����Ĭ��size
#define PACKAGE_DEFAULT_SIZE   1024

//������С����
#define PACKAGE_MIN_LEN  18

struct pbpack
{
    BYTE *buf;
    int pos;
    int tail;
    int total;
};


void SetCmd(struct pbpack* pkt, __u32 ulCmd);

__u32 GetCmd(const struct pbpack* pkt);

void SetSeq(struct pbpack* pkt, __u32 wSeq);

__u32 GetSeq(const struct pbpack* pkt);

bool AddAllData(struct pbpack* pkt, const char* buf, int len);

int GetPackLen(struct pbpack* pkt);

const char* GetDataPos(struct pbpack* pkt);

int GetDataSize(struct pbpack* pkt);

void Destroy(struct pbpack* pkt);

struct pbpack* CreatePack(char* buf, int len);

const char* PackToStr(struct pbpack* pkt);

struct pbpack* StrToPack(char* buf, int len);

#endif

