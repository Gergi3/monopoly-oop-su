#pragma once
#include "Player.h"

class Card
{
	String name;
public:
	Card(const String& name);
	virtual void applyEffect(Player& player) const = 0;

	String getName() const;
};

