#include "Player.h"
#include "MathHelpers.h"
#include "Railroad.h"

Railroad::Railroad(const String& name, int price)
	: Field(name), OwnedField(name), PricedField(name, price)
{}

int Railroad::getRent() const
{
	if (!owner)
	{
		return 0;
	}

	int factor = MathHelpers::getClosestPowerOf(owner->getOwnedRailroads().getSize(), 2);
	return RailroadConstants::BASE_RENT * factor;
}

FieldType Railroad::getType() const
{
	return FieldType::Railroad;
}

Tile Railroad::toTile() const
{
	Tile tile;
	tile.setColor(Color::Gray);
	tile.addRow(0, name);

	String secondRow = "Price: " + String(getPrice()) + "$";
	if (owner)
	{
		secondRow = String(getRent()) + "$  Owner: " + getOwner()->getName();
	}
	tile.addRow(1, secondRow);

	return tile;
}
