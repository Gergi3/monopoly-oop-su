#pragma once
#include "String.h"

class Player;

class Card
{
protected:
	String name;
public:
	Card();
	Card(const String& name);
	virtual ~Card() = default;
	virtual void applyEffect(Player& player) const = 0;
	virtual Card* clone() const = 0;

	const String& getName() const;
};
