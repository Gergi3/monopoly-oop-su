#include "ColorGroup.h"
#include "String.h"
#include "Typedefs.h"
#include "Vector.hpp"

class Property;
class Bank;

class Player
{
	static int defaultCreated;

	String name;
	int money;
	size_t boardPos;
	MutableProperties ownedProperties;
	bool eliminated;

	void transferPropertyOwnership(Property& property, Player& buyer);
	MutableProperties getOwnedPropertiesByColor(ColorGroup color) const;
	void ensureCanBuildHouseOn(const Property& property) const;
	void ensureCanDemolishHouseOn(const Property& property) const;
	void ensureIsOwnerOf(const Property& property) const;

	bool hasFullColorGroup(ColorGroup colorGroup, const Properties& gameProperties) const;
	bool colorGroupHasHouses(ColorGroup colorGroup, const Properties& gameProperties) const;

public:
	Player();
	Player(const String& name, int money, size_t boardPos);

	MutableProperties& getOwnedProperties();

	void setName(const String& name);
	const String& getName() const;

	void addMoney(int money);
	void setMoney(int money);
	int getMoney() const;

	bool isEliminated() const;
	bool isBankrupt() const;

	void setBoardPos(size_t pos);
	size_t getBoardPos() const;

	void payRentTo(const Property& property, const Bank& bank);
	void buildHouseOn(Property& property, const Properties& gameProperties, const Bank& bank);
	void demolishHouseOn(Property& property, const Bank& bank);
	void buyProperty(Property& property, const Bank& bank);
	void ensureCanSellPropertyTo(
		Property& property,
		Player& buyer,
		int price,
		const Properties& gameProperties);
	void sellPropertyTo(
		Property& property,
		Player& buyer,
		int price,
		const Properties& gameProperties,
		const Bank& bank);
};