#pragma once
#include "Field.h"

class Deck;
class Card;

class CardField : public Field
{
	Deck& deck;

public:
	CardField(const String& name, Deck& deck);

	Deck& getDeck();
	const Deck& getDeck() const;

	Tile toTile() const override;
	FieldType getType() const override;
};

