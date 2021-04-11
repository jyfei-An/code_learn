#include <iostream>
//使用string需要引入头文件
#include <string>
#include "main.h"
using namespace std;

class A {
public:
	A(int data = 0) :m_data(data) {}
	/*如果成员函数中不需要修改类中的成员变量，那么
	  就应该声明为常函数，避免意外修改其成员变量*/
	void print(void)const {
		cout << m_data/*++*/ << endl;
	}
	void show(void)const {
		cout << m_data++ << endl;
		//cout << const_cast<A*>(this) -> m_data++ 
		//	<< endl;
	}
	/*void show(const A* this){
		cout << this->m_data++ << endl;
	}*/
private:
	//mutable修饰的成员变量会在使用是去除常属性
	//该成员变量可以在常函数中被修改
	mutable int m_data;
};

void Test1()
{
	A a(100);
	//a.print();//100
	//a.print();//100
	a.show();
	a.show();
}

class A1 {
public:
	//void func1(const A* this)
	void func1(void)const {
		cout << "常函数" << endl;
	}
	//void func2(A* this)
	void func2(void) {
		cout << "非 常函数" << endl;
	}
};

void  Test2()
{
	A1 b;//非 常对象
	b.func1();//func1(&b);&b:A* 
	b.func2();
	const A1 b2 = b;//常对象
	b2.func1();//func1(&b2);&b2:const A*
	//b2.func2();//func2(&b2);&b2:const A*

	const A1* p = &b;//p常指针
	p->func1();//ok
	//p->func2();//error

	const A1& r = b;//r常引用
	r.func1();//ok
	//r.func2();//error
}

class A2 {
public:
	//void func(const A*){}
	void func(void)const {
		cout << "func函数常版本" << endl;
	}
	//void func(A*){}
	void func(void) {
		cout << "func函数非常版本" << endl;
	}
};

void Test3()
{
	A2 a;
	const A2& ra = a;
	a.func();
	ra.func();
}

int main(int argc, char *argv[])
{
	//不能在常函数中修改成员变量的值
	//被mutable关键字修饰的成员变量可以在常函数中被修改
	Test1();
	//非常对象既可以调用非常函数，也可以调用常函数，但是常对象只能调用常函数，不能调用非常函数。
	//常对象包含常指针和常引用
	Test2();
	Test3();
    return 0;
}
