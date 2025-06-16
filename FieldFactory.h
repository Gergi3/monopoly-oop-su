#pragma once

#include "Property.h"
#include "String.h"
#include "Vector.hpp"

class FieldFactory
{
public:
    static std::unique_ptr<Property> createProperty(
        const String& name,
        ColorGroup colorGroup,
        int price,
        int housePrice,
        Vector<int> rentTable);
};