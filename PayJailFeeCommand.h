#pragma once
#include "Command.h"

class GameEngine;
class Field;
class Player;

class PayJailFeeCommand : public Command
{
	void execute(GameEngine& engine, Field* field, Player& player) override;
	Command* clone() const override;
};

