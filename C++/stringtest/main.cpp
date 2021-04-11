#include <iostream>
//使用string需要引入头文件
#include <string>
using namespace std;

void Test1()
{
	//定义一个字符串
	string s = "hello";
	cout << s << endl;//hello
	

	//字符串连接
	s += " world!";
	cout << s << endl;//hello world!


	//字符串的拷贝
	string s2;
	s2 = s;
	cout << "s2=" << s2 << endl;//hello world!


	//字符串的交换
	string s3 = "abcdefg";
	swap(s2, s3);
	cout << "s2=" << s2 << endl;//abcdefg
	cout << "s3=" << s3 << endl;//hello world!
	//获取字符串中某个字符
	cout << s[0] << s[1] << s[2] << endl;//hel

	//字符串比较
	cout << (s == s2) << endl;//0
	cout << (s == s3) << endl;//1
	cout << (s > s2) << endl;//1

	//转化为C风格的字符串
	//c_str():string-->char*
	cout << strlen(s.c_str()) << endl;

	//获取字符串长度
	cout <<"s.length():"<< s.length() << endl;
	cout <<"s.size():"<< s.size() << endl;
}

int main(int argc, char *argv[])
{
	//测试string的基本知识
	Test1();
    return 0;
}
