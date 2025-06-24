#pragma once
#include "Card.h"
#include "MovePositionType.h"

class MovePositionCard : public Card
{
protected:
	MovePositionType type;
	mutable size_t spaces;

public:
	MovePositionCard(const String& name, MovePositionType type, size_t spaces);
	virtual ~MovePositionCard() = default;

	void applyEffect(Player& player) const override;
	Card* clone() const override;
};
