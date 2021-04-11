#include <iostream>

//测试C++输入输出
void Test1()
{
	std::cout << "hello world!" << std::endl;
	printf("hello world!\n");
	int i1 = 10;
	int i2 = 20;
	//向标准输出流插入数据：i1，i2
	std::cout << i1 << ',' << i2 << std::endl;
	//从标准输入流提取数据放入变量：i1、i2
	std::cout << "请输入两个数:" << std::endl;
	std::cin >> i1 >> i2;
	std::cout << i1 << ',' << i2 << std::endl;
}

using namespace std;

namespace ns1 {
	void func(void) {
		//std::cout << "ns1::func" << std::endl;
		cout << "ns1::func" << endl;
	}
	int num = 10;
}

namespace ns2 {
	void func(void) {
		cout << "ns2::func" << endl;
	}
}

int num = 20;//将会放入无名名字空间

void Test2()
{
	//func();名字空间的成员不能直接使用
	ns1::func();

	using namespace ns1;
	func();
	using namespace ns2;//可能引入歧义错误
	//func();

	using ns1::func;//名字空间声明
	func();
	//using ns2::func;
	//func();//歧义错误
	using namespace ns2;//名字空间指令
	func();//ns1::func,局部优先
	ns2::func();//ns2::func

	//无名名字空间测试
	using ns1::num;//声明
	cout << ns1::num << endl;//10
	cout << num << endl;//10
	cout << ::num << endl;//20
}

struct Student {
	char name[100];
	int age;
	void who(void) {
		cout << "我叫" << name << ",今年" << age
			<< "岁。" << endl;
	}
};

void Test3()
{
	Student s = { "张飞",25 };
	s.who();
}

void Test4()
{
	union {//匿名联合
		unsigned int un;
		unsigned char uc[4];
	};
	un = 0x12345678;
	for (int i = 0; i < 4; i++) {
		printf("%#x ", uc[i]);//0x78 0x56 0x34 0x12	
	}
	printf("\n");
}

void Test5()
{
	enum Color { RED, GREEN, BLUE = 10, YELLOW };
	/*enum*/ Color c;
	//c = 10;//error
	c = BLUE;
	cout << c << endl;//10
}

void Test6()
{
	bool b = false;
	cout << b << endl;//0
	cout << "sizeof(bool):"<< sizeof(bool) << endl;//0
	cout << "sizeof(b):"<< sizeof(b) << endl;//0
	//插入流控制符boolalpha,以字符串形式打印bool
	cout << boolalpha << b << endl;//false
	b = 100;
	cout << b << endl;//true
	b = 3.14;
	cout << b << endl;//true	
	b = "hello world";
	cout << b << endl;//true
	char* p = NULL;//NULL==>(void*)0
	b = p;
	cout << b << endl;//false
}



int main(int argc, char *argv[])
{
	//测试C++输入输出
	//Test1();
	//测试namespace名字空间
	//Test2();
	//测试C++结构体struct
	//Test3();
	//测试C++联合union
	//Test4();
	//测试C++枚举enum
	//Test5();
	//测试c++bool类型
	Test6();
    return 0;
}
