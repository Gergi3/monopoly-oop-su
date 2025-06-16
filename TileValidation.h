#pragma once

namespace TileValidation
{
	constexpr int MIN_COLOR = 0;
	constexpr int MAX_COLOR = 15;
	const String COLOR_ERR = (String)"Tile color values must be between " + MIN_COLOR
		+ " and " + MAX_COLOR + ".";

	inline bool isValidColor(int color)
	{
		return color >= MIN_COLOR && color <= MAX_COLOR;
	}
}