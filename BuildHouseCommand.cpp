#include "Board.h"
#include "BuildHouseCommand.h"
#include "GameEngine.h"
#include "Menu.h"
#include "Player.h"
#include "Property.h"
#include "Typedefs.h"
#include <iostream>
#include <stdexcept>

String BuildHouseCommand::getPropertyLabel(Property* property)
{
	if (!property)
	{
		throw std::invalid_argument("Cannot create label from null property!");
	}

	return property->getName() + " (-$" + property->getHousePrice() + ")";
}

String BuildHouseCommand::getMenuTitle(Player& player)
{
	return player.getName() + "\'s owned properties to a build house on:";
}

Property& BuildHouseCommand::askForProperty(Menu& menu, Player& player) const
{
	MutableProperties& ownedProps = player.getOwnedProperties();
	if (ownedProps.getSize() == 0)
	{
		throw std::logic_error("No properties to build houses on!");
	}

	Options propertyOptions = menu.generateOptionsFrom(ownedProps, getPropertyLabel);
	Option selected = menu.selectOption(propertyOptions, getMenuTitle(player));

	Property* prop = ownedProps[selected.key];
	if (!prop)
	{
		throw std::logic_error("Cannot build a house on null property!");
	}

	return *prop;
}

void BuildHouseCommand::execute(GameEngine& engine, Field* field, Player& player)
{
	Menu& menu = engine.getMenu();
	Bank& bank = engine.getBank();
	Board& board = engine.getBoard();

	Property& property = askForProperty(menu, player);

	player.buildHouseOn(property, board.getProperties(), bank);
}

Command* BuildHouseCommand::clone() const
{
	return new BuildHouseCommand(*this);
}
