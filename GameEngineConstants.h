#pragma once
#include "String.h"

namespace GameEngineConstants
{
	constexpr unsigned STARTING_MONEY = 1500;
	constexpr unsigned STEP_ON_START_MONEY = 200;
	constexpr unsigned TURNS_IN_JAIL_BEFORE_OUT_OPTIONS = 3;
	constexpr unsigned MONEY_FOR_JAIL_ESCAPE = 50;
	constexpr unsigned ROLLS_BEFORE_JAIL = 3;
	constexpr unsigned JAIL_POS = 30;

	const String REPEATED_MSG = "Lucky pair! You get to roll again after this turn!";
	const String THREE_IN_A_ROW_MSG = "Three doubles in a row? That's illegal! Go directly to jail!";
	const String JAIL_ESCAPE_MSG = "Freedom! You escaped jail with a lucky double!";
	const String JAIL_ESCAPE_FAIL_MSG = "The dice weren't kind. You stay in jail.";

	const String PASS_START_MSG = String("Woo-hoo! You passed start and recieved ") + STEP_ON_START_MONEY + "$!";

	const String GAME_FILENAME = "game_data.bin";
}