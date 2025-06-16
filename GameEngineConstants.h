#pragma once
#include "Pair.hpp"
#include "String.h"

typedef size_t CommandCode;
typedef Pair<CommandCode, String> Option;
typedef Vector<Option> Options;

namespace GameEngineConstants
{
	constexpr unsigned DEFAULT_STARTING_CASH = 1500;

	const Option DEFAULT_MENU = { 0, "Default Menu" };
	const Option END_TURN = { 1, "End Turn" };
	const Option BUY_PROPERTY = { 100, "Buy Property (On Tile)" };
	const Option SELL_PROPERTY = { 101, "Sell Property" };
	const Option BUILD_HOUSE = { 102, "Build House" };
	const Option DEMOLISH_HOUSE = { 103, "Demolish House" };

	const Option ACCEPT_DEAL = { 201, "Accept deal!" };
	const Option REJECT_DEAL = { 202, "Reject deal!" };
	
	const Option GO_BACK = { 104, "Ok!" };
}