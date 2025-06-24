#include "OwnedField.h"
#include "Player.h"


OwnedField::OwnedField(const String& name) : Field(name), owner(nullptr)
{
}

void OwnedField::setOwner(Player* owner)
{
	this->owner = owner;
}

Player* OwnedField::getOwner() const
{
	return owner;
}
