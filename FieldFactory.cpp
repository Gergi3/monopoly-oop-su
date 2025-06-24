#include "CardField.h"
#include "Deck.h"
#include "FieldFactory.h"
#include "Property.h"
#include "Utility.h"
#include <memory>

std::unique_ptr<Property> FieldFactory::createProperty(
    const String& name, 
    ColorGroup colorGroup, 
    int price, 
    int housePrice, 
    Vector<int> rentTable)
{
    return std::make_unique<Property>(name, colorGroup, price, housePrice, rentTable);
}

std::unique_ptr<Railroad> FieldFactory::createRailroad(const String& name, int price)
{
    return std::make_unique<Railroad>(name, price);

}

std::unique_ptr<Utility> FieldFactory::createUtility(const String& name, int price)
{
    return std::make_unique<Utility>(name, price);
}

std::unique_ptr<CardField> FieldFactory::createCardField(const String& name, Deck& deck)
{
    return std::make_unique<CardField>(name, deck);
}

std::unique_ptr<TextField> FieldFactory::createTextField(const String& name)
{
    return std::make_unique<TextField>(name);
}

std::unique_ptr<TaxField> FieldFactory::createTaxField(const String& name, int tax)
{
    return std::make_unique<TaxField>(name, tax);
}
