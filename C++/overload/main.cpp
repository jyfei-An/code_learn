#include <iostream>
//使用string需要引入头文件
#include <string>
using namespace std;

int foo(int a) {
	cout << "foo(int)" << endl;
	return 0;
}
void foo(int a, int b) {
	cout << "foo(int,int)" << endl;
}
double foo(void) {
	cout << "foo(void)" << endl;
	return 0;
}
void foo(int a, float b) {
	cout << "foo(int,float)" << endl;
}

void Test1()
{
	foo(10);
	foo(10, 20);
	foo();
	foo(10, 3.14f);
	//函数指针的类型(参数)决定其匹配的重载版本
	void(*pfunc)(int, float) = foo;
	pfunc(10, 20);
}

//char->int,升级转换
void bar(int i) {
	cout << "bar(1)" << endl;
}

//char->const char，常量转换
void bar(const char c) {
	cout << "bar(2)" << endl;
}
//short-->char,降级转换
void func(char c) {
	cout << "func(1)" << endl;
}
#if 1
//short-->int,升级转换
void func(int i) {
	cout << "func(2)" << endl;
}
#endif
//short-->long long,过分升级转换,和降级转换同样差
void func(long long ll) {
	cout << "func(3)" << endl;
}

//省略号匹配最差的
void hum(int i, ...) {
	cout << "hum(1)" << endl;
}
//double-->int,降级转换
void hum(int i, int j) {
	cout << "hum(2)" << endl;
}

void Test2()
{
	//一定要先初始化
	char c = 'A';
	bar(c);
	short s = 10;
	func(s);
	hum(10, 1.23);

}

void foo1(int a, int b = 200, int c = 300);//声明
void foo1(int a, int b/*=200*/, int c/*=300*/) {//定义
	cout << "a=" << a << ',' << "b=" << b <<
		',' << "c=" << c << endl;
}
//注意防止重载的歧义冲突
//void foo1(int i) {}

void Test3()
{
	foo1(1);//1,200,300
	foo1(1, 2);//1,2,300
	foo1(1, 2, 3);//1,2,3
}

int add(int a) {
	++a;
	return a;
}
int add(int a, int/*哑元*/) {
	int old = a;
	++a;
	return old;
}

void Test4()
{
	cout << add(10) << endl;//11
	cout << add(10, 0) << endl;//10
}

int main(int argc, char *argv[])
{
	//函数重载测试
	//Test1();
	//函数重载的匹配测试 完全匹配>常量装换>升级转换>降级转换>省略号匹配	
	//Test2();
	//函数默认参数测试
	//Test3();
	//哑元参数测试
	Test4();
    return 0;
}
