#include "Bank.h"
#include "Command.h"
#include "GameEngine.h"
#include "GameEngineConstants.h"
#include "Menu.h"
#include "PayJailFeeCommand.h"
#include "Player.h"

void PayJailFeeCommand::execute(GameEngine& engine, Field* field, Player& player)
{
	Menu& menu = engine.getMenu();
	Bank& bank = engine.getBank();

	bank.takeMoney(player, GameEngineConstants::MONEY_FOR_JAIL_ESCAPE);
	player.freeFromJail();
	engine.renderGameState();
	
	menu.showMessage(String("You payed ") + GameEngineConstants::MONEY_FOR_JAIL_ESCAPE + "$ to get out of jail!");
}

Command* PayJailFeeCommand::clone() const
{
	return new PayJailFeeCommand(*this);
}
