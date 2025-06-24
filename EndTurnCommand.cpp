#include "Command.h"
#include "EndTurnCommand.h"

void EndTurnCommand::execute(GameEngine& engine, Field* field, Player& player)
{}

Command* EndTurnCommand::clone() const
{
	return new EndTurnCommand(*this);
}
