#pragma once
#include "OwnedField.h"
#include "PricedField.h"

class Utility : public OwnedField, public PricedField
{
public:
    Utility(const String& name, int price);

    int calculateRent(int diceRoll) const;

    int getRent() const override;
    FieldType getType() const override;
    Tile toTile() const override;
};