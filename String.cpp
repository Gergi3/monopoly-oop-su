#include "MathHelpers.h"
#include "String.h"
#include "StringHelpers.h"
#include <cstring>
#include <stdexcept>
#pragma warning (disable : 4996)

void String::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
}

void String::copyFrom(const String& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new char[capacity] {};
	strcpy(data, other.data);
}

void String::moveFrom(String&& other)
{
	data = other.data;
	size = other.size;
	capacity = other.capacity;
	other.data = nullptr;
}

void String::resize(size_t newCapacity)
{
	if (newCapacity < size)
	{
		throw std::invalid_argument("New capacity must be bigger than size!");
	}

	if (newCapacity == capacity)
	{
		return;
	}

	char* temp = new char[newCapacity] {};
	strcpy(temp, data);

	delete[] data;
	capacity = newCapacity;
	data = temp;
}

void String::setData(const char* data)
{
	if (!data)
	{
		data = "";
	}

	size = strlen(data) + 1;
	capacity = MathHelpers::getClosestPowerOf(size, factor);

	this->data = new char[capacity] {};
	strcpy(this->data, data);
}

String::String() : String("")
{}

String::String(char data)
{
	capacity = 2;
	size = 2;
	this->data = new char[capacity] {};
	this->data[0] = data;
}

String::String(short data)
	: String(StringHelpers::toString(data).get())
{}

String::String(unsigned short data)
	: String(StringHelpers::toString(data).get())
{}

String::String(int data)
	: String(StringHelpers::toString(data).get())
{}

String::String(unsigned int data)
	: String(StringHelpers::toString(data).get())
{}

String::String(long data)
	: String(StringHelpers::toString(data).get())
{}

String::String(unsigned long data)
	: String(StringHelpers::toString(data).get())
{}

String::String(unsigned long long data)
	: String(StringHelpers::toString(data).get())
{}

String::String(double data)
	: String(StringHelpers::toString(data).get())
{}

String::String(float data)
	: String(StringHelpers::toString(data).get())
{}

String::String(size_t count, char ch)
{
	char* temp = new char[count + 1] {};
	for (size_t i = 0; i < count; i++)
	{
		temp[i] = ch;
	}
	try
	{
		setData(temp);
		delete[] temp;
	}
	catch (...)
	{
		delete[] temp;
		throw;
	}
}

String::String(long long data)
	: String(StringHelpers::toString(data).get())
{}

String::String(const char* data)
{
	setData(data);
}

String::String(const String& other)
{
	copyFrom(other);
}

String::String(String&& other) noexcept
{
	moveFrom(std::move(other));
}

String& String::operator=(const String& other)
{
	if (&other != this)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

String& String::operator=(String&& other) noexcept
{
	if (&other != this)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

String::~String()
{
	free();
}

size_t String::getLen() const
{
	return size - 1;
}

size_t String::getSize() const
{
	return size;
}

size_t String::getCapacity() const
{
	return capacity;
}

const char* String::c_str() const
{
	return data;
}

String String::toLower() const
{
	String result = *this;
	return result.makeLower();
}

String& String::makeLower()
{
	for (size_t i = 0; i < size; i++)
	{
		data[i] = StringHelpers::toLower(data[i]);
	}

	return *this;
}

String String::toUpper() const
{
	String result = *this;
	return result.makeUpper();
}

String& String::makeUpper()
{
	for (size_t i = 0; i < size; i++)
	{
		data[i] = StringHelpers::toUpper(data[i]);
	}

	return *this;
}

String String::trimmed() const
{
	String result = *this;
	return result.makeTrimmed();
}

String& String::makeTrimmed()
{
	size_t start = 0;
	size_t end = getLen();

	while (start < end && StringHelpers::isWhitespace((*this)[start]))
	{
		++start;
	}

	while (end > start && StringHelpers::isWhitespace((*this)[end - 1]))
	{
		--end;
	}

	*this = substr(start, end);
	return *this;
}

String String::paddedRight(unsigned count) const
{
	if (getLen() >= count)
	{
		return substr(0, count);
	}

	return *this + String(count - getLen(), ' ');
}

String String::substr(size_t start, size_t end) const
{
	if (start > end || end > size - 1)
	{
		throw std::out_of_range("Out of bounds start and/or end indices!");
	}

	String result;
	for (size_t i = start; i < end; i++)
	{
		result += data[i];
	}

	return result;
}

char& String::operator[](size_t indx)
{
	if (indx > size)
	{
		throw std::out_of_range("Index out of range!");
	}

	return data[indx];
}

const char& String::operator[](size_t indx) const
{
	if (indx > size)
	{
		throw std::out_of_range("Index out of range!");
	}

	return data[indx];
}

String& String::operator+=(const String& other)
{
	if (other.getLen() == 0)
	{
		return *this;
	}

	size_t newSize = size + other.size - 1;
	if (newSize > capacity)
	{
		resize(MathHelpers::getClosestPowerOf(newSize, factor));
	}

	// + size - 1 optimizes strcat for appending to bigger strings
	// by reducing searching for '\0' from O(n) to O(1)
	strcat(data + size - 1, other.data);
	size = newSize;
	return *this;
}

String& String::operator+=(char ch)
{
	size_t newSize = size + 1;
	if (size == capacity)
	{
		resize(MathHelpers::getClosestPowerOf(newSize, factor));
	}

	data[size - 1] = ch;
	data[size++] = '\0';

	return *this;
}

void String::serialize(std::ostream& os) const
{
	os.write((const char*)&size, sizeof(size));
	os.write((const char*)&capacity, sizeof(capacity));
	os.write((const char*)data, size - 1);
}

void String::deserialize(std::istream& is)
{
	free();

	is.read((char*)&size, sizeof(size));
	is.read((char*)&capacity, sizeof(capacity));
	data = new char[capacity] {};
	is.read(data, size - 1);
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.data;
	return os;
}

std::istream& operator>>(std::istream& is, String& str)
{
	str = "";
	is >> std::ws;

	char current;
	while (is.get(current) && !StringHelpers::isWhitespace(current))
	{
		str += current;
	}

	return is;
}

bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator<(const String& lhs, const String& rhs)
{
	return !(lhs >= rhs);
}

bool operator<=(const String& lhs, const String& rhs)
{
	return !(lhs > rhs);
}

bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}

String operator+(const String& lhs, const String& rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(const String& lhs, char rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(const String& lhs, int rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(const String& lhs, unsigned int rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(const String& lhs, long rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(const String& lhs, unsigned long rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(const String& lhs, long long rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(const String& lhs, unsigned long long rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(const String& lhs, float rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(const String& lhs, double rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(int lhs, const String& rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(unsigned int lhs, const String& rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(long lhs, const String& rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(unsigned long lhs, const String& rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(long long lhs, const String& rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(unsigned long long lhs, const String& rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(float lhs, const String& rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(double lhs, const String& rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}

String operator+(char lhs, const String& rhs)
{
	String cpy = lhs;
	return (cpy += rhs);
}
