#!/bin/bash

:<< WCDJ
sar�кܶ���;�����Ҫ���������������ʹ������������з�ʽ��

sar -n DEV interval count

���У�interval��ͳ��ʱ����������Ϊ��λ��count���ܹ�ͳ�Ƽ��Σ����Ϊ0�Ͳ��ϵ�ͳ��ֱ�� Ctrl+C ��ϣ�����ִ��count�ξ��˳���

���磺sar -n DEV 1 4
���磺sar -n DEV 10 0

IFACE��LAN�ӿ�
rxpck/s��ÿ���ӽ��յ����ݰ�
txpck/s��ÿ���ӷ��͵����ݰ�
rxbyt/s��ÿ���ӽ��յ��ֽ���
txbyt/s��ÿ���ӷ��͵��ֽ���

���ߣ�
watch more /proc/net/dev 

WCDJ

sar -n DEV 1 4

