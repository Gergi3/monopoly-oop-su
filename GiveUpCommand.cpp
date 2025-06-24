#include "Command.h"
#include "Field.h"
#include "GameEngine.h"
#include "GiveUpCommand.h"
#include "Menu.h"
#include "Player.h"

void GiveUpCommand::execute(GameEngine& engine, Field* field, Player& player)
{
	player.eliminate();
}

Command* GiveUpCommand::clone() const
{
	return new GiveUpCommand(*this);
}
