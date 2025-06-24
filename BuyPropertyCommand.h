#pragma once
#include "Command.h"

class GameEngine;
class Field;
class Player;

class BuyPropertyCommand : public Command
{
public:
	void execute(GameEngine& engine, Field* field, Player& player) override;
	Command* clone() const override;
};
