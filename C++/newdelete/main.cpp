#include <iostream>
//使用string需要引入头文件
#include <string>
using namespace std;

void Test1()
{
	int* p = new int;
	*p = 100;
	cout << *p << endl;
	delete p;
	p = NULL;

	//分配内存同时初始化
	p = new int(200);
	cout << *p << endl;//200
	delete p;
	p = NULL;

	//new数组
	//int* pa = new int[10];
	//new数组同时初始化,C++11中支持
	int* pa = new int[10]{ 0,1,2,3,4,5,6,7,8,9 };
	for (int i = 0; i < 10; i++) {
		//pa[i] = i + 1;
		cout << pa[i] << ' ';
	}
	cout << endl;
	delete[] pa;
	pa = NULL;
}


int main(int argc, char *argv[])
{
	//new delete 测试
	Test1();
    return 0;
}
