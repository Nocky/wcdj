// A.h
#ifndef _A_H_
#define _A_H_

#include "B.h"// AҪ֪��ģ����B�Ķ���

class A
{
public:
	static A& getTheApp();
	void funA();
	typedef B<int> BINT;
	BINT m_iBa;// ģ����B���͵ĳ�Ա

private:
	static A* theApp;	

};
#endif