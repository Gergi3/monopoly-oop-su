#pragma once
#include "String.h"
#include "Validation.h"

namespace BankValidation
{
	constexpr int MIN_AMOUNT = 0;
	const String AMOUNT_ERR = String("Money must be over ") + MIN_AMOUNT;

	inline bool isValidAmount(int amount)
	{
		return amount > MIN_AMOUNT;
	}
}