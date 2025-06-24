#pragma once
#include "Command.h"
#include "String.h"

class GameEngine;
class Field;
class Menu;
class Property;
class Player;

class BuildHouseCommand : public Command
{
	static String getPropertyLabel(Property* property) ;
	static String getMenuTitle(Player& player) ;
	Property& askForProperty(Menu& menu, Player& player) const;

public:
	void execute(GameEngine& engine, Field* field, Player& player) override;
	Command* clone() const override;
};

