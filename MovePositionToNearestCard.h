#pragma once
#include "MovePositionCard.h"

class MovePositionToNearestCard : public MovePositionCard
{
protected:
	Vector<size_t> positions;

	void setPositions(const Vector<size_t>& positions);
public:
	MovePositionToNearestCard(const String& name, const Vector<size_t>& positions);
	
	void applyEffect(Player& player) const override;
	Card* clone() const override;
};
