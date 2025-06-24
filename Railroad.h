#pragma once
#include "FieldType.h"
#include "OwnedField.h"
#include "PricedField.h"
#include "RailroadConstants.h"

class Railroad : public PricedField, public OwnedField
{
public:
	Railroad(const String& name, int price);

	int getRent() const override;

	FieldType getType() const override;
	Tile toTile() const override;
};

