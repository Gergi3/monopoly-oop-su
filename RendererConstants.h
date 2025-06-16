#pragma once
#include "TileConstants.h"

namespace RendererConstants
{
	constexpr int START_X = 1;
	constexpr int START_Y = 0;

	constexpr int VIEW_WIDTH = TileConstants::WIDTH * 11 + START_X;
	constexpr int VIEW_HEIGHT = TileConstants::HEIGHT * 11 + START_Y;

	constexpr int DIE_WIDTH = 5;
	constexpr int DIE_HEIGHT = 5;
	constexpr int SPACING = 5;
	constexpr int DIE_ROWS = 3;

	const char BOX_TL_SYMB = '\xDA';
	const char BOX_TR_SYMB = '\xBF';
	const char BOX_BL_SYMB = '\xC0';
	const char BOX_BR_SYMB = '\xD9';
	const char BOX_H_SYMB = '\xC4';
	const char BOX_V_SYMB = '\xB3';

	const String DIE_TOP_BORDER = String(BOX_TL_SYMB) + String(7, BOX_H_SYMB) + BOX_TR_SYMB;
	const String DIE_BOTTOM_BORDER = String(BOX_BL_SYMB) + String(7, BOX_H_SYMB) + BOX_BR_SYMB;
	const String DIE_SIDE_BORDER = String(BOX_V_SYMB);


	const char* DIE_FACES[6][3] = {
	{ "       ", "   \xFE   ", "       " },
	{ " \xFE     ", "       ", "     \xFE " },
	{ " \xFE     ", "   \xFE   ", "     \xFE " },
	{ " \xFE   \xFE ", "       ", " \xFE   \xFE " },
	{ " \xFE   \xFE ", "   \xFE   ", " \xFE   \xFE " },
	{ " \xFE \xFE \xFE ", "       ", " \xFE \xFE \xFE " }
	};
}