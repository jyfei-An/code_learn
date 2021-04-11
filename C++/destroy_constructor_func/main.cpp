#include <iostream>
//使用string需要引入头文件
#include <string>
#include "main.h"
using namespace std;

class Integer {
public:
	Integer(int data = 0) :m_data(new int(data)) {
		//m_data = new int(data);
	}
	/*构造函数在对象被创建时自动调用，析构函数和构
	  造函数相反，在对象被销毁时自动调用*/
	~Integer(void) {
		cout << "析构函数" << endl;
		delete m_data;
	}
	int get(void)const {
		return *m_data;
	}
private:
	int* m_data;
};

void Test1()
{
	Integer i(100);
	cout << i.get() << endl;//100
}

class A {
public:
	~A(void) { cout << "A::~A(void)" << endl; }
};

void Test2()
{
	do {
		A a1;
		A* pa2 = new A;
		cout << "test1" << endl;
		delete pa2;//delete-->A::~A()
		cout << "test3" << endl;
	} while (0);//"}"-->A::~A()
	cout << "test2" << endl;
}

class A1 {
public:
	A1(void) { cout << "A::A(void)" << endl; }
	~A1(void) { cout << "A::~A(void)" << endl; }
};
class B {
public:
	B(void) { cout << "B::B(void)" << endl; }
	~B(void) { cout << "B::~B(void)" << endl; }
	A1 m_a;
};

void Test3()
{
	B b;
}

class Integer1 {
public:
	Integer1(int data = 0) :m_data(new int(data)) {
	}
	/*缺省拷贝构造，浅拷贝
	Integer(const Integer& that)
		:m_data(that.m_data){}*/
		/*Integer(const Integer& that){
			m_data = that.m_data;
		}*/

		//自定义，深拷贝
		/*Integer(const Integer& that):
			m_data(new int(*that.m_data)){}*/
	Integer1(const Integer1& that) {
		m_data = new int;
		*m_data = *that.m_data;
	}

	~Integer1(void) {
		delete m_data;
	}
	int get(void)const {
		return *m_data;
	}
private:
	int* m_data;
};

void Test4()
{
	Integer1 i(100);
	cout << i.get() << endl;//100
	Integer1 i2(i);//拷贝构造
	cout << i2.get() << endl;//100
}

int main(int argc, char *argv[])
{
	//析构函数测试
	Test1();
	Test2();
	Test3();
	Test4();
    return 0;
}
