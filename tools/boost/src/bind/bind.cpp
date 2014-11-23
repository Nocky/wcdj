#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <boost/bind.hpp>

void print(int i) 
{ 
  std::cout << i << std::endl; 
} 

void add(int i, int j) 
{ 
  std::cout << i + j << std::endl; 
} 

bool compare(int i, int j) 
{ 
  return i > j; 
} 

void print_vec(std::vector<int> &v)
{
	std::vector<int>::iterator iter;
	for (iter = v.begin(); iter != v.end(); ++iter)
	{
		print(*iter);
	}
}

int main() 
{ 
  std::vector<int> v; 
  v.push_back(1); 
  v.push_back(3); 
  v.push_back(2); 

  // ok
  std::for_each(v.begin(), v.end(), print); 
  std::cout << "--------------" << std::endl;

  // error, ���� std::for_each() Ҫ����ǽ�����һ�������ĺ��������Բ���ֱ�Ӵ��� add() ����
  //std::for_each(v.begin(), v.end(), add); 

  // Boost.Bind ���˲�ͬ����֮��İ󶨡� ��ֻ����һ�� boost::bind() ģ�庯���������� boost/bind.hpp ��
  // ��ע��1��
  std::for_each(v.begin(), v.end(), boost::bind(add, 10, _1)); 
  std::cout << "--------------" << std::endl;

  // ok, std::sort() �㷨Ҫ��һ����Ԫ������Ϊ�����������
  std::sort(v.begin(), v.end(), compare);
  print_vec(v);
  std::cout << "--------------" << std::endl;
  
  // ok, ���� compare() �������һ����Ԫ����������ʹ�� boost::bind() ȷ�Ƕ����
  // ��ע��2��
  std::sort(v.begin(), v.end(), boost::bind(compare, _1, _2));
  print_vec(v);
  std::cout << "--------------" << std::endl;

  // ����ʹ�� boost::bind() ����������ġ����磬�������Ҫ���������ж��ֲ����޸� compare() �����Ķ���
  // ��ע��3��
  std::sort(v.begin(), v.end(), boost::bind(compare, _2, _1));
  print_vec(v);

  return 0;
} 
/*
g++ -o bind bind.cpp -I/Users/gerryyang/code/public/boost_1_54_0

mba:bind gerryyang$ ./bind 
1
3
2
--------------
11
13
12
--------------
3
2
1
--------------
3
2
1
--------------
1
2
3
 
* */
