#include "Color.h"
#include "ColorGroup.h"
#include "Player.h"
#include "Property.h"
#include "PropertyConstants.h"
#include "PropertyValidation.h"
#include "StringHelpers.h"
#include "Tile.h"
#include "Vector.hpp"

Property::Property(const String& name, ColorGroup colorGroup, int price, int housePrice, Vector<int> rentTable)
{
	setName(name);
	this->colorGroup = colorGroup;
	setPrice(price);
	setHousePrice(housePrice);
	setRentTable(rentTable);
}

void Property::setOwner(Player* owner)
{
	this->owner = owner;
}

Player* Property::getOwner() const
{
	return owner;
}

void Property::setPrice(int price)
{
	if (!PropertyValidation::isValidPrice(price))
	{
		throw std::invalid_argument(PropertyValidation::PRICE_ERR.c_str());
	}

	this->price = price;
}

int Property::getPrice() const
{
	return price;
}

void Property::setHousePrice(int housePrice)
{
	if (!PropertyValidation::isValidHousePrice(housePrice))
	{
		throw std::invalid_argument(PropertyValidation::HOUSE_PRICE_ERR.c_str());
	}

	this->housePrice = housePrice;
}

int Property::getHousePrice() const
{
	return housePrice;
}

int Property::getHouseSellPrice() const
{
	return housePrice / 2;
}

void Property::setRentTable(Vector<int> rentTable)
{
	if (!PropertyValidation::isValidRentTableSize(rentTable))
	{
		throw std::invalid_argument(PropertyValidation::RENTS_COUNT_ERR.c_str());
	}

	if (!PropertyValidation::isValidRentTable(rentTable))
	{
		throw std::invalid_argument(PropertyValidation::RENT_ERR.c_str());
	}

	this->rentTable = rentTable;
	rentIndex = 0;
}

int Property::getRent() const
{
	return rentTable[rentIndex];
}

void Property::setName(const String& name)
{
	if (!PropertyValidation::isValidName(name))
	{
		throw std::invalid_argument(PropertyValidation::NAME_ERR.c_str());
	}

	this->name = name;
}

const String& Property::getName() const
{
	return name;
}

void Property::increaseRentIndex()
{
	rentIndex++;
}

void Property::decreaseRentIndex()
{
	rentIndex--;
}

void Property::resetRentIndex()
{
	rentIndex = 0;
}

unsigned Property::getHouseLevel() const
{
	return rentIndex;
}

void Property::setColorGroup(ColorGroup colorGroup)
{
	this->colorGroup = colorGroup;
}

ColorGroup Property::getColorGroup() const
{
	return colorGroup;
}

Tile Property::toTile() const
{
	Tile tile;
	tile.setColor((Color)colorGroup);
	tile.addRow(0, name);

	String secondRow = "Price: " + String(getPrice()) + "$";
	if (owner)
	{
		secondRow = String(getRent()) + "$  Owner: " + getOwner()->getName();
	}
	tile.addRow(1, secondRow);

	String housesRow;
	for (size_t i = 0; i < rentIndex; i++)
	{
		housesRow += (i + 1) != PropertyValidation::MAX_RENTS_COUNT - 1 ? '\x7F' : '\xBA';
		housesRow += ' ';
	}
	tile.addRow(2, housesRow);

	return tile;
}

FieldType Property::getType() const
{
	return FieldType::Property;
}
