// B.h
#ifndef _B_H_
#define _B_H_

// ����ģ����B
template <typename T>
class B
{
public:
	B(){}
	B(T tvar, int ivar = 0):// ��ʼ��
	  m_tb(tvar), m_ib(ivar){}
	void funB();

	T m_tb;
	int m_ib;
};

template <typename T>
void B<T>::funB()
{
	printf("funB...\n");
	A::getTheApp().funA();

	A a;
	printf("a.m_iBa.m_ib = %d\n", a.m_iBa.m_ib);// ���ʣ�m_ibΪʲôû�б���ʼ��Ϊ0
}

/* ˵����
 * (1) ��B.h��ģ����ʹ�õ���A.h�еĶ��壬������B.h�в���Ҫ֪��A���������塣
 * ����ģ����B�п���ʹ���κ����ͣ����ҽ�����ģ����Bʵ����ʱ���ű������A���͵Ķ��塣
 * 
 * (2) �� #include "A.h" ����ģ����B����֮��ԭ���ǣ���A.h����Ҫ����֪��ģ����B�Ķ��塣
*/
#include "A.h"

#endif