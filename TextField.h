#pragma once
#include "Field.h"

class TextField : public Field
{
public:
	TextField(const String& name);
	Tile toTile() const override;
	FieldType getType() const override;
};

