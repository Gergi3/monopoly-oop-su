#pragma once
#include "MathHelpers.h"
#include <iostream>
#pragma warning (disable : 4996)

class String
{
public:
	static constexpr size_t factor = 2;

	char* data;
	// Size includes '\0'
	size_t size;
	// Capacity includes '\0'
	size_t capacity;

	void free();
	void copyFrom(const String& other);
	void moveFrom(String&& other);
	void resize(size_t newCapacity);

	void setData(const char* data);

	String();
	String(char data);
	String(short data);
	String(unsigned short data);
	String(int data);
	String(unsigned int data);
	String(long data);
	String(unsigned long data);
	String(long long data);
	String(unsigned long long data);
	String(double data);
	String(float data);
	String(size_t count, char ch);
	String(const char* data);
	String(const String& other);
	String(String&& other) noexcept;
	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	~String();

	// Len does not include '\0'
	size_t getLen() const;
	// Size includes '\0'
	size_t getSize() const;
	// Capacity includes '\0'
	size_t getCapacity() const;

	const char* c_str() const;
	String toLower() const;
	String& makeLower();
	String toUpper() const;
	String& makeUpper();
	String trimmed() const;
	String& makeTrimmed();
	String paddedRight(unsigned count) const;
	// Start and end is inclusive [start, end]
	String substr(size_t start, size_t end) const;

	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);

	char& operator[](size_t indx);
	const char& operator[](size_t indx) const;

	String& operator+=(const String& other);
	String& operator+=(char ch);

	template<typename T>
	String& operator+=(T other)
	{
		String otherStr = other;
		return (*this += otherStr);
	}

	friend std::ostream& operator<<(std::ostream& os, const String& str);
	friend std::istream& operator>>(std::istream& is, String& str);
	friend bool operator>(const String& lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const String& rhs);
	friend bool operator<(const String& lhs, const String& rhs);
	friend bool operator<=(const String& lhs, const String& rhs);
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);

	// WARNING!
	// windows.h library for displaying board starts acting up (for operator+ ambiguity)
	// and since we can't use SFINAE to metaprogram T to numerics only (due to limitations of the OOP course),
	// we hack it by making operator+ for each numeric type
	// TODO: In future, make use of SFINAE
	friend String operator+(const String& lhs, const String& rhs);
	friend String operator+(const String& lhs, char rhs);
	friend String operator+(const String& lhs, int rhs);
	friend String operator+(const String& lhs, unsigned int rhs);
	friend String operator+(const String& lhs, long rhs);
	friend String operator+(const String& lhs, unsigned long rhs);
	friend String operator+(const String& lhs, long long rhs);
	friend String operator+(const String& lhs, unsigned long long rhs);
	friend String operator+(const String& lhs, float rhs);
	friend String operator+(const String& lhs, double rhs);
	friend String operator+(int lhs, const String& rhs);
	friend String operator+(unsigned int lhs, const String& rhs);
	friend String operator+(long lhs, const String& rhs);
	friend String operator+(unsigned long lhs, const String& rhs);
	friend String operator+(long long lhs, const String& rhs);
	friend String operator+(unsigned long long lhs, const String& rhs);
	friend String operator+(float lhs, const String& rhs);
	friend String operator+(double lhs, const String& rhs);
	friend String operator+(char lhs, const String& rhs);
};
