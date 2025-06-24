#include "BuildHouseCommand.h"
#include "BuyPropertyCommand.h"
#include "BuyRailroadCommand.h"
#include "BuyUtilityCommand.h"
#include "Command.h"
#include "CommandHandler.h"
#include "CommandHandlerConstants.h"
#include "DefaultMenuCommand.h"
#include "DemolishHouseCommand.h"
#include "EndTurnCommand.h"
#include "GiveUpCommand.h"
#include "JailEscapeMenuCommand.h"
#include "JailPassCommand.h"
#include "PayJailFeeCommand.h"
#include "SellPropertyCommand.h"
#include "SellRailroadCommand.h"
#include "SellUtilityCommand.h"
#include "Typedefs.h"

using namespace CommandHandlerConstants;

Command* CommandHandler::createCommand(const Option& chosenOption)
{
	if (chosenOption == END_TURN)
	{
		return new EndTurnCommand();
	}
	else if (chosenOption == BUY_PROPERTY)
	{
		return new BuyPropertyCommand();
	}
	else if (chosenOption == SELL_PROPERTY)
	{
		return new SellPropertyCommand();
	}
	else if (chosenOption == BUILD_HOUSE)
	{
		return new BuildHouseCommand();
	}
	else if (chosenOption == DEMOLISH_HOUSE)
	{
		return new DemolishHouseCommand();
	}
	else if (chosenOption == DEFAULT_MENU)
	{
		return new DefaultMenuCommand();
	}
	else if (chosenOption == USE_JAIL_PASS)
	{
		return new JailPassCommand();
	}
	else if (chosenOption == PAY_JAIL_FEE)
	{
		return new PayJailFeeCommand();
	}
	else if (chosenOption == JAIL_ESCAPE_MENU)
	{
		return new JailEscapeMenuCommand();
	}
	else if (chosenOption == BUY_RAILROAD)
	{
		return new BuyRailroadCommand();
	}
	else if (chosenOption == SELL_RAILROAD)
	{
		return new SellRailroadCommand();
	}
	else if (chosenOption == BUY_UTILITY)
	{
		return new BuyUtilityCommand();
	}
	else if (chosenOption == SELL_UTILITY)
	{
		return new SellUtilityCommand();
	}
	else if (chosenOption == GIVE_UP)
	{
		return new GiveUpCommand();
	}

	return nullptr;
}
