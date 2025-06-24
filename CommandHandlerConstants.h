#pragma once
#include "GameEngineConstants.h"
#include "Typedefs.h"

namespace CommandHandlerConstants
{
	static const Option DEFAULT_MENU = { 0, "Default Menu" };
	static const Option END_TURN = { 1, "End Turn" };
	
	static const Option USE_JAIL_PASS = { 2, "Use a Get Out Of Jail Free Card!" };
	static const Option PAY_JAIL_FEE = { 3, String("Pay ") + GameEngineConstants::MONEY_FOR_JAIL_ESCAPE + "$ `to get out of jail!" };
	static const Option JAIL_ESCAPE_MENU = { 4, "Jail Escape Menu" };
	
	static const Option BUY_PROPERTY = { 100, "Buy Property (On Tile)" };
	static const Option SELL_PROPERTY = { 101, "Sell Property" };
	static const Option BUILD_HOUSE = { 102, "Build House" };
	static const Option DEMOLISH_HOUSE = { 103, "Demolish House" };

	static const Option BUY_RAILROAD = { 201, "Buy Railroad (On Tile)" };
	static const Option SELL_RAILROAD = { 202, "Sell Railroad" };

	static const Option BUY_UTILITY = { 301, "Buy Utility (On Tile)" };
	static const Option SELL_UTILITY = { 302, "Sell Utility" };

	static const Option GIVE_UP = { 500, "Give up!" };
}