#pragma once
#include "Command.h"
#include "String.h"

class Property;
class Menu;
class Player;

class DemolishHouseCommand : public Command
{
	static String getPropertyLabel(Property* property) ;
	static String getMenuTitle(Player& player) ;
	Property& askForProperty(Menu& menu, Player& player) const;

public:
	void execute(GameEngine& engine, Field* field, Player& player) override;
	Command* clone() const override;
};

