#pragma once
#include "String.h"
#include "Validation.h"

namespace PricedFieldValidation
{
	constexpr int MIN_PRICE = 0;
	constexpr int MAX_PRICE = 500;
	const String PRICE_ERR = (String)"Field price must be between " + MIN_PRICE
		+ " and " + MAX_PRICE + '.';

	inline bool isValidPrice(int price)
	{
		return Validation::isInRange(price, MIN_PRICE, MAX_PRICE);
	}
}