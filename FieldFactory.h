#pragma once

#include "CardField.h"
#include "Property.h"
#include "Railroad.h"
#include "String.h"
#include "TaxField.h"
#include "TextField.h"
#include "Utility.h"
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

    static std::unique_ptr<Railroad> createRailroad(
        const String& name,
        int price
    );

    static std::unique_ptr<Utility> createUtility(
        const String& name,
        int price
    );

    static std::unique_ptr<CardField> createCardField(
        const String& name,
        Deck& deck
    );

    static std::unique_ptr<TextField> createTextField(
        const String& name
    );

    static std::unique_ptr<TaxField> createTaxField(
        const String& name,
        int tax
    );
};