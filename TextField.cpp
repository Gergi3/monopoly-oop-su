#include "TextField.h"

TextField::TextField(const String& name) : Field(name)
{}

Tile TextField::toTile() const
{
	Tile tile;
	tile.addRow(0, name);
	return tile;
}

FieldType TextField::getType() const
{
	return FieldType::TextField;
}
