#pragma once
#include "Command.h"
#include "Typedefs.h"

class CommandHandler
{
public:
	Command* createCommand(const Option& chosenOption);
};
