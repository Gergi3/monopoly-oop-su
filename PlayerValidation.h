#pragma once
#include "String.h"
#include "Validation.h"

namespace PlayerValidation
{
	constexpr unsigned MIN_NAME_LEN = 1;
	constexpr unsigned MAX_NAME_LEN = 3;
	const String NAME_ERR = (String)"Name must be between " + MIN_NAME_LEN 
		+ " and " + MAX_NAME_LEN + " characters long and cannot contain whitespaces.";

	inline bool isValidName(const String& name)
	{
		return Validation::isValidLen(name, MIN_NAME_LEN, MAX_NAME_LEN)
			&& !Validation::hasWhitespaces(name);
	}
}