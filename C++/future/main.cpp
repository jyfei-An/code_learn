#include <iostream>
#include <future>

void Test1()
{
	//使用std::async创建简单异步任务
	auto future = std::async(std::launch::async, []() {
		//while(1)
		std::cout << "I'm a thread" << std::endl;
	});

	std::cout << "waiting0..." << std::endl;
	//阻塞当前线程，直至异步任务完成并返回结果
	//如果创建的线程中存在死循环，则永远不会执行下一步
	future.get();
	std::cout << "waiting1..." << std::endl;
	//get方法不能调用两次，一旦调用get方法获取线程结果，再次获取将会报错
	//future.get();
}

void Test2()
{
	auto future = std::async(std::launch::async, []() {
		std::this_thread::sleep_for(std::chrono::seconds(5));
		return 42;
	});

	std::cout << "waiting0..." << std::endl;
	//blocking阻塞
	std::cout << future.get() << std::endl;
	std::cout << "waiting1..." << std::endl;
}

int main(int argc, char *argv[])
{
	Test1();
	Test2();
    return 0;
}
