#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class MoveQueue
{
	T* data;
	size_t capacity;
	size_t size;
	size_t front;
	size_t rear;

	static const size_t defaultCapacity = 8;

	void free();
	void moveFrom(MoveQueue<T>&& other);
	void resize(size_t newCapacity);

	void setCapacity(size_t newCapacity);
public:
	MoveQueue();
	MoveQueue(size_t capacity);
	MoveQueue(const MoveQueue<T>& other) = delete;
	MoveQueue(MoveQueue<T>&& other);
	MoveQueue<T>& operator=(const MoveQueue<T>& other) = delete;
	MoveQueue<T>& operator=(MoveQueue<T>&& other);
	~MoveQueue();

	void enqueue(T&& other);
	void dequeue();
	T& peek();
	T& peekBack();
	const T& peek() const;
	const T& peekBack() const;

	bool isEmpty() const;
	bool isFull() const;
	size_t getSize() const;
	size_t getCapacity() const;

	void shrinkToFit();
	void clear();

	void print() const;

	void shuffle();
};

template<typename T>
void MoveQueue<T>::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
	front = 0;
	rear = 0;
}

template<typename T>
void MoveQueue<T>::moveFrom(MoveQueue<T>&& other)
{
	front = other.front;
	rear = other.rear;
	capacity = other.capacity;
	size = other.size;
	data = other.data;
	other.data = nullptr;
}

template<typename T>
void MoveQueue<T>::resize(size_t newCapacity)
{
	if (newCapacity < size)
	{
		throw std::invalid_argument("New capacity must be greater than size!");
	}

	if (newCapacity == capacity)
	{
		return;
	}

	T* temp = new T[newCapacity];
	for (size_t i = 0; i < size; ++i)
	{
		size_t indx = (front + i) % capacity;
		temp[i] = std::move(data[indx]);
	}

	front = 0;
	rear = size - 1;
	capacity = newCapacity;

	delete[] data;
	data = temp;
}

template<typename T>
void MoveQueue<T>::setCapacity(size_t capacity)
{
	if (capacity == 0)
	{
		throw std::invalid_argument("Capacity can't be 0");
	}

	this->capacity = capacity;
}

template<typename T>
MoveQueue<T>::MoveQueue() : MoveQueue(defaultCapacity)
{}

template<typename T>
MoveQueue<T>::MoveQueue(size_t capacity)
{
	setCapacity(capacity);
	size = 0;
	front = 0;
	rear = 0;
	data = new T[capacity]{};
}

template<typename T>
MoveQueue<T>::MoveQueue(MoveQueue<T>&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
MoveQueue<T>& MoveQueue<T>::operator=(MoveQueue<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
MoveQueue<T>::~MoveQueue()
{
	free();
}

template<typename T>
void MoveQueue<T>::enqueue(T&& el)
{
	if (isFull())
	{
		resize(capacity * 2);
	}

	if (size != 0)
	{
		rear = (rear + 1) % capacity;
	}

	data[rear] = std::move(el);
	size++;
}

template<typename T>
void MoveQueue<T>::dequeue()
{
	if (isEmpty())
	{
		throw std::logic_error("Queue is empty!");
	}

	if (size == 1) // for restoring linearity
	{
		front = 0;
		rear = 0;
	}
	else
	{
		front = (front + 1) % capacity;
	}

	size--;
}

template<typename T>
T& MoveQueue<T>::peek()
{
	if (isEmpty())
	{
		throw std::logic_error("Queue is empty!");
	}

	return data[front];
}

template<typename T>
T& MoveQueue<T>::peekBack()
{
	if (isEmpty())
	{
		throw std::logic_error("Queue is empty!");
	}

	return data[rear];
}

template<typename T>
const T& MoveQueue<T>::peek() const
{
	if (isEmpty())
	{
		throw std::logic_error("Queue is empty!");
	}

	return data[front];
}

template<typename T>
const T& MoveQueue<T>::peekBack() const
{
	if (isEmpty())
	{
		throw std::logic_error("Queue is empty!");
	}

	return data[rear];
}

template<typename T>
bool MoveQueue<T>::isEmpty() const
{
	return size == 0;
}

template<typename T>
bool MoveQueue<T>::isFull() const
{
	return size == capacity;
}

template<typename T>
size_t MoveQueue<T>::getSize() const
{
	return this->size;
}

template<typename T>
size_t MoveQueue<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
void MoveQueue<T>::shrinkToFit()
{
	resize(size);
}

template<typename T>
void MoveQueue<T>::clear()
{
	size = 0;
	front = 0;
	rear = 0;
}

template<typename T>
void MoveQueue<T>::print() const
{
	if (isEmpty())
	{
		std::cout << "Queue is empty!";
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		size_t index = (front + i) % capacity;
		std::cout << data[index];
	}
}

template<typename T>
void MoveQueue<T>::shuffle()
{
	if (size <= 1)
		return;

	for (size_t i = size - 1; i > 0; --i)
	{
		size_t j = static_cast<size_t>(rand() % (i + 1));

		size_t idx_i = (front + i) % capacity;
		size_t idx_j = (front + j) % capacity;

		T temp = std::move(data[idx_i]);
		data[idx_i] = std::move(data[idx_j]);
		data[idx_j] = std::move(temp);
	}
}