#include "StringHelpers.h"

bool StringHelpers::isDigit(char symb)
{
	return symb >= '0' && symb <= '9';
}

bool StringHelpers::isLower(char symb)
{
	return symb >= 'a' && symb <= 'z';
}

char StringHelpers::toLower(char symb)
{
	if (!isLower(symb) && isLetter(symb))
	{
		symb += 'a' - 'A';
	}

	return symb;
}

bool StringHelpers::isUpper(char symb)
{
	return symb >= 'A' && symb <= 'Z';
}

char StringHelpers::toUpper(char symb)
{
	if (!isUpper(symb) && isLetter(symb))
	{
		symb -= 'a' - 'A';
	}

	return symb;
}

bool StringHelpers::isLetter(char symb)
{
	return (isLower(symb) || isUpper(symb));
}

bool StringHelpers::isSpecialSymbol(char symb)
{
	return (symb >= '!' && symb <= '/') ||  // !"#$%&'()*+,-./
		(symb >= ':' && symb <= '@') ||  // :;<=>?@
		(symb >= '[' && symb <= '`') ||  // [\]^_`
		(symb >= '{' && symb <= '~'); // {|}~
}

bool StringHelpers::isWhitespace(char symb)
{
	return symb == ' ' || symb == '\t' || symb == '\n' ||
		symb == '\v' || symb == '\f' || symb == '\r';
}

bool StringHelpers::hasLetters(const String& str)
{
	return hasLetters(str.c_str());
}

bool StringHelpers::hasLetters(const char* str)
{
	return hasHelper(str, isLetter);
}

bool StringHelpers::hasDigits(const String& str)
{
	return hasDigits(str.c_str());
}

bool StringHelpers::hasDigits(const char* str)
{
	return hasHelper(str, isDigit);
}

bool StringHelpers::hasSymbols(const String& str)
{
	return hasSymbols(str.c_str());
}

bool StringHelpers::hasSymbols(const char* str)
{
	return hasHelper(str, isSpecialSymbol);
}

bool StringHelpers::hasWhitespaces(const char* str)
{
	return hasHelper(str, isWhitespace);
}

bool StringHelpers::hasWhitespaces(const String& str)
{
	return hasWhitespaces(str.c_str());
}

size_t StringHelpers::getWordsCount(const String& str)
{
	std::stringstream ss(str.c_str());
	size_t count = 0;
	while (ss.good())
	{
		String temp;
		ss >> temp;
		count += temp.getLen() > 0;
	}
	return count;
}
