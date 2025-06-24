#include "Command.h"
#include "CommandHandlerConstants.h"
#include "DefaultMenuCommand.h"
#include "Field.h"
#include "FieldType.h"
#include "GameEngine.h"
#include "Menu.h"
#include "Player.h"
#include "Property.h"
#include "Typedefs.h"

using namespace CommandHandlerConstants;

void DefaultMenuCommand::execute(GameEngine& engine, Field* field, Player& player)
{
	Menu& menu = engine.getMenu();

	Options options;
	options.push_back(END_TURN);
	options.push_back(SELL_PROPERTY);
	options.push_back(BUILD_HOUSE);
	options.push_back(DEMOLISH_HOUSE);
	options.push_back(SELL_RAILROAD);
	options.push_back(SELL_UTILITY);

	if (player.isBankrupt())
	{
		options.remove(END_TURN);
		options.remove(BUILD_HOUSE);
		options.push_back(GIVE_UP);
	}

	if (!player.isBankrupt() && field)
	{
		if (field->getType() == FieldType::Property)
		{
			Property& property = dynamic_cast<Property&>(*field);

			if (!property.getOwner())
			{
				options.insert(1, BUY_PROPERTY);
			}
		}
		else if (field->getType() == FieldType::Railroad)
		{
			Railroad& property = dynamic_cast<Railroad&>(*field);

			if (!property.getOwner())
			{
				options.insert(4, BUY_RAILROAD);
			}
		}
		else if (field->getType() == FieldType::Utility)
		{
			Utility& property = dynamic_cast<Utility&>(*field);

			if (!property.getOwner())
			{
				options.insert(0, BUY_UTILITY);
			}
		}
	}
	String msg = player.getName() + "\'s turn:";

	if (player.isBankrupt())
	{
		msg = "You (" + player.getName() + ") need to resolve ur debt in order to continue playing!";
	}

	Option selected = menu.selectOption(options, msg);
	engine.executePlayerCommand(engine.getCommandHandler(), selected, field, player);
	if (selected == GIVE_UP)
	{
		return;
	}
	if (selected != END_TURN)
	{
		engine.executePlayerCommand(engine.getCommandHandler(), DEFAULT_MENU, field, player);
	}
}

Command* DefaultMenuCommand::clone() const
{
	return new DefaultMenuCommand(*this);
}
