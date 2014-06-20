#if 0
���ֲ����㷨

�ڼ������ѧ�У��۰�������Ҳ�ƶ��ֲ����㷨��������������һ�������������в���ĳһ�ض�Ԫ�ص������㷨�����ع��̴�������м�Ԫ�ؿ�ʼ������м�Ԫ��������Ҫ���ҵ�Ԫ�أ������ع��̽��������ĳһ�ض�Ԫ�ش��ڻ���С���м�Ԫ�أ�����������ڻ�С���м�Ԫ�ص���һ���в��ң����Ҹ���ʼһ�����м�Ԫ�ؿ�ʼ�Ƚϡ������ĳһ��������Ϊ�գ�������Ҳ��������������㷨ÿһ�αȽ϶�ʹ������Χ��Сһ�롣

#endif

#include <stdio.h>

void bubblesort(int a[], int n)
{
	// select min item to first place
	int tmp = 0;

	for (int i = 1; i < n; ++i)
	{
		for (int j = n - 1; j > i - 1; --j)
		{
			if (a[j-1] > a[j])
			{
				tmp    =  a[j];
				a[j]   =  a[j-1];
				a[j-1] =  tmp;
			}
		}

	}
}

void printIntArray(int a[], int size)
{
	for (int i = 0; i != size; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

int bsearch(int a[], int size, int key)
{
	int mid = 0;
	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		mid = (left + right) / 2;
		if (a[mid] == key)
		{
			return mid;
		} 
		else if (a[mid] > key)
		{
			right = mid - 1;
		}
		else if (a[mid] < key)
		{
			left = mid + 1;
		}
	}

	return -1;
}

int main(int argc, char **argv)
{
	int a[] = {2, 1, 4, 6, 3, 5, 7};
	int len = sizeof(a)/sizeof(int);
	printIntArray(a, len);

	bubblesort(a, len);
	printIntArray(a, len);

	printf("bsearch(a, len, 12) = %d\n", bsearch(a, len, 12));
	printf("bsearch(a, len, 5) = %d\n",  bsearch(a, len, 5));
	printf("bsearch(a, len, 2) = %d\n",  bsearch(a, len, 2));

	return 0;
}
/*
output:
2 1 4 6 3 5 7 
1 2 3 4 5 6 7 
bsearch(a, len, 12) = -1
bsearch(a, len, 5) = 4
bsearch(a, len, 2) = 1
 */
