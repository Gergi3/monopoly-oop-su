#include "BoardUtilities.h"
#include "Card.h"
#include "MovePositionCard.h"
#include "MovePositionToNearestCard.h"
#include "MovePositionToNearestCardValidation.h"
#include "MovePositionType.h"
#include "Player.h"
#include "String.h"
#include "Vector.hpp"
#include <stdexcept>

using namespace MovePositionToNearestCardValidation;

void MovePositionToNearestCard::setPositions(const Vector<size_t>& positions)
{
	if (!areValidPositions(positions))
	{
		throw std::invalid_argument(POS_ERR.c_str());
	}

	this->positions = positions;
}

MovePositionToNearestCard::MovePositionToNearestCard(const String& name, const Vector<size_t>& positions)
	: MovePositionCard(name, MovePositionType::Goto, 0)
{
	setPositions(positions);
}

void MovePositionToNearestCard::applyEffect(Player& player) const
{
	size_t closest = 0;
	size_t minDiff = BoardUtilities::ALL_FIELDS;
	for (size_t i = 0; i < positions.getSize(); i++)
	{
		long long difference = positions[i] - (long long)player.getBoardPos();
		if (difference >= 0 && difference < minDiff)
		{
			minDiff = difference;
			closest = positions[i];
		}
	}

	spaces = closest;
	MovePositionCard::applyEffect(player);
}

Card* MovePositionToNearestCard::clone() const
{
	return new MovePositionToNearestCard(*this);
}
