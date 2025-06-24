#include <iostream>
#include <stdexcept>

template<class T>
class Stack
{
	T* data;
	size_t size;
	size_t capacity;

	void copyFrom(const Stack<T>& other);
	void moveFrom(Stack<T>&& other);
	void free();
	void resize(size_t newCapacity);

public:
	Stack();
	Stack(size_t capacity);
	Stack(const Stack<T>& other);
	Stack(Stack<T>&& other) noexcept;
	Stack<T>& operator=(const Stack<T>& other);
	Stack<T>& operator=(Stack<T>&& other) noexcept;
	~Stack();

	void push(const T& elem);
	void push(T&& elem);
	void pop();
	const T& top() const;

	bool isEmpty() const;
	size_t getSize() const;
};

template<class T>
void Stack<T>::copyFrom(const Stack<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity]{};
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

template<class T>
void Stack<T>::moveFrom(Stack<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
}

template<class T>
void Stack<T>::free()
{
	delete[] data;
	size = 0;
	capacity = 0;
}

template<class T>
void Stack<T>::resize(size_t newCapacity)
{
	if (newCapacity < size)
	{
		throw std::invalid_argument("Invalid new capacity!");
	}

	if (newCapacity == capacity)
	{
		return;
	}

	T* temp = new T[newCapacity]{};
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = std::move(data[i]);
	}
	delete[] data;
	capacity = newCapacity;
	data = temp;
}

template<class T>
Stack<T>::Stack() : Stack(8)
{}

template<class T>
Stack<T>::Stack(size_t capacity)
{
	this->capacity = capacity == 0 ? 1 : capacity;
	size = 0;
	data = new T[capacity]{};
}

template<class T>
Stack<T>::Stack(const Stack<T>& other)
{

}

template<class T>
Stack<T>::Stack(Stack<T>&& other) noexcept
{

}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
}

template<class T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
{
}

template<class T>
Stack<T>::~Stack()
{}

template<class T>
void Stack<T>::push(const T& elem)
{}

template<class T>
void Stack<T>::push(T&& elem)
{}

template<class T>
void Stack<T>::pop()
{}

template<class T>
const T& Stack<T>::top() const
{
}

template<class T>
bool Stack<T>::isEmpty() const
{
	return false;
}

template<class T>
size_t Stack<T>::getSize() const
{
	return size_t();
}
