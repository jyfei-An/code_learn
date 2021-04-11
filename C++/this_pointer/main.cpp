#include <iostream>
//使用string需要引入头文件
#include <string>
#include "main.h"
using namespace std;

class User {
public:
	/*
	User(const string& name,int age):
		m_name(name),m_age(age){
		cout << "构造函数:" << this << endl;
	}*/
	//当参数变量名和成员变量名一样，必须用this区分
	User(const string& m_name, int m_age) {
		this->m_name = m_name;
		this->m_age = m_age;
	}
	void print(void) {
		cout << m_name << "," << m_age << endl;
		cout << this->m_name << "," <<
			this->m_age << endl;
	}/*print被编译器编译后,代码类似：
	  void print(User* this){
		cout << this->m_name << "," <<
			this->m_age << endl;
	  }*/
private:
	string m_name;
	int m_age;
};

void Test1()
{
	User user1("张飞", 28);
	User user2("赵云", 25);
	cout << "user1:" << &user1 << endl;
	cout << "user2:" << &user2 << endl;

	user1.print();//user1.print(&user1)
	user2.print();//user2.print(&user2)
}

class Counter {
public:
	Counter(int data = 0) :m_data(data) {}
	Counter& add(void) {
		++m_data;
		return *this;//返回自引用
	}
	int m_data;
};

void Test2()
{
	Counter cn(2);
	cn.add().add().add();
	cout << cn.m_data << endl;//5
}

int main(int argc, char *argv[])
{
	//this指针区分作用域
	Test1();
	//this指针区返回自引用
	Test2();
    return 0;
}
