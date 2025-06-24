#pragma once
#include "BoardUtilities.h"
#include "Validation.h"

namespace MovePositionToNearestCardValidation
{
	constexpr size_t MIN_POS_VALUE = 0;
	constexpr size_t MAX_POS_VALUE = BoardUtilities::ALL_FIELDS - 1;
	const String POS_ERR = String("Position must be within the board limits! [") 
		+ MIN_POS_VALUE + ", " + MAX_POS_VALUE + "]";


	inline bool isValidPosition(size_t pos)
	{
		return Validation::isInRange(pos, MIN_POS_VALUE, MAX_POS_VALUE);
	}

	inline bool areValidPositions(Vector<size_t> positions)
	{
		for (size_t i = 0; i < positions.getSize(); i++)
		{
			if (!isValidPosition(positions[i]))
			{
				return false;
			}
		}

		return true;
	}
}