#include <iostream>
//使用string需要引入头文件
#include <string>
using namespace std;

int g_data = 100;

class A
{
public:
	/*A(void)
	{
		cout <<"A默认构造函数" << endl;
	}*/
	
	A(int a)
	{
		cout << "A有参构造函数" << endl;
	}
};

class AA
{
public:
	AA(void)
	{
		cout << "AA无参构造函数" << endl;
	}
	//拷贝构造函数也是构造函数
	AA(const A&that)
	{
		cout << "AA拷贝构造函数" << endl;
	}
private:

};

class AAA
{
public:
	//如果一个构造函数为所有参数提供了默认实参，则它实际上也定义了默认构造函数
	AAA(int a = 100)
	{
		cout << "AAA构造函数" << endl;
	}
};


class B
{
public:
	//先定义成员变量，再对其赋初值
	//如果没有再构造函数的初始值列表中显示地初始化成员，则该成员在构造函数体之前执行默认初始化
	//通过初始化表指定成员子对象m_a初始化方式
	//成员变量的初始化顺序由声明顺序决定，而与初始化表的顺序无关.
	B(const string& name, int age) :m_a(100), m_r(g_data), m_c(200) {
		//m_name为空，m_age为随机数
		cout << m_name << ',' << m_age << endl;
		m_name = name;
		m_age = age;
		cout << m_name << ',' << m_age << endl;
		
		/*error，引用和const变量必须初始化，不能先定义后赋值
		m_r = g_data;
		m_c = 200;
		*/
	}
	
	//定义成员变量同时对其初始化
	/*
	B(const string& name, int age):m_name(name), m_age(age) {
		cout << m_name << ',' << m_age << endl;
	}
	*/
	void who(void) {
		cout << m_name << ',' << m_age << endl;
	}
private:
	//当成员属于某种类类型且该类没有定义默认构造函数时（提供的构造函数均为有参构造函数），必须将这个成员初始化
	A m_a;
	AA m_aa;
	AAA m_aaa;
	string m_name;
	int m_age;
	
	//引用和const变量必须初始化，不能先定义后赋值
	int& m_r;
	const int m_c;
};



void Test1()
{
	B b("张飞", 29);
	b.who();
}


int main(int argc, char *argv[])
{
	//初始化表测试
	Test1();
    return 0;
}
