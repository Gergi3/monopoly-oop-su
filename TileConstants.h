#pragma once
#include "Color.h"

namespace TileConstants
{
	constexpr const char* INDEX_EXCEEDS_TILE_HEIGHT_ERR = "Cannot add a row to tile, given index out of height range!";

	constexpr Color DEFAULT_COLOR = Color::White;

	constexpr int WIDTH = 19;
	constexpr int HEIGHT = 6;
	constexpr int INNER_WIDTH = WIDTH - 2;
	constexpr int INNER_HEIGHT = HEIGHT - 2;

	constexpr char TOP_SYMB = '-';
	constexpr char CORNER_SYMB = '+';
	constexpr char SIDE_SYMB = '|';
}