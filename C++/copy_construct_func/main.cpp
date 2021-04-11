#include <iostream>
//使用string需要引入头文件
#include <string>
using namespace std;

class A {
public:
	A(void) {}
	A(const A& that) {
		cout << "A::A(const A&)" << endl;
	}
};
void foo(A a) {}
A bar(void) {
	A a;
	cout << "bar::" << &a << endl;
	return a;//拷贝构造
}

void Test1()
{
	A a1;
	A a2 = a1;//拷贝构造
	foo(a1);//拷贝构造
	/*bar函数返回将a拷贝到临时对象，临时对象再拷贝给
	  a3,发生两次对象的拷贝*/
	  /*因为编译器优化：a3直接引用函数返回的a，不再
		发生拷贝*/
		/*防止编译器优化选项：
		  g++ 09cpcons.cpp -fno-elide-constructors*/
	A a3 = bar();//拷贝构造
	cout << "a3:" << &a3 << endl;
}

int main(int argc, char *argv[])
{
	//函数返回值拷贝构造函数测试
	Test1();
    return 0;
}
