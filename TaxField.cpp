#include "TaxField.h"

TaxField::TaxField(const String& name, int tax) : Field(name), tax(tax)
{}

Tile TaxField::toTile() const
{
    Tile tile;
    tile.addRow(0, name);
    tile.addRow(1, String("Tax: ") + tax + "$");
    return tile;
}

FieldType TaxField::getType() const
{
    return FieldType::TaxField;
}

int TaxField::getTax() const
{
    return tax;
}
