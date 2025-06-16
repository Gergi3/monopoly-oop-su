#include "Die.h"
#include <random>

Die::Die() : lastRoll(6)
{}

unsigned Die::roll() const
{
	lastRoll = (std::rand() % 6) + 1;
	return lastRoll;
}


unsigned Die::getLastRoll() const
{
	return lastRoll;
}
