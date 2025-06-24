#pragma once
#include "Console.h"
#include "Tile.h"
#include "Tileable.h"

class Player;
class Die;
class Board;

class Renderer
{
	Console& console;

	void resetPen() const;

public:
	Renderer(Console& console);

	void draw(int x, int y, const Tileable& tileable) const;
	void drawTile(int x, int y, const Tile& tile)  const;
	void drawBoard(const Board& board, const Vector<Player*>& players) const;
	void drawDice(int x, int y, const Vector<Die>& dice) const;
	void drawDiceCentered(const Vector<Die>& dice) const;
	void drawNumberPromptMenu(
		unsigned num,
		const String& title = "",
		Color color = Color::Green);
	
	void drawPromptMenu(
		const Options& options,
		const String& title = "",
		size_t defaultIndex = 0,
		Color selectedColor = Color::LightRed,
		Color unselectedColor = Color::White) const;

	void drawPromptMenu(
		int x, 
		int y, 
		const Options& options, 
		const String& title = "",
		size_t defaultIndex = 0,
		Color selectedColor = Color::LightRed,
		Color unselectedColor = Color::White) const;
	void clearArea(int x1, int y1, int x2, int y2) const;
	void drawPlayers(const Vector<Player*>& players) const;
};

