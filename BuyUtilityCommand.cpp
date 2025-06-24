#include "Bank.h"
#include "BuyUtilityCommand.h"
#include "Field.h"
#include "GameEngine.h"
#include "Player.h"
#include "Utility.h"

void BuyUtilityCommand::execute(GameEngine& engine, Field* field, Player& player)
{
	if (!field || field->getType() != FieldType::Utility)
	{
		throw std::invalid_argument("Field was null while executing buy utility command!");
	}

	Utility& utility = dynamic_cast<Utility&>(*field);
	player.buyUtility(utility, engine.getBank());
}

Command* BuyUtilityCommand::clone() const
{
	return new BuyUtilityCommand(*this);
}
