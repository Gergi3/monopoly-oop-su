#include "GameEngine.h"
#include "JailPassCommand.h"
#include "Menu.h"
#include "Player.h"

void JailPassCommand::execute(GameEngine& engine, Field* field, Player& player)
{
	Menu& menu = engine.getMenu();

	player.decrementJailPasses();
	player.freeFromJail();

	menu.showMessage("You used a Get Out Of Jail Free Card!");
}

Command* JailPassCommand::clone() const
{
	return new JailPassCommand(*this);
}
