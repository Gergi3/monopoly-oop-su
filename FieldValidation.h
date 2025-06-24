#pragma once
#include "String.h"
#include "Validation.h"

namespace FieldValidation
{
	constexpr size_t MIN_NAME_LEN = 2;
	constexpr size_t MAX_NAME_LEN = 30;
	const String NAME_ERR = (String)"Field name must be between " + MIN_NAME_LEN
		+ " and " + MAX_NAME_LEN + '.';

	inline bool isValidName(String name)
	{
		return Validation::isInRange(name.getLen(), MIN_NAME_LEN, MAX_NAME_LEN);
	}
}