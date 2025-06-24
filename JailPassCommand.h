#pragma once
#include "Command.h"

class JailPassCommand : public Command
{
	void execute(GameEngine& engine, Field* field, Player& player) override;
	Command* clone() const override;
};

