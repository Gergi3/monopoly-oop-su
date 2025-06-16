#include "MathHelpers.h"

size_t MathHelpers::getClosestPowerOf(size_t num, size_t of)
{
	size_t pow = 1;
	while (num > pow)
	{
		pow *= of;
	}
	return pow;
}