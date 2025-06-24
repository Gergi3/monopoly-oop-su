#pragma once
#include "String.h"
#include "Validation.h"

namespace PaymentCardValidation
{
	constexpr int MIN_AMOUNT = 0;
	constexpr int MAX_AMOUNT = 99'999;
	const String AMOUNT_ERR = String("Money for payment card must be over ") + MIN_AMOUNT
		+ " and under " + MAX_AMOUNT;

	inline bool isValidAmount(int amount)
	{
		return Validation::isInRange(amount, MIN_AMOUNT, MAX_AMOUNT);
	}
}