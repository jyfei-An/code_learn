#include <iostream>
#include <set>

using namespace std;

void Test1()
{
	/*

	在Linux环境下调用

	_Rb_tree<int, int, _Identity<int>, less<int>> itree;
	cout << itree.empty() << endl;  //1
	cout << itree.size() << endl;   //0

	itree._M_insert_unique(3);
	itree._M_insert_unique(8);
	itree._M_insert_unique(5);
	itree._M_insert_unique(9);
	itree._M_insert_unique(13);
	itree._M_insert_unique(5);  //no effect, since using insert_unique().
	cout << itree.empty() << endl;  //0
	cout << itree.size() << endl;   //5
	cout << itree.count(5) << endl; //1

	itree._M_insert_equal(5);
	itree._M_insert_equal(5);
	cout << itree.size() << endl;   //7, since using insert_equal().
	cout << itree.count(5) << endl; //3 

		*/
}



int main(int argc, char *argv[])
{
	Test1();
    return 0;
}
