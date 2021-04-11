#include <iostream>
//使用string需要引入头文件
#include <string>
using namespace std;

class Student {
public:
	//构造函数
	Student()
	{

	}
	Student(const string& name, int age, int no) {
		cout << "Student::Student(..)" << endl;
		m_name = name;
		m_age = age;
		m_no = no;
	}

	//行为
	void eat(const string& food) {
		cout << "我吃" << food << endl;
	}
	void sleep(int time) {
		cout << "我睡了" << time << "小时" << endl;
	}
	void learn(const string& course) {
		cout << "我学" << course << endl;
	}
	void who(void) {
		cout << "我叫" << m_name << ",今年" <<
			m_age << "岁，学号是" << m_no << endl;
	}
	/*私有属性的成员不能访问，但是可以提供公有的接口
	函数来间接访问，可以对非法数据加以限定，或者控
	制业务逻辑的合理性*/
	void setName(const string& name) {
		if (name == "二") {
			cout << "你才" << name << endl;
		}
		else {
			m_name = name;
		}
	}
	void setAge(int age) {
		if (age < 0) {
			cout << "无效年龄" << endl;
		}
		else {
			m_age = age;
		}
	}
	void setNo(int no) {
		if (no < 1000) {
			cout << "无效学号" << endl;
		}
		else {
			m_no = no;
		}
	}
private:
	//属性
	string m_name;
	int m_age;
	int m_no;
};

void Test1()
{
	//创建对象/或者对象实例化
	Student s;
#if 0
	s.m_name = "张飞";
	s.m_name = "二";
	s.m_age = 25;
	s.m_no = 10011;
#endif
	s.setName("张飞");
	s.setName("二");
	s.setAge(25);
	s.setAge(-10);
	s.setNo(10086);
	s.setNo(250);

	s.who();
	s.eat("牛肉");
	s.sleep(8);
	s.learn("C++编程");
}

void Test2()
{
	//栈区创建单个对象
//	Student s("张飞",28,10011);
	//和上面等价
	Student s = Student("张飞", 28, 10011);
	s.who();

	//栈区创建多个对象
	Student sa[3] = { Student("赵云",27,10012),
					Student("关羽",30,10013),
					Student("刘备",35,10010) };
	sa[0].who();
	sa[1].who();
	sa[2].who();

	//在堆区创建单个对象
	Student* ps = new Student("曹操", 38, 10086);
	ps->who();
	delete ps;//销毁
	ps = NULL;

	//在堆区创建多个对象
	ps = new Student[3]{
				Student("司马懿",40,10087),
				Student("张辽",35,10088),
				Student("曹仁",28,10089) };
	ps[0].who();
	ps[1].who();
	ps[2].who();
	delete[] ps;
	ps = NULL;
}

class Teacher {
public:
	/*Teacher(void){
		cout << "缺省构造函数" << endl;
	}*/
	Teacher(const string& name = "无名", int age = 0) {
		m_name = name;
		m_age = age;
	}
	void who(void) {
		cout << m_name << ',' << m_age << endl;
	}
private:
	string m_name;//类 类型
	int m_age;//基本类型
};

void Test3()
{
	Teacher t;
	t.who();
}

class Ingeter {
public:
	Ingeter(void) {
		cout << "Ingeter::Ingeter()" << endl;
		m_data = 0;
	}
	//类型转换构造函数(单参构造函数)
	//explicit关键字：告诉编译器必须做显示转换
	/*explicit*/ Ingeter(const int& i) {
		cout << "Ingeter::Ingeter(int)" << endl;
		m_data = i;
	}
	void print(void) {
		cout << m_data << endl;
	}
private:
	int m_data;
};

void Test4()
{
	Ingeter i;
	i.print();//0
	//编译器会自动调用类型转换构造函数，将100-》转换成Ingeter对象，再赋值
	i = 100;
	i.print();//100

	//显示类型转换
	//i = (Ingeter)200;//ok
	i = Ingeter(200);//best
	//i = static_cast<Ingeter>(200);//good
	i.print();
}

class A {
public:
	A(int data = 0) {
		cout << "A::A(void)" << endl;
		m_data = data;
	}
	//拷贝构造函数，参数必须是当前 类 类型的常引用
	A(const A& that) {
		cout << "A::A(const A&)" << endl;
		m_data = that.m_data;
	}
	int m_data;
};

void Test5()
{
	A a1(100);
	//A a2(a1);
	A a2 = a1;//和上面写法完全等价	
	cout << a1.m_data << endl;//100
	cout << a2.m_data << endl;//100
}

class AA {
public:
	AA(int data = 0) {
		cout << "A::A(int=0)" << endl;
		m_data = data;
	}
	AA(const A& that) {
		cout << "A::A(const A&)" << endl;
		m_data = that.m_data;
	}
	int m_data;
};
class BB {
public:
	BB(void) {
		cout << "B::B(void)" << endl;
	}
	BB(const BB &that)
	{

	}
	AA m_a;
};

void Test6()
{
	BB b;
	cout << b.m_a.m_data << endl;//0
	b.m_a.m_data = 100;
	BB b2(b);//调用拷贝构造函数
	cout << b2.m_a.m_data << endl;//100
}

int main(int argc, char *argv[])
{
	//创建对象 / 或者对象实例化测试
	//Test1();
	//栈区/堆区 创建单个/多个对象
	//Test2();
	//构造函数默认参数测试
	//Test3();
	//类型转换构造函数测试
	//Test4();
	//拷贝构造函数测试
	//Test5();
	//拷贝构造函数测试
	Test6();
    return 0;
}
