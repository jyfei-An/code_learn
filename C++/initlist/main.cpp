#include <iostream>
//使用string需要引入头文件
#include <string>
using namespace std;

class Student {
public:
	/*先定义成员变量，再对其赋初值
	Student(const string& name,int age){
		m_name = name;
		m_age = age;
	}*/
	//定义成员变量同时对其初始化
	Student(const string& name, int age) :
		m_name(name), m_age(age) {}
	void who(void) {
		cout << m_name << ',' << m_age << endl;
	}
private:
	string m_name;
	int m_age;
};

void Test1()
{
	Student s("张飞", 29);
	s.who();
}

class A {
public:
	A(int data) {
		cout << "A::A(int)" << endl;
		m_data = data;
	}
	int m_data;
};
class B {
public:
	//通过初始化表指定成员子对象m_a初始化方式
	B(void) :m_a(100) {
		cout << "B::B(void)" << endl;
	}
	A m_a;
};

void Test2()
{
	B b;
	cout << b.m_a.m_data << endl;//100
}

int g_data = 100;

class AA {
public:
	/*AA(void){
		m_r = g_data;
		m_c = 200;
	}*/
	AA(void):m_r(g_data),m_c(200){}
	int& m_r;
	const int m_c;
};

void Test3()
{
	AA a;
	cout << a.m_r << ' ' << a.m_c << endl;
}

int main(int argc, char *argv[])
{
	//初始化表测试
	//Test1();
	//初始化表测试
	//Test2();
	//必须使用初始化表测试
	Test3();
    return 0;
}
