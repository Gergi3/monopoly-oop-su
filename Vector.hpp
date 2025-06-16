#pragma once
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility> // std::move

template<typename T>
class Vector
{
	static const size_t factor = 2;

	T* data;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);
	void resize();
	void resize(size_t newCapacity);

public:
	Vector();
	Vector(size_t size);
	Vector(size_t size, const T& rhs);
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other) noexcept;
	~Vector();

	void push_back(const T& rhs);
	void push_back(T&& rhs);
	void pop_back();

	void insert(size_t indx, const T& rhs);
	void insert(size_t indx, T&& rhs);
	void removeAt(size_t indx);
	bool remove(const T& value);
	bool contains(const T& value) const;

	template<typename Predicate>
	size_t countBy(Predicate func) const;

	template <typename Predicate>
	Vector<T> filterBy(Predicate func) const;
	 
	template<typename Predicate>
	T maxBy(Predicate func) const;

	template<typename Predicate>
	T minBy(Predicate func) const;

	template<typename Predicate>
	bool anyBy(Predicate func) const;

	void shrink_to_fit();
	void clear();

	const T& operator[](size_t indx) const;
	T& operator[](size_t indx);
	T* begin();
	T* end();
	const T* begin() const;
	const T* end() const;
	bool isEmpty() const;
	size_t getSize() const;
	size_t getCapacity() const;
};

template<typename T>
void Vector<T>::free()
{
	delete[] data;
	size = 0;
	capacity = 0;
}

template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity]{};
	for (size_t i = 0; i < capacity; i++)
	{
		data[i] = other.data[i];
	}
}

template<typename T>
void Vector<T>::moveFrom(Vector<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
}

template<typename T>
void Vector<T>::resize()
{
	resize(capacity == 0 ? 1 : capacity * factor);
}

template<typename T>
void Vector<T>::resize(size_t newCapacity)
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

template<typename T>
Vector<T>::Vector() : Vector(0)
{}

template<typename T>
Vector<T>::Vector(size_t n)
{
	capacity = n;
	size = n;
	data = new T[capacity];
	for (size_t i = 0; i < n; i++)
	{
		data[i] = T();
	}
}

template<typename T>
Vector<T>::Vector(size_t n, const T& rhs)
{
	capacity = n;
	size = n;
	data = new T[capacity];
	for (size_t i = 0; i < n; i++)
	{
		data[i] = rhs;
	}
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	free();
}

template<typename T>
void Vector<T>::push_back(const T& rhs)
{
	if (size == capacity)
	{
		resize();
	}

	data[size++] = rhs;
}

template<typename T>
void Vector<T>::push_back(T&& rhs)
{
	if (size == capacity)
	{
		resize();
	}

	data[size++] = std::move(rhs);
}

template<typename T>
void Vector<T>::pop_back()
{
	if (isEmpty())
	{
		throw std::logic_error("Array is empty!");
	}

	size--;
}

template<typename T>
void Vector<T>::insert(size_t indx, const T& rhs)
{
	if (indx > size)
	{
		throw std::out_of_range("Given index is out of the bounds of the vector");
	}

	if (size == capacity)
	{
		resize();
	}

	for (size_t i = size; i > indx; i--)
	{
		data[i] = std::move(data[i - 1]);
	}
	data[indx] = rhs;
	size++;
}

template<typename T>
void Vector<T>::insert(size_t indx, T&& rhs)
{
	if (indx >= size)
	{
		throw std::out_of_range("Given index is out of the bounds of the vector");
	}

	if (size == capacity)
	{
		resize();
	}

	for (size_t i = size; i > indx; i--)
	{
		data[i] = std::move(data[i - 1]);
	}
	data[indx] = std::move(rhs);
	size++;
}

template<typename T>
void Vector<T>::removeAt(size_t indx)
{
	if (indx >= size)
	{
		throw std::out_of_range("Given index is out of the bounds of the vector");
	}

	for (size_t i = indx; i < size - 1; i++)
	{
		data[i] = std::move(data[i + 1]);
	}

	size--;
}

template<typename T>
bool Vector<T>::remove(const T& value)
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == value)
		{
			removeAt(i);
			return true;
		}
	}
	return false;
}

template<typename T>
bool Vector<T>::contains(const T& value) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == value)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
void Vector<T>::shrink_to_fit()
{
	resize(size);
}

template<typename T>
void Vector<T>::clear()
{
	size = 0;
}

template<typename T>
const T& Vector<T>::operator[](size_t indx) const
{
	if (indx >= size)
	{
		throw std::out_of_range("Index out of range!");
	}

	return data[indx];
}

template<typename T>
T& Vector<T>::operator[](size_t indx)
{
	if (indx >= size)
	{
		throw std::out_of_range("Index out of range!");
	}

	return data[indx];
}

template<typename T>
T* Vector<T>::begin()
{
	return data;
}

template<typename T>
T* Vector<T>::end()
{
	return data + size;
}

template<typename T>
const T* Vector<T>::begin() const
{
	return data;
}

template<typename T>
const T* Vector<T>::end() const
{
	return data + size;
}

template<typename T>
bool Vector<T>::isEmpty() const
{
	return size == 0;
}

template<typename T>
size_t Vector<T>::getSize() const
{
	return size;
}

template<typename T>
size_t Vector<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
template<typename Predicate>
size_t Vector<T>::countBy(Predicate func) const
{
	size_t count = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (func(data[i]))
		{
			count++;
		}
	}
	return count;
}

template<typename T>
template<typename Predicate>
Vector<T> Vector<T>::filterBy(Predicate func) const
{
	Vector<T> result;
	for (size_t i = 0; i < size; i++)
	{
		if (func(data[i]))
		{
			result.push_back(data[i]);
		}
	}
	return result;
}

template<typename T>
template<typename Predicate>
T Vector<T>::maxBy(Predicate func) const
{
	if (isEmpty())
	{
		throw std::logic_error("Cannot find max in an empty vector.");
	}

	T max = data[0];
	for (size_t i = 1; i < size; i++)
	{
		if (func(data[i]) > func(max))
		{
			max = data[i];
		}
	}
	return max;
}

template<typename T>
template<typename Predicate>
T Vector<T>::minBy(Predicate func) const
{
	if (isEmpty())
	{
		throw std::logic_error("Cannot find min in an empty vector.");
	}

	T min = data[0];
	for (size_t i = 1; i < size; i++)
	{
		if (func(data[i]) < func(min))
		{
			min = data[i];
		}
	}
	return min;
}

template<typename T>
template<typename Predicate>
bool Vector<T>::anyBy(Predicate func) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (func(data[i]))
		{
			return true;
		}
	}
	return false;
}
