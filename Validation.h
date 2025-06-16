#pragma once
#include "String.h"
#include "StringHelpers.h"

namespace Validation
{
    inline bool isValidLen(const String& str, size_t min, size_t max)
    {
        size_t len = str.getLen();
        return len >= min && len <= max;
    }

    template<typename T>
    inline bool isInRange(const T& value, const T& min, const T& max)
    {
        return value >= min && value <= max;
    }

    inline bool isNotEmpty(const String& str)
    {
        return str.getLen() != 0;
    }

    inline bool hasDigits(const String& str)
    {
		return StringHelpers::hasDigits(str);
    }

	inline bool hasWhitespaces(const String& str)
	{
		return StringHelpers::hasWhitespaces(str);
	}
}