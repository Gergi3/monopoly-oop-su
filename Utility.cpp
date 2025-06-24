#include "Field.h"
#include "FieldType.h"
#include "OwnedField.h"
#include "Player.h"
#include "PricedField.h"
#include "Tile.h"
#include "Utility.h"
#include "UtilityConstants.h"


Utility::Utility(const String& name, int price)
	: Field(name), OwnedField(name), PricedField(name, price)
{}

int Utility::getRent() const
{
	if (!owner || owner->getOwnedUtilities().getSize() == 0)
	{
		return 0;
	}

	if (owner->getOwnedUtilities().getSize() == 1)
	{
		return UtilityConstants::ONE_UTIL_COEF;
	}

	return UtilityConstants::MORE_THAN_ONE_UTIL_COEF;
}

FieldType Utility::getType() const
{
	return FieldType::Utility;
}

int Utility::calculateRent(int diceRoll) const
{
	return 0;
}

Tile Utility::toTile() const
{
	Tile tile;
	tile.setColor(Color::White);
	tile.addRow(0, name);

	String secondRow = "Price: " + String(getPrice()) + "$";
	if (owner)
	{
		secondRow = String("$") + getRent() + " x dice roll";
		tile.addRow(2, "Owner: " + getOwner()->getName());
	}
	tile.addRow(1, secondRow);

	return tile;
}
