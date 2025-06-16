#pragma once
#include "Card.h"
#include "MovePositionType.h"

class MovePositionCard : public Card
{
	MovePositionType type;
	unsigned spaces;
public:
	MovePositionCard(const String& name, MovePositionType type, unsigned spaces);
	void applyEffect(Player& player) const override;
};

