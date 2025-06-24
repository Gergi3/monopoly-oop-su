#include "BuyPropertyCommand.h"
#include "Command.h"
#include "Field.h"
#include "FieldType.h"
#include "GameEngine.h"
#include "Player.h"
#include "Property.h"
#include <stdexcept>

void BuyPropertyCommand::execute(GameEngine& engine, Field* field, Player& player)
{
	if (!field || field->getType() != FieldType::Property)
	{
		throw std::invalid_argument("Field was null while executing buy property command!");
	}

	Property& property = dynamic_cast<Property&>(*field);
	player.buyProperty(property, engine.getBank());
}

Command* BuyPropertyCommand::clone() const
{
	return new BuyPropertyCommand();
}
