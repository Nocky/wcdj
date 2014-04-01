#!/bin/sh

# ssh devloper@10.137.150.206 devloper
# ls ~/portal/portal_20120514*


# ͳ��2012-05-14��������ݣ�

# 1��
# NoSession�����������: 5718061
cat portal/portal_20120514* | grep "type=first" |grep "NoSession" | gawk 'BEGIN {RS="&"} $0 ~/^PortalSerialNo/ {print $1}' | gawk -F'=' '{print $2}' | sort -u | wc -l

# 2��
# NoSession������ҵ���������: 215
cat portal/portal_20120514* | grep "type=first" |grep "NoSession" | gawk 'BEGIN {RS="&"} $0 ~/^ServiceCode/ {print $1}' | gawk -F'=' '{print $2}' | sort -u | wc -l
# NoSession��ÿ��ҵ������������
cat portal/portal_20120514* | grep "type=first" |grep "NoSession" | gawk 'BEGIN {RS="&"} $0 ~/^ServiceCode/ {print $1}' | gawk -F'=' '{print $2}' | sort > service_nosession_sort.out
cat service_nosession_sort.out | gawk 'BEGIN {cur="-ASOLJA";cnt=0;stat=0} {if(cur==$0){++cnt}else{stat=1;cur=$0;} if(stat==1){print cnt;stat=0;cnt=1}} END{print cnt}' > request.out
cat service_nosession_sort.out | sort -u | wc -l
# NoSession��ÿ��ҵ�����ĳɹ�������
# [0] ����ȡ���гɹ���NoSession���� 
# �ɹ�ʧ���������
cat portal/portal_20120514*.log | grep "type=water" |grep "NoSession" | grep "ResultCode=0" | wc -l 
cat portal/portal_20120514*.log | grep "type=water" |grep "NoSession" | grep "ResultCode=0" > req_nosession_succ.out 
# [1] �ɹ���ÿ��ҵ�����
cat portal/portal_20120514*.log | grep "type=water" |grep "NoSession" | grep "ResultCode=0" | gawk 'BEGIN {RS="&"} $0 ~/^ServiceCode/ {print $1}' | gawk -F'=' '{print $2}' | sort > service_nosession_succ_sort.out
cat service_nosession_succ_sort.out | sort -u > service_nosession_succ.out
# [2] �ɹ���ÿ��ҵ������Ӧ��������
cat service_nosession_succ_sort.out | gawk 'BEGIN {cur="-ASOLJA";cnt=0;stat=0} {if(cur==$0){++cnt}else{stat=1;cur=$0;} if(stat==1){print cur" "cnt;stat=0;cnt=1}} END{print cur" "cnt}' > request_succ.out
# [3] �ɹ���ÿ��ҵ������֧�����
for ServiceCode in \-XXYXLB \-GMHLZT QQACCT_SAVE QQKDC LTMCLUB \-QQXW \-YBDX XXJZGW \-XXGMHD \-QQDJ \-QQPOINT \-HLDDZ XXQQF XXQGAME \-HLDJ CFCLUB XXZXYY \-DNFDQ XXSQQM \-XXGHDJ QQFCZZ \-HXFR QQ3GUO \-HLYXHD \-CFDQ \-XZQY QQR2 DNFHZ \-QCSJLD \-GMDZZT LKWG \-XHZS QQXWZZ \-QXZB \-XXQQTG \-QQBB \-SJMJ \-XLQY \-YXZHSH \-YXDWC \-SQJBLQ GM20010 PETVIP \-QQPET2 \-QQFRFO \-YLZT \-QQXWCFT \-QQXWZD \-PPLOL \-QQS2 \-XXXY \-GMMC MZYFF \-CHHJ \-HEROD \-YXLBS \-JHQXZ \-LOLSC \-LOLDQ \-LHWY \-WXJYHB \-DXQZYY \-QQSCHY \-FXWR \-QQXXYB \-EZFY \-XXYYSC \-DG QQBOOKBY \-QQJX \-HXXY10 \-HLYXML \-QQHX QQR2BY \-LZQY \-WCBYDQ \-CJDQ QQYFSC \-CBSWDH \-YJJA XXQQT \-SZJJT \-LSZT \-XXQQGJZ \-QQZZ \-YXTZSD \-QQHXSJ XXZXGP \-QQXYOL NBAVIP \-FFOWY \-QQBS \-QQSHDQ \-HBTTD \-FHZG \-QSPAY DMLQ XXVIP \-DWSG \-TMXY \-SJOL \-XXDJSC \-AVAD \-MDOL \-WAP1328 \-QQSGPAY \-HXXYSZ \-DWSGAD \-QQXY LTQQX \-MBZH \-MHDL \-SIOL \-HLZY \-TTDS \-HXXY8 \-QQHXSJCFT \-JJDQ \-QQXJDJ \-QQHY \-XWDQ \-CJMX \-XZQYXY AVAVIP \-PKDZ \-GFXY \-DJXZS \-GRSPACE \-DHSH \-QQFYSG XYVIP \-LHSC \-QQCLQB \-MHOL \-KMKZY \-SLYX \-PETQE \-XZTX \-KDJL \-HTQYJA \-XLOL \-CYWC \-LZGDZF \-FFOWEB \-OLMH \-STYX \-ZHJH \-ASOLJA \-PCQQC \-YXDWEB \-QQHXWY \-YDZWYM \-QQXWDJ \-MKZY \-SGT \-ZFTX \-QQXHCS QSBYQZ MHVIP \-QQSCYY \-DGOL \-XIYOLAD \-XYOL \-QQSCQQX \-QQBOOKAT \-HTQYAD \-XJQQ \-YXZC \-DFZQ \-ZSOL \-WZWDQ \-FCWRZF \-XXGAMEFT \-SHOL QQFCHH \-RXOLJA \-HXISDSZ \-CJQAT \-TTGM \-QINGD \-CWJL \-XYZT \-SJLD \-KXCB \-QYOL \-QCDD \-HXSJWB \-FSWAP \-QXDWX \-XXGMRK \-WYMC \-ZSSGZF \-SZHY \-HSPPDJ \-OLTY \-CJWG \-WSOLAD \-RXOLAD \-FEJBQB \-DJQXZB \-BYDHAD \-WSOLJA SJQQYYB \-MYJ \-MSHOL \-DDZAT \-XDTAD \-TYONLINE \-MHDLWB WKVIP \-QQTGSN \-SKOL \-KLCS KDXXSQQ \-CHFY YKPET \-XQQD \-TXSP \-SGII QTD512M QTD256M \-MYQXZB \-MDOLSJ \-HLPPQD \-HBQP \-FCPPQG \-BXOL 
do
	echo "$ServiceCode beg"
	cat req_nosession_succ.out | grep "\\$ServiceCode" | gawk 'BEGIN {RS="&"} $0 ~/^PayAmt=/ {print $1}' | gawk -F'=' -v key="$ServiceCode" 'BEGIN{sum=0} {if($2!=0) sum+=$2} END{printf("%s %d\n",key,sum)}' | sort >> payamt.out
	echo "$ServiceCode end"
done
# �Ե�2���ֶ�����
cat payamt.out | sort -k2 -nr | more

# test
#!/bin/sh
mkdir -p amt
for ServiceCode in \-ASOLJA \-AVAD 
do 
	echo "$ServiceCode beg"
	cat out | grep "\\$ServiceCode" | gawk 'BEGIN{RS="&"} $0 ~/^PayAmt=/ {print $1}' | gawk -F'=' -v key="$ServiceCode" 'BEGIN{sum=0} {if($2!=0) sum+=$2} END{printf("%s %d\n",key,sum)}'
    echo "$ServiceCode end"
done 

# NoSession������ҵ�����
cat portal/portal_20120514* | grep "type=first" |grep "NoSession" | gawk 'BEGIN {RS="&"} $0 ~/^ServiceCode/ {print $1}' | gawk -F'=' '{print $2}' | sort -u > service_all_nosession.out

# 3��
# NoSession��������������: 11
cat portal/portal_20120514* | grep "type=first" |grep "NoSession" | gawk 'BEGIN {RS="&"} $0 ~/^PayChannel=/ {print $1}' | gawk -F'=' '{print $2}' | sort -u | wc -l
# NoSession����������
cat portal/portal_20120514* | grep "type=first" |grep "NoSession" | gawk 'BEGIN {RS="&"} $0 ~/^PayChannel=/ {print $1}' | gawk -F'=' '{print $2}' | sort -u > channel_nosession.out


# ======================================
# ����-DNFDQ��SessionType���ͺ�֧������
# SessionType����
cat portal/portal_20120514*.log | grep "type=water" | grep "ResultCode=0" > req_allsession_succ.out 
cat portal/portal_20120514*.log | grep "type=water" | grep "ResultCode=0" | grep "ServiceCode=-DNFDQ" | gawk 'BEGIN {RS="&"} $0 ~/^SessionType/ {print $1}' | gawk -F'=' '{print $2}' | sort > sessiontype_sort.out
cat sessiontype_sort.out | gawk 'BEGIN {cur="community";cnt=0;stat=0} {if(cur==$0){++cnt}else{stat=1;cur=$0;} if(stat==1){print cnt;stat=0;cnt=1}} END{print cnt}' > request_by_sessiontype.out
cat sessiontype_sort.out | sort -u > sessiontype_uniqsort.out

# ֧������(CmdCodeû��ֵ)
cat portal/portal_20120514*.log | grep "type=water" | grep "ResultCode=0" | grep "ServiceCode=-DNFDQ" | gawk 'BEGIN {RS="&"} $0 ~/^CmdCode/ {print $1}' | gawk -F'=' '{print $2}' | sort > cmdcode_sort.out
cat cmdcode_sort.out | gawk 'BEGIN {cur="prepay";cnt=0;stat=0} {if(cur==$0){++cnt}else{stat=1;cur=$0;} if(stat==1){print cnt;stat=0;cnt=1}} END{print cnt}' > request_by_cmdcode.out
cat cmdcode_sort.out | sort -u > cmdcode_uniqsort.out


