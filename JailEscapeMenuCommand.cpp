#include "CommandHandlerConstants.h"
#include "GameEngine.h"
#include "JailEscapeMenuCommand.h"
#include "Menu.h"
#include "Player.h"
#include "Typedefs.h"

void JailEscapeMenuCommand::execute(GameEngine& engine, Field* field, Player& player)
{
	using namespace CommandHandlerConstants;

	Menu& menu = engine.getMenu();

	Options options;
	if (player.getJailPassesCount() > 0)
	{
		options.push_back(USE_JAIL_PASS);
	}

	options.push_back(PAY_JAIL_FEE);

	Option selected = menu.selectOption(options, player.getName() + "\'s turn:");
	engine.executePlayerCommand(engine.getCommandHandler(), selected, field, player);
}

Command* JailEscapeMenuCommand::clone() const
{
	return new JailEscapeMenuCommand(*this);
}
