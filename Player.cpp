#include "Bank.h"
#include "Board.h"
#include "ColorGroup.h"
#include "FieldType.h"
#include "GameEngineConstants.h"
#include "Player.h"
#include "PlayerConstants.h"
#include "PlayerValidation.h"
#include "Property.h"
#include "PropertyValidation.h"
#include "RailroadConstants.h"
#include "String.h"
#include "Typedefs.h"
#include <stdexcept>

using namespace PlayerConstants;

void Player::ensureIsOwnerOf(const OwnedField& ownedField) const
{
	Player* owner = ownedField.getOwner();
	if (owner != this)
	{
		String msg = String(NOT_OWNER_ERR) + FieldTypeHelpers::getFieldTypeStr(ownedField.getType()) + "!";
		throw std::invalid_argument(msg.c_str());
	}
}

void Player::transferUtilityOwnership(Utility& utility, Player& buyer)
{
	ensureIsOwnerOf(utility);
	utility.setOwner(&buyer);
	ownedUtilities.remove(&utility);
	buyer.ownedUtilities.push_back(&utility);
}

void Player::transferRailroadOwnership(Railroad& railroad, Player& buyer)
{
	ensureIsOwnerOf(railroad);
	railroad.setOwner(&buyer);
	ownedRailroads.remove(&railroad);
	buyer.ownedRailroads.push_back(&railroad);
}

void Player::transferPropertyOwnership(Property& property, Player& buyer)
{
	ensureIsOwnerOf(property);
	property.setOwner(&buyer);
	ownedProperties.remove(&property);
	buyer.ownedProperties.push_back(&property);
}

MutableProperties Player::getOwnedPropertiesByColor(ColorGroup color) const
{
	return ownedProperties
		.filterBy([color](Property* prop) { return prop->getColorGroup() == color; });
}

void Player::ensureCanBuildHouseOn(const Property& property) const
{
	size_t minHouseLevel = this
		->getOwnedPropertiesByColor(property.getColorGroup())
		.minBy([](Property* prop) { return prop->getHouseLevel(); })
		->getHouseLevel();

	if (property.getHouseLevel() == PropertyValidation::MAX_RENTS_COUNT - 1)
	{
		throw std::invalid_argument(MAXIMUM_HOUSES_REACHED_ERR);
	}

	if (property.getHouseLevel() != minHouseLevel)
	{
		throw std::logic_error(CANT_BUILD_HOUSE_ERR);
	}
}

void Player::ensureCanDemolishHouseOn(const Property& property) const
{
	size_t maxHouseLevel = this
		->getOwnedPropertiesByColor(property.getColorGroup())
		.maxBy([](Property* prop) { return prop->getHouseLevel(); })
		->getHouseLevel();

	if (property.getHouseLevel() == 0)
	{
		throw std::logic_error(NO_HOUSES_TO_DEMOLISH_ERR);
	}

	if (property.getHouseLevel() != maxHouseLevel)
	{
		throw std::logic_error(CANT_DEMOLISH_HOUSE_ERR);
	}
}

int Player::defaultCreated = 1;

Player::Player() : Player(String("P") + defaultCreated, 0.0, 0)
{
	defaultCreated++;
}

Player::Player(const String& name, int money, size_t boardPos)
	: eliminated(false), isJailed(false), jailPasses(0), turnsInJail(0), diceRoll(0)
{
	setName(name);
	setMoney(money);
	setBoardPos(boardPos);
}

MutableProperties& Player::getOwnedProperties()
{
	return ownedProperties;
}

const MutableProperties& Player::getOwnedProperties() const
{
	return ownedProperties;
}

Vector<Railroad*>& Player::getOwnedRailroads()
{
	return ownedRailroads;
}

const Vector<Railroad*>& Player::getOwnedRailroads() const
{
	return ownedRailroads;
}

Vector<Utility*>& Player::getOwnedUtilities()
{
	return ownedUtilities;
}

const Vector<Utility*>& Player::getOwnedUtilities() const
{
	return ownedUtilities;
}

void Player::setName(const String& name)
{
	if (!PlayerValidation::isValidName(name))
	{
		throw std::invalid_argument(PlayerValidation::NAME_ERR.c_str());
	}

	this->name = name;
}

const String& Player::getName() const
{
	return name;
}

void Player::setDiceRoll(unsigned roll)
{
	this->diceRoll = roll;
}

unsigned Player::getDiceRoll() const
{
	return diceRoll;
}

void Player::addMoney(int money)
{
	this->money += money;
}

void Player::setMoney(int money)
{
	this->money = money;
}

int Player::getMoney() const
{
	return money;
}

void Player::eliminate()
{
	for (size_t i = 0; i < ownedProperties.getSize(); i++)
	{
		ownedProperties[i]->setOwner(nullptr);
	}	
	
	for (size_t i = 0; i < ownedRailroads.getSize(); i++)
	{
		ownedRailroads[i]->setOwner(nullptr);
	}
	
	for (size_t i = 0; i < ownedUtilities.getSize(); i++)
	{
		ownedUtilities[i]->setOwner(nullptr);
	}

	ownedProperties.clear();
	ownedRailroads.clear();
	ownedUtilities.clear();

	eliminated = true;
}

bool Player::isEliminated()
{
	return eliminated;
}

void Player::putInJail()
{
	isJailed = true;
	boardPos = GameEngineConstants::JAIL_POS;
}

void Player::freeFromJail()
{
	isJailed = false;
	turnsInJail = 0;
}

unsigned Player::getJailPassesCount() const
{
	return jailPasses;
}

void Player::decrementJailPasses()
{
	if (jailPasses > 0)
	{
		jailPasses--;
	}
}

void Player::incrementJailPasses()
{
	jailPasses++;
}

void Player::incrementTurnsInJail()
{
	turnsInJail++;
}

unsigned Player::getTurnsInJailCount() const
{
	return turnsInJail;
}

bool Player::isInJail() const
{
	return isJailed;
}

bool Player::isEliminated() const
{
	return eliminated;
}

bool Player::isBankrupt() const
{
	return money < 0;
}

void Player::setBoardPos(size_t pos)
{
	this->boardPos = pos;
}

size_t Player::getBoardPos() const
{
	return boardPos;
}

void Player::buyField(Field& field, const Bank& bank)
{
	if (!isRentableField(field))
	{
		throw std::invalid_argument("Cannot buy non-rentable field!");
	}

	PricedField& asPriced = dynamic_cast<PricedField&>(field);
	if (money < asPriced.getPrice())
	{
		throw std::logic_error(NOT_ENOUGH_OWNERSHIP_MONEY_ERR);
	}

	bank.takeMoney(*this, asPriced.getPrice());

	OwnedField& asOwned = dynamic_cast<OwnedField&>(field);
	asOwned.setOwner(this);
}

bool Player::isRentableField(const Field& field) const
{
	return field.getType() == FieldType::Property
		|| field.getType() == FieldType::Railroad
		|| field.getType() == FieldType::Utility;
}

void Player::payRentTo(const Field& field, const Bank& bank)
{
	if (!isRentableField(field))
	{
		throw std::invalid_argument("Can't pay rent to non-rentable field!");
	}

	const PricedField& asPriced = dynamic_cast<const PricedField&>(field);
	int rent = asPriced.getRent();

	if (field.getType() == FieldType::Utility)
	{
		rent *= diceRoll;
	}

	const OwnedField& asOwned = dynamic_cast<const OwnedField&>(field);
	if (!asOwned.getOwner())
	{
		throw std::logic_error(NO_PROP_OWNER_ERR);
	}

	bank.transfer(*this, *asOwned.getOwner(), rent);
}

void Player::buyUtility(Utility& utility, const Bank& bank)
{
	if (utility.getOwner())
	{
		throw std::logic_error(UTILITY_ALREADY_OWNED_ERR);
	}

	buyField(utility, bank);

	ownedUtilities.push_back(&utility);
}

void Player::sellUtilityTo(Utility& utility, Player& buyer, int price, Bank& bank)
{
	ensureCanSellUtilityTo(utility, buyer, price);

	bank.transfer(buyer, *this, price);
	transferUtilityOwnership(utility, buyer);
}

void Player::ensureCanSellUtilityTo(Utility& utility, Player& buyer, int price)
{
	ensureIsOwnerOf(utility);

	if (&buyer == this)
	{
		throw std::invalid_argument(SELL_UTILITY_TO_SELF_ERR);
	}

	if (price < 0)
	{
		throw std::invalid_argument(INVALID_UTILITY_SELL_PRICE_ERR);
	}

	if (buyer.getMoney() < price)
	{
		throw std::logic_error(INSUFFICIENT_UTILITY_BUYER_MONEY_ERR);
	}
}

void Player::buyRailroad(Railroad& railroad, const Bank& bank)
{
	if (railroad.getOwner())
	{
		throw std::logic_error(RAILROAD_ALREADY_OWNED_ERR);
	}

	buyField(railroad, bank);

	ownedRailroads.push_back(&railroad);
}

void Player::sellRailroadTo(Railroad& railroad, Player& buyer, int price, Bank& bank)
{
	ensureCanSellRailroadTo(railroad, buyer, price);

	bank.transfer(buyer, *this, price);
	transferRailroadOwnership(railroad, buyer);
}

void Player::ensureCanSellRailroadTo(Railroad& railroad, Player& buyer, int price)
{
	ensureIsOwnerOf(railroad);

	if (&buyer == this)
	{
		throw std::invalid_argument(SELL_RAILROAD_TO_SELF_ERR);
	}

	if (price < 0)
	{
		throw std::invalid_argument(INVALID_RAILROAD_SELL_PRICE_ERR);
	}

	if (buyer.getMoney() < price)
	{
		throw std::logic_error(INSUFFICIENT_RAILROAD_BUYER_MONEY_ERR);
	}
}

bool Player::hasFullColorGroup(
	ColorGroup colorGroup,
	const Properties& gameProperties) const
{
	size_t neededCount = gameProperties
		.countBy([colorGroup](const Property* prop) { return prop && prop->getColorGroup() == colorGroup; });

	size_t currentCount = ownedProperties
		.countBy([colorGroup](const Property* prop) { return prop && prop->getColorGroup() == colorGroup; });

	return neededCount == currentCount;
}

bool Player::colorGroupHasHouses(
	ColorGroup colorGroup,
	const Properties& gameProperties) const
{
	return gameProperties
		.filterBy([colorGroup](const Property* prop) { return prop->getColorGroup() == colorGroup; })
		.anyBy([](const Property* prop) { return prop->getHouseLevel() > 0; });
}

void Player::buyProperty(Property& property, const Bank& bank)
{
	Player* owner = property.getOwner();
	if (owner)
	{
		throw std::invalid_argument(ALREADY_OWNED_PROP_ERR);
	}

	buyField(property, bank);

	ownedProperties.push_back(&property);
}

void Player::ensureCanSellPropertyTo(Property& property, Player& buyer, int price, const Properties& gameProperties)
{
	ensureIsOwnerOf(property);

	if (&buyer == this)
	{
		throw std::invalid_argument(SELL_PROPERTY_TO_SELF_ERR);
	}

	if (price < 0)
	{
		throw std::invalid_argument(INVALID_PROP_SELL_PRICE_ERR);
	}

	if (colorGroupHasHouses(property.getColorGroup(), gameProperties))
	{
		throw std::logic_error(PROPERTY_SELL_WHILE_HOUSES_PRESENT_ERR);
	}

	if (buyer.getMoney() < price)
	{
		throw std::logic_error(INSUFFICIENT_PROP_BUYER_MONEY_ERR);
	}
}

void Player::demolishHouseOn(Property& property, const Bank& bank)
{
	ensureIsOwnerOf(property);
	ensureCanDemolishHouseOn(property);

	bank.giveMoney(*this, property.getHouseSellPrice());
	property.decreaseRentIndex();
}

void Player::sellPropertyTo(
	Property& property,
	Player& buyer,
	int price,
	const Properties& gameProperties,
	const Bank& bank)
{
	ensureCanSellPropertyTo(property, buyer, price, gameProperties);

	bank.transfer(buyer, *this, price);
	transferPropertyOwnership(property, buyer);
}

void Player::buildHouseOn(
	Property& property,
	const Properties& gameProperties,
	const Bank& bank)
{
	ensureIsOwnerOf(property);

	if (!hasFullColorGroup(property.getColorGroup(), gameProperties))
	{
		throw std::logic_error(HOUSE_BUILD_WHILE_NO_FULL_GROUP_ERR);
	}

	ensureCanBuildHouseOn(property);

	if (money < property.getHousePrice())
	{
		throw std::logic_error(NOT_ENOUGH_HOUSE_MONEY_ERR);
	}

	property.increaseRentIndex();
	bank.takeMoney(*this, property.getHousePrice());
}

void Player::serialize(std::ostream& os) const
{
	name.serialize(os);
	os.write((const char*)&money, sizeof(money));
	os.write((const char*)&boardPos, sizeof(boardPos));
	os.write((const char*)&eliminated, sizeof(eliminated));
	os.write((const char*)&isJailed, sizeof(isJailed));
	os.write((const char*)&jailPasses, sizeof(jailPasses));
	os.write((const char*)&turnsInJail, sizeof(turnsInJail));
	os.write((const char*)&diceRoll, sizeof(diceRoll));
	
	size_t propsSize = ownedProperties.getSize();
	os.write((const char*)&propsSize, sizeof(propsSize));
	for (size_t i = 0; i < propsSize; i++)
	{
		ownedProperties[i]->getName().serialize(os);
		unsigned houseLevel = ownedProperties[i]->getHouseLevel();
		os.write((const char*)&houseLevel, sizeof(houseLevel));
	}

	size_t railroadsSize = ownedRailroads.getSize();
	os.write((const char*)&railroadsSize, sizeof(railroadsSize));
	for (size_t i = 0; i < railroadsSize; i++)
	{
		ownedRailroads[i]->getName().serialize(os);
	}

	size_t utilitiesSize = ownedUtilities.getSize();
	os.write((const char*)&utilitiesSize, sizeof(utilitiesSize));
	for (size_t i = 0; i < utilitiesSize; i++)
	{
		ownedUtilities[i]->getName().serialize(os);
	}
}

void Player::deserialize(std::istream& is, Board& board)
{
	name.deserialize(is);
	is.read((char*)&money, sizeof(money));
	is.read((char*)&boardPos, sizeof(boardPos));
	is.read((char*)&eliminated, sizeof(eliminated));
	is.read((char*)&isJailed, sizeof(isJailed));
	is.read((char*)&jailPasses, sizeof(jailPasses));
	is.read((char*)&turnsInJail, sizeof(turnsInJail));
	is.read((char*)&diceRoll, sizeof(diceRoll));

	size_t propsSize = 0;
	is.read((char*)&propsSize, sizeof(propsSize));
	for (size_t i = 0; i < propsSize; i++)
	{
		String name;
		name.deserialize(is);
		Property* prop = dynamic_cast<Property*>(board.getFieldByName(name));
		if (!prop)
		{
			throw std::exception("Could not read property from file!");
		}
		unsigned houseLevel = 0;
		is.read((char*)&houseLevel, sizeof(houseLevel));
		while (houseLevel--)
		{
			prop->increaseRentIndex();
		}

		ownedProperties.push_back(prop);
		prop->setOwner(this);
	}

	size_t railroadsSize = 0;
	is.read((char*)&railroadsSize, sizeof(railroadsSize));
	for (size_t i = 0; i < railroadsSize; i++)
	{
		String name;
		name.deserialize(is);
		Railroad* railroad = dynamic_cast<Railroad*>(board.getFieldByName(name));
		if (!railroad)
		{
			throw std::exception("Could not read railroad from file!");
		}
		ownedRailroads.push_back(railroad);
		railroad->setOwner(this);
	}

	size_t utilitiesSize = 0;
	is.read((char*)&utilitiesSize, sizeof(utilitiesSize));
	for (size_t i = 0; i < utilitiesSize; i++)
	{
		String name;
		name.deserialize(is);
		Utility* utility = dynamic_cast<Utility*>(board.getFieldByName(name));
		if (!utility)
		{
			throw std::exception("Could not read utility from file!");
		}
		ownedUtilities.push_back(utility);
		utility->setOwner(this);
	}
}