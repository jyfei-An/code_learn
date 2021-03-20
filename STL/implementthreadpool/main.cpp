// ConsoleApplication11.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <vector>
#include <queue>
#include<thread>
#include <condition_variable>

//https://www.youtube.com/watch?v=eWTGtp3HXiw&t=531s&ab_channel=CodeBlacksmith
//https://pastebin.com/MM5kSvH6

class Threadpool
{
public:

	using Task = std::function<void()>;

	explicit Threadpool(std::size_t numthreads)
	{
		Start(numthreads);
	}

	~Threadpool()
	{
		Stop();
	}

	void enqueue(Task task)
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			//???
			m_tasks.emplace(std::move(task));

		}

		m_conditionvariable.notify_one();
	}
private:
	void Start(std::size_t numthreads)
	{
		for (auto i = 0u; i < numthreads; ++i)
		{
			m_threads.emplace_back([=] {

				while (true)
				{
					Task task;

					{
						std::unique_lock<std::mutex> lock(m_mutex);

						//wait？？？？？
						m_conditionvariable.wait(lock, [=] {return m_stopping || !m_tasks.empty(); });

						if (m_stopping || m_tasks.empty())
						{
							break;
						}

						task = std::move(m_tasks.front());
						m_tasks.pop();
					}



					task();
				}

			});
		}
	}

	void Stop()noexcept
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_stopping = true;
		}
		m_conditionvariable.notify_all();

		//引用
		for (auto &thread : m_threads)
		{
			thread.join();
		}
	}

private:
	bool m_stopping = false;
	std::vector<std::thread> m_threads;
	std::condition_variable m_conditionvariable;
	std::mutex m_mutex;

	std::queue<Task> m_tasks;
};

int main()
{
	Threadpool pool{ 36 };
	pool.enqueue([] {
		std::cout << "1" << std::endl;
	});
	pool.enqueue([] {
		std::cout << "2" << std::endl;
	});
	std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
