#pragma once
#include "String.h"
#include "TileConstants.h"
#include "Vector.hpp"

class Tile
{
	Vector<String> rows;
	Color color;

	void ensureValidRowIndex(size_t index) const;

public:
	Tile();
	Tile(Color color);

	void addRow(size_t index, const String& str, char lrSymb = TileConstants::SIDE_SYMB);
	void addRow(size_t index, const Vector<String>& strings, char lrSymb = TileConstants::SIDE_SYMB);
	void addRow(size_t index, char repeated, char lrSymb = TileConstants::SIDE_SYMB);
	const Vector<String>& getRows() const;
	size_t getRowsCount() const;

	void setColor(Color color);
	Color getColor() const;

	const String& operator[](size_t index) const;
	String& operator[](size_t index);

	static String makeBorder();
	static String makeEmptyRow(char lrSymb = TileConstants::SIDE_SYMB);
	static String makeRow(const String& str, char lrSymb = TileConstants::SIDE_SYMB);
	static String makeRow(const Vector<String>& strings, char lrSymb = TileConstants::SIDE_SYMB);
	static String makeRow(char repeated, char lrSymb = TileConstants::SIDE_SYMB);
};