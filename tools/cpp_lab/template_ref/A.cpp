// A.cpp
#include <stdio.h>
#include "A.h"

A* A::theApp = NULL;

A& A::getTheApp()
{
	 if (theApp == NULL) {
		 theApp = new A();
	 }
	 return *theApp;	
}

void A::funA() {
	printf("funA...\n");

	// ����A�п���ʹ��ģ����B��ģ����B�Ķ�������A.h�а���
	B<int> b1(1);
	printf("m_ib = %d, m_tb = %d\n", b1.m_ib, b1.m_tb);
	B<double> b2(1.0, 2);
	printf("m_ib = %d, m_tb = %lf\n", b2.m_ib, b2.m_tb);
}