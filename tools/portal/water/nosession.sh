#!/bin/sh


# ͳ��2012-05-14��������ݣ�

# 1��
# NoSession�����������: 5718061
cat portal/portal_20120514* | grep "type=first" |grep "NoSession" | gawk 'BEGIN {RS="&"} $0 ~/^PortalSerialNo/ {print $1}' | gawk -F'=' '{print $2}' | sort -u | wc -l

# 2��
# NoSession������ҵ���������: 215
# NoSession������ҵ�����
cat portal/portal_20120514* | grep "type=first" |grep "NoSession" | gawk 'BEGIN {RS="&"} $0 ~/^ServiceCode/ {print $1}' | gawk -F'=' '{print $2}' | sort -u | wc -l
cat portal/portal_20120514* | grep "type=first" |grep "NoSession" | gawk 'BEGIN {RS="&"} $0 ~/^ServiceCode/ {print $1}' | gawk -F'=' '{print $2}' | sort -u > service_nosession.out

# 3��
# NoSession��������������:
# NoSession����������
cat portal/portal_20120514* | grep "type=first" |grep "NoSession" | gawk 'BEGIN {RS="&"} $0 ~/^PayChannel/ {print $1}' | gawk -F'=' '{print $2}' | sort -u | wc -l
cat portal/portal_20120514* | grep "type=first" |grep "NoSession" | gawk 'BEGIN {RS="&"} $0 ~/^PayChannel/ {print $1}' | gawk -F'=' '{print $2}' | sort -u > channel_nosession.out



