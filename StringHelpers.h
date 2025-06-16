#pragma once
#include "String.h"
#include <cstring>
#include <memory>
#include <sstream>
#pragma warning (disable:4996)

namespace StringHelpers
{
	bool isDigit(char symb);
	bool isLower(char symb);
	char toLower(char symb);
	bool isUpper(char symb);
	char toUpper(char symb);
	bool isLetter(char symb);
	bool isSpecialSymbol(char symb);
	bool isWhitespace(char symb);
	bool hasLetters(const char* str);
	bool hasLetters(const String& str);
	bool hasDigits(const char* str);
	bool hasDigits(const String& str);
	bool hasSymbols(const char* str);
	bool hasSymbols(const String& str);
	bool hasWhitespaces(const char* str);
	bool hasWhitespaces(const String& str);
	size_t getWordsCount(const String& str);

	template<typename T>
	std::unique_ptr<char[]> toString(T value)
	{
		std::stringstream ss;
		ss << value;

		size_t len = std::strlen(ss.str().c_str());

		std::unique_ptr<char[]> buffer(new char[len + 1]);
		std::strcpy(buffer.get(), ss.str().c_str());

		return buffer;
	}

	template<typename Func>
	bool hasHelper(const char* str, Func isFunc)
	{
		if (!str)
		{
			return false;
		}

		while (*str)
		{
			if (isFunc(*str))
			{
				return true;
			}

			str++;
		}
		return false;
	}

	template<typename T>
	bool parseString(const String& str, T& out)
	{
		std::stringstream ss(str.c_str());
		return (ss >> out) && ss.eof();
	}

	template<typename T, typename ErrorType>
	void parseOrThrow(const String& str, T& out, const String& errorMessage)
	{
		if (!parseString(str, out))
		{
			throw ErrorType(errorMessage.c_str());
		}
	}

	template<typename T>
	void parseOrThrow(const String& str, T& out, const String& errorMessage)
	{
		parseOrThrow<T, std::invalid_argument>(str, out, errorMessage);
	}
}
