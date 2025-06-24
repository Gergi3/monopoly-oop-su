#pragma once
#include "ColorGroup.h"
#include "Railroad.h"
#include "String.h"
#include "Typedefs.h"
#include "Utility.h"
#include "Vector.hpp"
#include <iostream>

class Bank;
class Board;

class Player
{
	static int defaultCreated;

	String name;
	int money;
	size_t boardPos;
	MutableProperties ownedProperties;
	Vector<Railroad*> ownedRailroads;
	Vector<Utility*> ownedUtilities;
	bool eliminated;
	bool isJailed;
	unsigned jailPasses;
	unsigned turnsInJail;
	unsigned diceRoll;

	void transferUtilityOwnership(Utility& utility, Player& buyer);
	void transferRailroadOwnership(Railroad& railroad, Player& buyer);
	void transferPropertyOwnership(Property& property, Player& buyer);

	MutableProperties getOwnedPropertiesByColor(ColorGroup color) const;
	void ensureCanBuildHouseOn(const Property& property) const;
	void ensureCanDemolishHouseOn(const Property& property) const;
	void ensureIsOwnerOf(const OwnedField& ownedField) const;

	bool hasFullColorGroup(ColorGroup colorGroup, const Properties& gameProperties) const;
	bool colorGroupHasHouses(ColorGroup colorGroup, const Properties& gameProperties) const;
	bool isRentableField(const Field& field) const;

public:
	Player();
	Player(const String& name, int money, size_t boardPos);

	MutableProperties& getOwnedProperties();
	const MutableProperties& getOwnedProperties()const;
	
	Vector<Railroad*>& getOwnedRailroads();
	const Vector<Railroad*>& getOwnedRailroads() const;

	Vector<Utility*>& getOwnedUtilities();
	const Vector<Utility*>& getOwnedUtilities() const;

	void setName(const String& name);
	const String& getName() const;

	void setDiceRoll(unsigned roll);
	unsigned getDiceRoll() const;

	void addMoney(int money);
	void setMoney(int money);
	int getMoney() const;

	void eliminate();
	bool isEliminated();

	void putInJail();
	bool isInJail() const;
	void freeFromJail();

	unsigned getJailPassesCount() const;
	void decrementJailPasses();
	void incrementJailPasses();

	void incrementTurnsInJail();
	unsigned getTurnsInJailCount() const;

	bool isEliminated() const;
	bool isBankrupt() const;

	void setBoardPos(size_t pos);
	size_t getBoardPos() const;

	void buyField(Field& field, const Bank& bank);
	void payRentTo(const Field& field, const Bank& bank);
	
	void buyUtility(Utility& railroad, const Bank& bank);
	void sellUtilityTo(Utility& railroad, Player& buyer, int price, Bank& bank);
	void ensureCanSellUtilityTo(
		Utility& railroad,
		Player& buyer,
		int price);

	void buyRailroad(Railroad& railroad, const Bank& bank);
	void sellRailroadTo(Railroad& railroad, Player& buyer, int price, Bank& bank);
	void ensureCanSellRailroadTo(
		Railroad& railroad,
		Player& buyer,
		int price);

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

	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is, Board& board);
};