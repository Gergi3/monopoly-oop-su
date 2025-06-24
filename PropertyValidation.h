#pragma once
#include "Validation.h"

namespace PropertyValidation
{
	constexpr int MIN_RENT = 0;
	constexpr int MAX_RENT = 5000;
	const String RENT_ERR = (String)"Rent table values must be between " + MIN_RENT
		+ " and " + MAX_RENT + '.';

	inline bool isValidRentTable(const Vector<int>& rentTable)
	{
		for (size_t i = 0; i < rentTable.getSize(); i++)
		{
			if (!Validation::isInRange(rentTable[i], MIN_RENT, MAX_RENT))
			{
				return false;
			}
		}
		return true;
	}

	constexpr unsigned MAX_RENTS_COUNT = 6;
	const String RENTS_COUNT_ERR = (String)"Rent table size must be " + MAX_RENTS_COUNT + '.';

	inline bool isValidRentTableSize(const Vector<int>& rentTable)
	{
		return rentTable.getSize() == MAX_RENTS_COUNT;
	}

	constexpr int MIN_HOUSE_PRICE = 0;
	constexpr int MAX_HOUSE_PRICE = 1000;
	const String HOUSE_PRICE_ERR = (String)"House price must be between " + MIN_HOUSE_PRICE
		+ " and " + MAX_HOUSE_PRICE + '.';

	inline bool isValidHousePrice(int housePrice)
	{
		return Validation::isInRange(housePrice, MIN_HOUSE_PRICE, MAX_HOUSE_PRICE);
	}


}