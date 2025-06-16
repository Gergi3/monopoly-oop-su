#include "Bank.h"
#include "ColorGroup.h"
#include "Player.h"
#include "PlayerConstants.h"
#include "PlayerValidation.h"
#include "Property.h"
#include "PropertyValidation.h"

using namespace PlayerConstants;

void Player::ensureIsOwnerOf(const Property& property) const
{
	Player* owner = property.getOwner();
	if (owner != this)
	{
		throw std::invalid_argument(NOT_OWNER_ERR);
	}
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

Player::Player(const String& name, int money, size_t boardPos) : eliminated(false)
{
	setName(name);
	setMoney(money);
	setBoardPos(boardPos);
}

MutableProperties& Player::getOwnedProperties()
{
	return ownedProperties;
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

void Player::payRentTo(const Property& property, const Bank& bank)
{
	if (property.getOwner() == this)
	{
		throw std::invalid_argument(PAY_RENT_TO_SELF_ERR);
	}

	int rent = property.getRent();
	bank.transfer(*this, *property.getOwner(), rent);
}

void Player::buyProperty(Property& property, const Bank& bank)
{
	Player* owner = property.getOwner();
	if (owner)
	{
		throw std::invalid_argument(ALREADY_OWNED_ERR);
	}

	if (money < property.getPrice())
	{
		throw std::logic_error(NOT_ENOUGH_OWNERSHIP_MONEY_ERR);
	}

	bank.takeMoney(*this, property.getPrice());
	property.setOwner(this);
	ownedProperties.push_back(&property);
}

void Player::ensureCanSellPropertyTo(Property& property, Player& buyer, int price, const Properties& gameProperties)
{
	ensureIsOwnerOf(property);

	if (&buyer == this)
	{
		throw std::invalid_argument(SELL_PROPERTY_TO_SELF_ERR);
	}

	if (price <= 0)
	{
		throw std::invalid_argument(INVALID_SELL_PRICE_ERR);
	}

	if (colorGroupHasHouses(property.getColorGroup(), gameProperties))
	{
		throw std::logic_error(PROPERTY_SELL_WHILE_HOUSES_PRESENT_ERR);
	}

	if (buyer.getMoney() < price)
	{
		throw std::logic_error(INSUFFICIENT_BUYER_MONEY_ERR);
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
