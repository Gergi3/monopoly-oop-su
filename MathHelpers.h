#pragma once
#include "Vector.hpp"

namespace MathHelpers
{
	size_t getClosestPowerOf(size_t num, size_t of);

	template<typename T>
	T sum(Vector<T> nums)
	{
		T sum = 0;
		for (size_t i = 0; i < nums.getSize(); i++)
		{
			sum += nums[i];
		}
		return sum;
	}
}