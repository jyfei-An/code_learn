#include <iostream>
//使用string需要引入头文件
#include <string>
using namespace std;


/*

使用C实现虚函数多态

//class A {
//protected:
//    int a;
//public:
//    A() {a = 10;}
//    virtual void update() {a++;}
//    int access() {update(); return a;}
//};

struct A;

//存储函数指针
typedef struct {
	void (*A)(struct A*);
	void (*update)(struct A*);
	int (*access)(struct A*);
} A_functable;

//class存储data和虚指针，虚指针指向虚表
typedef struct A{
	int a;
	A_functable *vmt;
} A;

void A_A(A *this);
void A_update(A* this);
int A_access(A* this);

A_functable A_vmt = {A_A, A_update, A_access};

//构造函数，将虚指针与虚表进行绑定
void A_A(A *this) {this->vmt = &A_vmt; this->a = 10;}
void A_update(A* this) {this->a++;}
int A_access(A* this) {this->vmt->update(this); return this->a;}


//class B: public A {
//public:
//	void update() {a--;}
//};


struct B;
//B继承A，A的虚表B也会继承一份，声明的虚函数会覆盖基类的虚函数
typedef struct {
	void(*B)(struct B*);
	void(*update)(struct B*);
	int(*access)(struct A*);
} B_functable;

typedef struct B {
	A inherited;
} B;

void B_B(B *this);
void B_update(B* this);

B_functable B_vmt = { B_B, B_update, A_access };
//调用基类的构造函数，将虚指针与虚表进行绑定
void B_B(B *this) { A_A(this); this->inherited.vmt = &B_vmt; }
void B_update(B* this) { this->inherited.a--; }
int B_access(B* this) { this->inherited.vmt->update(this); return this->inherited.a; }

int main() {
	A x;
	B y;
	A_A(&x);
	B_B(&y);
	printf("%d\n", x.vmt->access(&x));
	printf("%d\n", y.inherited.vmt->access(&y));
}



*/

// 针对上面的代码我们做出以下改造
// 1.我们增加一个派生类Derive去继承Base
// 2.Derive中重写Func1
// 3.Base再增加一个虚函数Func2和一个普通函数Func3
class Base
{
public:
	virtual void Func1()
	{
		cout << "Base::Func1()" << endl;
	}
	virtual void Func2()
	{
		cout << "Base::Func2()" << endl;
	}

	void Func3()
	{
		cout << "Base::Func3()" << endl;
	}

private:
	int _b = 1;
};

class Derive : public Base
{
public:
	virtual void Func1()
	{
		cout << "Derive::Func1()" << endl;
	}
private:
	int _d = 2;
};

int main()
{
	Base b;
	Derive d;

	return 0;
}

