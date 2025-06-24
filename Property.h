#pragma once
#include "ColorGroup.h"
#include "Field.h"
#include "FieldType.h"
#include "OwnedField.h"
#include "PricedField.h"
#include "String.h"
#include "Tile.h"
#include "Vector.hpp"

class Property : public OwnedField, public PricedField
{
	ColorGroup colorGroup;
	int housePrice;
	Vector<int> rentTable;
	unsigned rentIndex;

public:
	Property(const String& name, ColorGroup colorGroup, int price, int housePrice, Vector<int> rentTable);

	FieldType getType() const override;

	void setHousePrice(int housePrice);
	int getHousePrice() const;
	int getHouseSellPrice() const;

	void setRentTable(Vector<int> rentTable);
	int getRent() const;

	void increaseRentIndex();
	void decreaseRentIndex();
	void resetRentIndex();
	unsigned getHouseLevel() const;
	 
	void setColorGroup(ColorGroup colorGroup);
	ColorGroup getColorGroup() const;

	Tile toTile() const override;
};
