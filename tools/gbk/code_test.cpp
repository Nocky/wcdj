/*  
 * ��ֹ��β����(GBK)�������� 
 * gerryyang 
 * 2012-07-14 
 */  
  
#include <stdio.h>  
#include <string.h>  
#include <string>  
using std::string;  
  
/* 
 * ���ܣ�����GBK���Ĵ������ضϵĳ����Է�ֹ��β���ֳ������� 
 * @para s: ����GBK�����ַ�����ͷָ�� 
 * @para iLeft: �����ⲿ�ܹ�ʹ�õĻ�������С 
 * @para ret: ���������ַ���s������ȡ�ĳ��� 
 */  
  
int GbkSubString(const char *s, int iLeft)  
{  
    int len = 0, i = 0;  
  
    if( s == NULL || *s == 0 || iLeft <= 0 )   
        return(0);  
  
    while( *s )  
    {  
        if( (*s & 0x80) == 0 )  
        {  
            i ++;  
            s ++;  
            len ++;  
        }  
        else  
        {  
            if( *(s + 1) == 0 ) break;  
  
            i += 2;  
            s += 2;  
            len += 2;  
        }  
  
        if( i == iLeft ) break;  
        else if( i > iLeft )  
        {  
            len -= 2;  
            break;  
        }  
    }  
  
    return(len);  
}  
  
  
int main(int argc, char **argv)  
{  
    char szBuf[10] = {0};  
    string str = "123abc���";  
  
    /*  
     * [1] δ�������Ľضϵ���� 
     */  
    snprintf(szBuf, sizeof(szBuf), "%s", str.c_str());  
    printf("szBuf: %s\n", szBuf);  
  
    /* 
     * [2] �������Ŀ��ܱ��ضϵ���� 
     */  
    memset(szBuf, 0x0, sizeof(szBuf));  
    int iBufLeftLen = sizeof(szBuf)-1;  
  
    // ����Ϸ��ĳ���ΪiGbkValidLen  
    int iGbkValidLen = GbkSubString(str.c_str(), iBufLeftLen);  
    puts("");  
    printf("str�������ȡ�ĳ���Ϊ: %d\n", iGbkValidLen);  
    snprintf(szBuf, iGbkValidLen + 1, "%s", str.c_str());  
    printf("szBuf: %s\n", szBuf);  
  
  
    return 0;  
}  
  
/*  
g++ -Wall -g -o code_test code_test.cpp 
 
output: 
szBuf: 123abc��? 
 
str�������ȡ�ĳ���Ϊ: 8 
szBuf: 123abc�� 
*/  

