#include "Board.h"
#include "BoardUtilities.h"
#include "Field.h"
#include "FieldFactory.h"
#include "Property.h"
#include <memory>

using namespace BoardUtilities;

void Board::initializeProperties(Vector<PropertyData> group)
{
    for (int i = 0; i < group.getSize(); ++i)
    {
        std::unique_ptr<Property> asField = FieldFactory::createProperty(
            group[i].name,
            group[i].colorGroup,
            group[i].price,
            group[i].housePrice,
            group[i].rentTable);

        fields[group[i].boardPos] = std::move(asField);
    }
}

void Board::initializeProperties()
{
    initializeProperties(makeBrownProperties());
    initializeProperties(makeLightBlueProperties());
    initializeProperties(makePinkProperties());
    initializeProperties(makeOrangeProperties());
    initializeProperties(makeRedProperties());
    initializeProperties(makeYellowProperties());
    initializeProperties(makeGreenProperties());
    initializeProperties(makeBlueProperties());
}

Board::Board() : fields(ALL_FIELDS)
{
    initializeProperties();
}

const Field* Board::getField(size_t index) const
{
    return fields[index].get();
}

Field* Board::getField(size_t index)
{
    return fields[index].get();
}

Vector<Field*> Board::getFields() const
{
    Vector<Field*> result = Vector<Field*>(fields.getCapacity());
    for (size_t i = 0; i < fields.getSize(); i++)
    {
        result[i] = fields[i].get();
    }
    return result;
}

Properties Board::getProperties() const
{
    Properties result;
    for (size_t i = 0; i < fields.getSize(); i++)
    {
        const Field* field = getField(i);
        if (field && field->getType() == FieldType::Property)
        {
            const Property* prop = dynamic_cast<const Property*>(field);
            result.push_back(prop);
        }
    }
    return result;
}

MutableProperties Board::getPropertiesMutable()
{
    MutableProperties result;
    for (size_t i = 0; i < fields.getSize(); i++)
    {
        Field* field = getField(i);
        if (field && field->getType() == FieldType::Property)
        {
            Property* prop = dynamic_cast<Property*>(field);
            result.push_back(prop);
        }
    }
    return result;
}
