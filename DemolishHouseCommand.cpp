#include "Bank.h"
#include "Command.h"
#include "DemolishHouseCommand.h"
#include "GameEngine.h"
#include "Menu.h"
#include "Player.h"
#include "Property.h"
#include "Typedefs.h"
#include "String.h"
#include <iostream>
#include <stdexcept>


String DemolishHouseCommand::getPropertyLabel(Property* property)
{
	if (!property)
	{
		throw std::invalid_argument("Cannot create label from null property!");
	}

	return property->getName() + " (+$" + property->getHouseSellPrice() + ")";
}

String DemolishHouseCommand::getMenuTitle(Player& player)
{
	return player.getName() + "\'s owned properties to demolish a house from:";
}

Property& DemolishHouseCommand::askForProperty(Menu& menu, Player& player) const
{
	MutableProperties& ownedProps = player.getOwnedProperties();
	if (ownedProps.getSize() == 0)
	{
		throw std::logic_error("No properties to demolish houses on!");
	}

	Options propertyOptions = menu.generateOptionsFrom(ownedProps, getPropertyLabel);
	Option selected = menu.selectOption(propertyOptions, getMenuTitle(player));

	Property* prop = ownedProps[selected.key];
	if (!prop)
	{
		throw std::logic_error("Cannot demolish house on null property!");
	}

	return *prop;
}

void DemolishHouseCommand::execute(GameEngine& engine, Field* field, Player& player)
{
	Menu& menu = engine.getMenu();
	Bank& bank = engine.getBank();

	Property& property = askForProperty(menu, player);
	player.demolishHouseOn(property, bank);
}

Command* DemolishHouseCommand::clone() const
{
	return new DemolishHouseCommand(*this);
}
