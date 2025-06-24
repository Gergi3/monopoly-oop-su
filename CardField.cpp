#include "CardField.h"

CardField::CardField(const String& name, Deck& deck)
	: Field(name), deck(deck)
{}

Deck& CardField::getDeck()
{
	return deck;
}

const Deck& CardField::getDeck() const
{
	return deck;
}

Tile CardField::toTile() const
{
	Tile tile;
	tile.addRow(0, name);
	return tile;
}

FieldType CardField::getType() const
{
	return FieldType::CardField;
}
