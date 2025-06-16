#pragma once
#include "ColorGroup.h"
#include "Field.h"
#include "String.h"
#include "Tile.h"
#include "Vector.hpp"
#include <memory>

class Player;

class Property : public Field
{
	String name;
	ColorGroup colorGroup;
	int price;
	int housePrice;
	Vector<int> rentTable;
	unsigned rentIndex;
	Player* owner;

public:
	Property(const String& name, ColorGroup colorGroup, int price, int housePrice, Vector<int> rentTable);

	FieldType getType() const override;

	void setOwner(Player* owner);
	Player* getOwner() const;

	void setPrice(int price);
	int getPrice() const;

	void setHousePrice(int housePrice);
	int getHousePrice() const;
	int getHouseSellPrice() const;

	void setRentTable(Vector<int> rentTable);
	int getRent() const;

	void setName(const String& name);
	const String& getName() const;

	void increaseRentIndex();
	void decreaseRentIndex();
	void resetRentIndex();
	unsigned getHouseLevel() const;
	 
	void setColorGroup(ColorGroup colorGroup);
	ColorGroup getColorGroup() const;

	Tile toTile() const override;
};
