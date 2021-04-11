#include <iostream>
//使用string需要引入头文件
#include <string>
using namespace std;

void Test1()
{
	int* pi = NULL;
	void* pv = pi;
	pi = static_cast<int*>(pv);

	char c = int(pi);//C++风格强制转换,不合理，使用危险
	//静态转换会检查合理型，不合理，所以报错
	//c = static_cast<char>(pi); 
}

void Test2()
{
	/*volatile关键字修饰的变量意味易变的，内存上的数
	  据随时可能发生改变，告诉编译器每次使用该变量时
	 都要从内存重新的读取一次，而不是取寄存器的副本
	 ，防止编译器优化*/
	const volatile int ci = 100;
	int* pci = const_cast<int*>(&ci);
	*pci = 200;
	cout << "pci:" << pci << endl;
	cout << "&ci:" << (void*)&ci << endl;

	cout << "*pci=" << *pci << endl;
	cout << "ci=" << ci << endl;//200
}

void Test3()
{
	int number = 0x12345678;
	void* ps = reinterpret_cast<void*>(number);
	cout << ps << endl;

	char text[] = "0001\00012345678\000888888";
	struct T {
		char type[5];
		char acc[9];
		char passwd[7];
	};
	//?????
	cout << "sizeof(T):"<<sizeof(T) << endl;
	T* pt = reinterpret_cast<T*>(text);
	cout << pt->type << endl;//0001
	cout << pt->acc << endl;//12345678
	cout << pt->passwd << endl;//888888
}


int main(int argc, char *argv[])
{
	//static_cast测试
	//Test1();
	//const_cast测试
	//Test2();
	//reinterpret_cast测试
	Test3();
    return 0;
}
