#include "Board.h"
#include "Color.h"
#include "Console.h"
#include "ConsoleConstants.h"
#include "Die.h"
#include "Field.h"
#include "GameEngineConstants.h"
#include "ITileable.h"
#include "Player.h"
#include "Renderer.h"
#include "RendererConstants.h"
#include "Tile.h"
#include "TileConstants.h"
#include "Vector.hpp"
#include <iostream>

using namespace RendererConstants;

void Renderer::resetPen() const
{
	console.moveCursorTo(0, 0);
}

Renderer::Renderer(Console& console) : console(console)
{}

void Renderer::draw(int x, int y, const ITileable& tileable) const
{
	drawTile(x, y, tileable.toTile());
}

void Renderer::drawTile(int x, int y, const Tile& tile) const
{
	console.setColor(tile.getColor());

	console.displayAt(x, y++, Tile::makeBorder());

	for (size_t i = 0; i < tile.getRowsCount(); i++)
	{
		console.displayAt(x, y++, tile[i]);
	}

	console.displayAt(x, y++, Tile::makeBorder());

	console.setColor(ConsoleConstants::DEFAULT_COLOR);

	resetPen();
}

void Renderer::drawBoard(const Board& board, const Vector<Player*>& players) const
{
	Vector<Field*> fields = board.getFields();

	const int startX = START_X;
	const int startY = START_Y;
	const int tileWidth = TileConstants::WIDTH;
	const int tileHeight = TileConstants::HEIGHT;

	size_t currentTilePos = 0;
	// TODO: Refactor later
	// Bottom row rtl (tiles 0–10)
	for (int i = 0; i <= 10; i++)
	{
		String playersString;
		for (size_t j = 0; j < players.getSize(); j++)
		{
			if (players[j]->getBoardPos() == currentTilePos)
			{
				playersString += players[j]->getName();
			}
		}
		Tile tile = fields[i] ? fields[i]->toTile() : Tile();
		tile.addRow(tile.getRowsCount() - 1, playersString);
		drawTile(startX + (10 - i) * tileWidth, startY + 10 * tileHeight, tile);
		currentTilePos++;
	}

	// Left column btt (tiles 11–20)
	for (int i = 0; i < 10; i++)
	{
		String playersString;
		for (size_t j = 0; j < players.getSize(); j++)
		{
			if (players[j]->getBoardPos() == currentTilePos)
			{
				playersString += players[j]->getName();
			}
		}

		size_t indx = 11 + i;
		Tile tile = fields[indx] ? fields[indx]->toTile() : Tile();
		tile.addRow(tile.getRowsCount() - 1, playersString);
		drawTile(startX, startY + (9 - i) * tileHeight, tile);
		currentTilePos++;
	}

	// Top row ltr (tiles 21–30)
	for (int i = 0; i < 10; i++)
	{
		String playersString;
		for (size_t j = 0; j < players.getSize(); j++)
		{
			if (players[j]->getBoardPos() == currentTilePos)
			{
				playersString += players[j]->getName();
			}
		}
		size_t indx = 21 + i;
		Tile tile = fields[indx] ? fields[indx]->toTile() : Tile();
		tile.addRow(tile.getRowsCount() - 1, playersString);
		drawTile(startX + (i + 1) * tileWidth, startY, tile);
		currentTilePos++;
	}

	// Right column ttb (tiles 31–39)
	for (int i = 0; i < 9; i++)
	{
		String playersString;
		for (size_t j = 0; j < players.getSize(); j++)
		{
			if (players[j]->getBoardPos() == currentTilePos)
			{
				playersString += players[j]->getName();
			}
		}
		size_t indx = 31 + i;
		Tile tile = fields[indx] ? fields[indx]->toTile() : Tile();
		tile.addRow(tile.getRowsCount() - 1, playersString);
		drawTile(startX + 10 * tileWidth, startY + (i + 1) * tileHeight, tile);
		currentTilePos++;
	}

	resetPen();
}

void Renderer::drawDice(int x, int y, const Vector<Die>& dice) const
{
	int currentX = x;
	for (size_t i = 0; i < dice.getSize(); i++)
	{
		console.displayAt(currentX, y, String(DIE_TOP_BORDER));
		currentX += DIE_WIDTH + SPACING;
	}

	for (int row = 0; row < DIE_ROWS; row++)
	{
		currentX = x;
		for (size_t i = 0; i < dice.getSize(); i++)
		{
			unsigned value = dice[i].getLastRoll();
			if (value < 1 || value > 6)
			{
				value = 1;
			}

			String line = String(DIE_SIDE_BORDER) + DIE_FACES[value - 1][row] + BOX_V_SYMB;

			console.displayAt(currentX, y + 1 + row, line);
			currentX += DIE_WIDTH + SPACING;
		}
	}

	currentX = x;
	for (size_t i = 0; i < dice.getSize(); i++)
	{
		console.displayAt(currentX, y + 4, DIE_BOTTOM_BORDER);
		currentX += DIE_WIDTH + SPACING;
	}

	resetPen();
}

void Renderer::drawDiceCentered(const Vector<Die>& dice) const
{
	int diceWidth = dice.getSize() * 5 + (dice.getSize() - 1) * 2;
	int x = (VIEW_WIDTH - diceWidth) / 2;
	int y = START_Y + (VIEW_HEIGHT) / 2;
	drawDice(x, y, dice);
}

void Renderer::drawNumberPromptMenu(unsigned num, const String& title, Color color)
{
	int x = TileConstants::WIDTH + 3;
	int y = TileConstants::HEIGHT + 1;

	clearArea(x, y, x + 100, y + 20);

	String numStr = "$" + String(num);
	unsigned outerPadding = 3;
	unsigned padding = outerPadding + std::max<size_t>(numStr.getLen(), title.getLen());

	String topBorder = BOX_TL_SYMB + String(padding + outerPadding, BOX_H_SYMB) + BOX_TR_SYMB;
	String bottomBorder = BOX_BL_SYMB + String(padding + outerPadding, BOX_H_SYMB) + BOX_BR_SYMB;
	String sideBorder = String(BOX_V_SYMB) + "   ";

	console.displayAt(x, y++, topBorder);
	console.displayAt(x, y++, sideBorder + String(padding, ' ') + sideBorder);
	
	if (!title.getLen() == 0)
	{
		String l1 = sideBorder + title.paddedRight(padding) + sideBorder;
		String l2 = sideBorder + String(padding, ' ') + sideBorder;
		console.displayAt(x, y++, l1);
		console.displayAt(x, y++, l2);
	}

	String numPadded = numStr.paddedRight(padding);
	console.displayAt(x, y, sideBorder);
	console.setColor(color);
	console.displayAt(x + sideBorder.getLen(), y, numPadded );
	console.setColor(ConsoleConstants::DEFAULT_COLOR);
	console.displayAt(x + sideBorder.getLen() + numPadded.getLen(), y++, sideBorder);

	console.displayAt(x, y++, sideBorder + String(padding, ' ') + sideBorder);
	console.displayAt(x, y, bottomBorder);

	resetPen();
}

void Renderer::drawPromptMenu(const Options& options, const String& title, size_t defaultIndex, Color selectedColor, Color unselectedColor) const
{
	int x = TileConstants::WIDTH + 3;
	int y = TileConstants::HEIGHT + 1;
	drawPromptMenu(x, y, options, title, defaultIndex, selectedColor, unselectedColor);
}

void Renderer::drawPromptMenu(
	int x,
	int y,
	const Options& options,
	const String& title,
	size_t defaultIndex,
	Color selectedColor,
	Color unselectedColor) const

{
	clearArea(x, y, x + 100, y + 20);

	unsigned outerPadding = 3;
	String optionDot = " o ";

	unsigned padding = outerPadding + std::max<size_t>(
		options.maxBy([](Option opt) { return opt.value.getLen(); }).value.getLen() + optionDot.getLen(),
		title.getLen()
	);

	String topBorder = BOX_TL_SYMB + String(padding + outerPadding, BOX_H_SYMB) + BOX_TR_SYMB;
	String bottomBorder = BOX_BL_SYMB + String(padding + outerPadding, BOX_H_SYMB) + BOX_BR_SYMB;
	String sideBorder = String(BOX_V_SYMB) + "   ";

	console.displayAt(x, y++, topBorder);
	console.displayAt(x, y++, sideBorder + String(padding, ' ') + sideBorder);

	if (!title.getLen() == 0)
	{
		String l1 = sideBorder + title.paddedRight(padding) + sideBorder;
		String l2 = sideBorder + String(padding, ' ') + sideBorder;
		console.displayAt(x, y++, l1);
		console.displayAt(x, y++, l2);
	}
	for (size_t i = 0; i < options.getSize(); ++i)
	{
		String optionText = (optionDot + options[i].value).paddedRight(padding);

		console.displayAt(x, y, sideBorder);
		console.setColor(i == defaultIndex ? selectedColor : unselectedColor);
		console.displayAt(x + sideBorder.getLen(), y, optionText);
		console.setColor(ConsoleConstants::DEFAULT_COLOR);
		console.displayAt(x + sideBorder.getLen() + optionText.getLen(), y++, sideBorder);
	}

	console.displayAt(x, y++, sideBorder + String(padding, ' ') + sideBorder);
	console.displayAt(x, y, bottomBorder);

	console.setColor(ConsoleConstants::DEFAULT_COLOR);

	resetPen();
}

void Renderer::clearArea(int x1, int y1, int x2, int y2) const
{
	int left = std::min<int>(x1, x2);
	int right = std::max<int>(x1, x2);
	int top = std::min<int>(y1, y2);
	int bottom = std::max<int>(y1, y2);

	String blank = String(right - left + 1, ' ');
	for (int y = top; y <= bottom; ++y)
	{
		console.displayAt(left, y, blank);
	}
}

void Renderer::drawPlayers(const Vector<Player*>& players) const
{
	const int tileX = START_X + 1 * TileConstants::WIDTH;
	const int tileY = START_Y + 9 * TileConstants::HEIGHT;

	const int width = TileConstants::WIDTH;
	const int height = TileConstants::HEIGHT;

	String top = BOX_TL_SYMB + String(width, BOX_H_SYMB) + BOX_TR_SYMB;
	String bottom = BOX_BL_SYMB + String(width, BOX_H_SYMB) + BOX_BR_SYMB;

	int x = tileX + 1;
	for (size_t i = 0; i < players.getSize(); ++i)
	{
		console.setColor(Color::White);

		Player* player = players[i];
		if (!player)
		{
			continue;
		}
		if (player->isEliminated())
		{
			console.setColor(Color::LightRed);
		}

		int y = tileY - 1;

		console.displayAt(x, y++, top);

		console.displayAt(x, y++, String(BOX_V_SYMB) + player->getName().paddedRight(width) + BOX_V_SYMB);

		String line1 = String("Money: ") + player->getMoney();
		String line2 = String("Board position: ") + player->getBoardPos();
		console.displayAt(x, y++, String(BOX_V_SYMB) + line1.paddedRight(width) + BOX_V_SYMB);
		console.displayAt(x, y++, String(BOX_V_SYMB) + line1.paddedRight(width) + BOX_V_SYMB);
		console.displayAt(x, y++, String(BOX_V_SYMB) + line1.paddedRight(width) + BOX_V_SYMB);
		console.displayAt(x, y++, String(BOX_V_SYMB) + line2.paddedRight(width) + BOX_V_SYMB);
		console.displayAt(x, y, bottom);
		x += tileX + 2;
	}

	console.setColor(ConsoleConstants::DEFAULT_COLOR);
	resetPen();
}
