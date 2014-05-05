#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <boost/lambda/lambda.hpp> 
#include <boost/lambda/if.hpp> 

void print(int i) 
{ 
	std::cout << i << std::endl; 
} 

int main() 
{ 
	std::vector<int> v; 
	v.push_back(1); 
	v.push_back(3); 
	v.push_back(2); 

	// ��ע��1��
	std::for_each(v.begin(), v.end(), print); 
	std::cout << "--------------" << std::endl;
	
	// ��ע��2��
	std::for_each(v.begin(), v.end(), std::cout << boost::lambda::_1 << "\n"); 
	std::cout << "--------------" << std::endl;

	// ֻ������1��Ԫ��д������׼�����
	// ��ע��3��
	std::for_each(v.begin(), v.end(), 
			boost::lambda::if_then(boost::lambda::_1 > 1, 
				std::cout << boost::lambda::_1 << "\n")); 

	return 0;
} 
/*
mba:bind gerryyang$ ./lambda 
1
3
2
--------------
1
3
2
--------------
3
2 
* */
