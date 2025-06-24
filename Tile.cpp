#include "Color.h"
#include "String.h"
#include "Tile.h"
#include "TileConstants.h"
#include "Vector.hpp"
#include <stdexcept>

using namespace TileConstants;

void Tile::ensureValidRowIndex(size_t index) const
{
	if (index >= INNER_HEIGHT)
	{
		throw std::out_of_range(INDEX_EXCEEDS_TILE_HEIGHT_ERR);
	}
}

Tile::Tile() : Tile(DEFAULT_COLOR) {}
 
Tile::Tile(Color color) : rows(Vector<String>(INNER_HEIGHT, makeEmptyRow()))
{
	setColor(color);
}

void Tile::addRow(size_t index, const String& str, char lrSymb)
{
	ensureValidRowIndex(index);
	rows[index] = makeRow(str, lrSymb);
}

void Tile::addRow(size_t index, const Vector<String>& strings, char lrSymb)
{
	addRow(index, makeRow(strings, lrSymb), lrSymb);
}

void Tile::addRow(size_t index, char repeated, char lrSymb)
{
	addRow(index, makeRow(repeated, lrSymb), lrSymb);
}

const Vector<String>& Tile::getRows() const
{
	return rows;
}

size_t Tile::getRowsCount() const
{
	return rows.getSize();
}

void Tile::setColor(Color color)
{
	this->color = color;
}

Color Tile::getColor() const
{
	return color;
}

const String& Tile::operator[](size_t index) const
{
	ensureValidRowIndex(index);
	return rows[index];
}

String& Tile::operator[](size_t index)
{
	ensureValidRowIndex(index);
	return rows[index];
}

String Tile::makeBorder()
{
	return makeRow(TOP_SYMB, CORNER_SYMB);
}

String Tile::makeEmptyRow(char lrSymb)
{
	return makeRow(' ', lrSymb);
}

String Tile::makeRow(const String& str, char lrSymb)
{
	return String(lrSymb) + str.paddedRight(INNER_WIDTH) + lrSymb;
}

String Tile::makeRow(const Vector<String>& strings, char lrSymb)
{
	String res;
	for (size_t i = 0; i < strings.getSize(); i++)
	{
		res += strings[i] + ' ';
	}
	return makeRow(res, lrSymb);
}

String Tile::makeRow(char repeated, char lrSymb)
{
	return makeRow(String(INNER_WIDTH, repeated), lrSymb);
}
