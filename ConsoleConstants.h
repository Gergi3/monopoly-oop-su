#pragma once
#include "String.h"
#include "TileConstants.h"

namespace ConsoleConstants
{
	constexpr Color DEFAULT_COLOR = Color::White;

	constexpr int SYSTEM_COLS = TileConstants::WIDTH * 12 + 3;
	constexpr int SYSTEM_LINES = TileConstants::HEIGHT * 12 + 3;
	const String SYSTEM_DIMENSIONS_ARG = String("mode con: cols=") + SYSTEM_COLS + " lines=" + SYSTEM_LINES;
	constexpr const char* SYSTEM_CLEAR_ARG = "cls";
}