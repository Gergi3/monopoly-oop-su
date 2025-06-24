#pragma once
#include "Field.h"

class TaxField : public Field
{
	int tax;
public:
	TaxField(const String& name, int tax);

	Tile toTile() const override;
	FieldType getType() const override;

	int getTax() const;
};

