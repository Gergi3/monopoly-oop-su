#include "FieldFactory.h"
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
