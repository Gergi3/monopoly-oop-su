#pragma once
#include "Command.h"

class GiveUpCommand : public Command
{
public:
	void execute(GameEngine& engine, Field* field, Player& player) override;
	Command* clone() const override;
};

