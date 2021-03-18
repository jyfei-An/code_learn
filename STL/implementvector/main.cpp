template <typename T>
class MyVector
{
public:

	typedef T * iterator;

	//无参构造函数
	MyVector()
	{
		my_capacity = 0;
		my_size = 0;
		buffer = nullptr;
	}

	MyVector(size_t size)
	{
		my_capacity = size;
		my_size = size;
		buffer = new T[size];
	}
	MyVector(size_t size, const T & initial)
	{
		my_size = size;
		my_capacity = size;
		buffer = new T[size];
		for (size_t i = 0; i < size; ++i)
			buffer[i] = initial;
	}
	//拷贝构造函数
	MyVector(const MyVector<T> & v)
	{
		my_size = v.my_size;
		my_capacity = v.my_capacity;
		buffer = new T[my_size];
		for (size_t i = 0; i < my_size; ++i)
			buffer[i] = v.buffer[i];
	}

	MyVector&operator=(const MyVector<T> & v)
	{
		if (&that != this)
		{
			delete[] buffer;
			my_size = v.my_size;
			my_capacity = v.my_capacity;
			buffer = new T[my_size];

			for (size_t i = 0; i < my_size; ++i)
				buffer[i] = v.buffer[i];
		}
		return *this;
	}

	//析构函数
	~MyVector()
	{
		if (buffer)
		{
			delete[] buffer;
			buffer = nullptr;
		}

	}

	size_t size()const
	{
		return my_size;
	}

	size_t capacity()const
	{
		return my_capacity;
	}


	iterator begin()
	{
		return buffer;
	}

	iterator end()
	{
		return buffer + size();
	}

	T & front()
	{
		return buffer[0];
	}

	T & back()
	{
		return buffer[my_size - 1];
	}

	void push_back(const T & value)
	{
		if (my_size == my_capacity) {
			T* temp = new T[2 * my_capacity];

			// copying old array elements to new array
			for (int i = 0; i < my_capacity; i++) {
				temp[i] = buffer[i];
			}

			// deleting previous array
			delete[] buffer;
			capacity *= 2;
			buffer = temp;
		}

		// Inserting data
		arr[my_size] = data;
		my_size++;

	}


	// function to add element at any index
	void push(int data, int index)
	{
		// if index is equal to capacity then this
		// function is same as push defined above
		if (index == capacity)
			push(data);
		else
			arr[index] = data;
	}


	void pop_back()
	{
		my_size--;
	}

private:
	//arr指向分配的内存
	T* buffer;

	//capacity为vector的容量
	size_t my_capacity;

	//current是元素的数量
	size_t my_size;
};


int main(void) {
	
	return 0;
}
