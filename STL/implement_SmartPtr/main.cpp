
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


int main(void) {
	
	return 0;
}
