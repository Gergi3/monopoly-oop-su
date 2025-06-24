#include "Card.h"
#include "String.h"

Card::Card() : Card("Card")
{}

Card::Card(const String& name) : name(name)
{}

const String& Card::getName() const
{
	return name;
}
