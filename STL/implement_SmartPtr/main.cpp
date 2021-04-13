
/*
	SharedPtr智能指针的简单实现
*/

template<typename T>
class SamrtPtr
{
public:
	//构造函数
	SamrtPtr(T* ptr = nullptr) :m_ptr(ptr) {
		if (m_ptr) {
			m_count = new size_t(1);
		}
		else {
			m_count = new size_t(0);
		}
	}

	//拷贝构造函数
	SamrtPtr(const SamrtPtr&that)
	{
		if (this != &that) {
			this->m_ptr = that.m_ptr;
			//指针指向的实际上是同一个计数器，同一块内存
			this->m_count = that.m_count;
			(*this->m_count)++;
		}
	}

	//拷贝赋值函数
	SamrtPtr&operator=(const SamrtPtr&that)
	{
		//指针指向的实际上是同一个计数器，同一块内存
		if (this->m_ptr == that.m_ptr)
		{
			return *this;
		}

		if (this->m_ptr)
		{
			//将原来的引用计数减一
			(*this->_count)--;
			if (this->_count == 0) {
				delete this->_ptr;
				delete this->_count;
			}
		}

		this->m_ptr = that.m_ptr;
		this->m_count = that.m_count;
		(*this->m_count)++;
		return *this;
	}

	//重载*操作符
	T& operator*()
	{
		return *(this->m_ptr);
	}

	T *operator->()
	{
		return this->m_ptr;
	}

	~SamrtPtr()
	{
		(*this->m_count)--;
		if (*this->m_count == 0)
		{
			delete this->m_ptr;
			delete this->m_count;
		}
	}

	size_t use_count() {
		return *this->m_count;
	}

private:
	//指针
	T* m_ptr;
	//计数器
	size_t* m_count;
};

/*
UniquePtr的简单实现
*/

template<typename T>
class UP
{
	T*   data;
public:
	// Explicit constructor
	explicit UP(T* data)
		: data(data)
	{}
	~UP()
	{
		delete data;
	}
	// Remove compiler generated methods.
	UP(UP const&) = delete;
	UP& operator=(UP const&) = delete;

	// Const correct access owned object
	T* operator->() const { return data; }
	T& operator*()  const { return *data; }

	// Access to smart pointer state
	T* get()                 const { return data; }
	explicit operator bool() const { return data; }

	// Modify object state
	T* release()
	{
		T* result = nullptr;
		std::swap(result, data);
		return result;
	}
};

/*===========================================================================*/
/*
WeakPtr的简单实现
*/
/*
Counter对象的目地就是用来申请一个块内存来存引用计数和弱引用计数。shareCount是SharedPtr的引用计数，weakCount是弱引用计数。

当shareCount为0时，删除T*对象。
当weakCount为0同时shareCount为0时，删除Counter*对象。
*/
class Counter
{
public:
	int shareCount = 0;
	int weakCount = 0;
};

/*

SharedPtr类
主要的成员函数包括：

默认构造函数
参数为T*的explicit单参数构造函数
参数为WeakPtr&的explicit单参数构造函数
拷贝构造函数
拷贝赋值函数
析构函数
隐式类型转换操作符 operator bool ()
operator -> ()
operator * ()
reset()
get()
use_count()

*/

template<class T> class WeakPtr;
template<class T> class SharedPtr
{
public:
	friend class WeakPtr<T>; //方便weak_ptr与share_ptr设置引用计数和赋值。

	SharedPtr()
		: m_pResource(nullptr)
		, m_pCounter(nullptr)
	{
	}

	explicit SharedPtr(T* pResource = nullptr) // 禁止隐式装换
		: m_pResource(pResource)
		, m_pCounter(nullptr)
	{
		if (m_pResource != nullptr)
		{
			m_pCounter = new Counter;
			m_pCounter->shareCount = 1;
		}
	}

	SharedPtr(const WeakPtr<T>& other) // 供WeakPtr的lock()使用
		: m_pResource(other.m_pResource)
		, m_pCounter(other.m_pCounter)
	{
		if (m_pCounter != nullptr && 0 == m_pCounter->shareCount)
		{
			m_pResource = nullptr;
		}
	}

	SharedPtr(const SharedPtr<T>& other)
		: m_pResource(other->m_pResource)
		, m_pCounter(other->m_pCounter)
	{
		if (m_pCounter != nullptr)
		{
			++(m_pCounter->shareCount); // 增加引用计数
		}
	}

	SharedPtr<T>& operator = (const SharedPtr<T>& other)
	{
		if (this == &other) return *this;

		release();
		m_pCounter = other.m_pCounter;
		m_pResource = other.m_pResource;

		if (m_pCounter != nullptr)
		{
			++(m_pCounter->shareCount); // 增加引用计数
		}

		return *this;
	}

	~SharedPtr()
	{
		release();
	}

	operator bool()
	{
		return m_pResource != nullptr;
	}

	T& operator * ()
	{
		// 如果nullptr == m_pResource，抛出异常
		return *m_pResource;
	}

	T* operator -> ()
	{
		return m_pResource;
	}

	void Reset(T* pOther = nullptr)
	{
		release();

		m_pResourse = pOther;
		if (m_pResourse != nullptr)
		{
			m_pCounter = new Counter();
			m_pCounter->shareCount = 1;
		}
	}

	T* get()
	{
		return m_pResource;
	}

	int use_count()
	{
		return (m_pCounter != nullptr) ? m_pCounter->shareCount : 0;
	}

private:
	void release()
	{
		if (nullptr == m_pCounter) return;

		// T*肯定由SharedPtr释放，Counter*如果没有WeakPtr，也由SharedPtr释放
		--m_pCounter->shareCount;

		if (0 == m_pCounter->shareCount)
		{
			delete m_pResource;
			m_pResource = nullptr;

			if (0 == m_pCounter->weakCount)
			{
				delete m_pCounter;
				m_pCounter = NULL;
			}
		}
	}

public:
	T* m_pResource = nullptr;
	Counter* m_pCounter = nullptr;
};

/*
WeakPtr类
主要的成员函数包括：

默认构造函数
参数为SharedPtr&的explicit单参数构造函数
拷贝构造函数
拷贝赋值函数
析构函数
lock()函数：取指向的SharePtr，如果未指向任何SharePtr，或者已被析构，返回指向nullptr的SharePtr
expired()函数：是否指向SharePtr，如果指向Share Ptr其是否已经析构
release()函数
*/
template<class T> class WeakPtr
{
public:
	friend class SharedPtr<T>;//方便weak_ptr与share_ptr设置引用计数和赋值。

	WeakPtr()
		: m_pResource(nullptr)
		, m_pCounter(nullptr)
	{
	}

	WeakPtr(SharedPtr<T>& other)
		: m_pResource(other.m_pResource)
		, m_pCounter(other.m_pCounter)
	{
		if (m_pCounter != nullptr)
		{
			++(m_pCounter->weakCount);
		}
	}

	WeakPtr(WeakPtr<T>& other)
		: m_pResource(other.m_pResource)
		, m_pCounter(other.m_pCounter)
	{
		if (m_pCounter != nullptr)
		{
			++(m_pCounter->weakCount);
		}
	}

	WeakPtr<T>& operator = (WeakPtr<T>& other)
	{
		if (this == &other) return *this;

		release();

		m_pCounter = other.m_pCounter;
		m_pResource = other.m_pResource;

		if (m_pCounter != nullptr)
		{
			++(m_pCounter->weakCount);
		}

		return *this;
	}

	WeakPtr<T>& operator =(SharedPtr<T>& other)
	{
		release();

		m_pCounter = other.m_pCounter;
		m_pResource = other.m_pCounter;

		if (m_pCounter != nullptr)
		{
			++(m_pCounter->weakCount);
		}

		return *this;
	}

	~WeakPtr()
	{
		release();
	}

	SharedPtr<T> lock()
	{
		return SharedPtr<T>(*this);
	}

	bool expired()
	{
		if (m_pCounter != nullptr && m_pCounter->shareCount > 0)
			return false;

		return true;
	}

private:
	void release()
	{
		if (nullptr == m_PCounter) return;

		--m_pCounter->weakCount;
		if (0 == m_pCounter->weakCount && 0 == m_pCounter->shareCount) // 必须都为0才能删除
		{
			delete m_pCounter;
			m_pCounter = NULL;
		}
	}

private:
	T* m_pResource; // 可能会成为悬挂指针 此时m_pCounter->shareCount = 0
	Counter* m_pCounter;
};


#include <memory>

int main(void) {
	auto sp = std::make_shared<int>(42);
	std::weak_ptr<int> gw = sp;
	return 0;
}
