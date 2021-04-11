#include <iostream>
//使用string需要引入头文件
#include <string>
using namespace std;

void Test1()
{
	int a = 123;
	int& b = a;//b引用a
	b++;
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;

	int c = 321;
	b = c;//将c赋值给a

	cout << "a=" << a << endl;//321
	cout << "b=" << b << endl;//321
}

int foo(void) {
	int a = 100;
	cout << "&a:" << &a << endl;
	return a;
}

void Test2()
{
	//int& r = 100;//error
	const int& r = 100;//ok
	cout << r << endl;//100

	//int& res = foo();//error
	const int& res = foo();//res就是临时变量的别名
	cout << "&res:" << &res << endl;

	const int& c = 3 + 5;
	cout << c << endl;

	char ch = 'A';
	const int& rch = ch;

}

void swap1(int x, int y) {
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
}
void swap2(int* x, int* y) {
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}
void swap3(int& x, int& y) {
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
}

void Test3()
{
	int x = 100;
	int y = 200;
	//swap2(&x,&y);
	swap3(x, y);
	cout << "x=" << x << endl;
	cout << "y=" << y << endl;
}

struct Student {
	char name[100];
	int age;
};

//将函数的参数定义为常引用可以避免意外修改实参的值
//还可以接收常量型的实参
void printStudent(const Student& s) {
	cout << s.name << ',' << s.age/*++*/ << endl;
}

void Test4()
{
	const Student s = { "悟空",26 };
	printStudent(s);
	Student s1 = { "悟空",27 };
	printStudent(s1);
}

struct A {
	int data;
	/*const*/ int& foo(void) {
		return data;
	}
	int& bar(void) {
		int data = 200;
		cout << "&data:" << &data << endl;
		//返回局部变量的引用，危险！
		//函数调用结束以后，内存已经被释放，可能
		//被其它变量所使用，结果异常
		return data;
	}
	int& hum(void) {
		int data = 300;
		cout << "&data:" << &data << endl;
		return data;
	}
};

void Test5()
{
	A a = { 0 };
	//a.foo() = 100;//a.data = 100
	//cout << a.data << endl;//100

	int& data = a.bar();
	cout << data << endl;//200

	a.hum();

	cout << data << endl;//300
}

int main(int argc, char *argv[])
{
	//引用测试
	//Test1();
	//常引用测试
	//Test2();
	//函数参数引用测试
	//Test3();
	//函数参数为常引用
	//Test4();
	//函数返回值为引用
	Test5();
    return 0;
}
