#include "Bank.h"
#include "BuyRailroadCommand.h"
#include "Field.h"
#include "GameEngine.h"
#include "Player.h"
#include "Railroad.h"

void BuyRailroadCommand::execute(GameEngine& engine, Field* field, Player& player)
{
	if (!field || field->getType() != FieldType::Railroad)
	{
		throw std::invalid_argument("Field was null while executing buy railroad command!");
	}

	Railroad& railroad = dynamic_cast<Railroad&>(*field);
	player.buyRailroad(railroad, engine.getBank());
}

Command* BuyRailroadCommand::clone() const
{
    return new BuyRailroadCommand(*this);
}
