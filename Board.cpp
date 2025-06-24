#include "Board.h"
#include "BoardUtilities.h"
#include "CardField.h"
#include "Field.h"
#include "FieldFactory.h"
#include "Property.h"
#include "Railroad.h"
#include "TextField.h"
#include "Utility.h"
#include <memory>

void Board::initializeProperties(Vector<BoardUtilities::PropertyData> props)
{
	for (int i = 0; i < props.getSize(); ++i)
	{
		std::unique_ptr<Property> propertyObj = FieldFactory::createProperty(
			props[i].name,
			props[i].colorGroup,
			props[i].price,
			props[i].housePrice,
			props[i].rentTable);

		fields[props[i].boardPos] = std::move(propertyObj);
	}
}

void Board::initializeRailroads(const Vector<BoardUtilities::RailroadData> railroads)
{
	for (size_t i = 0; i < railroads.getSize(); i++)
	{
		std::unique_ptr<Railroad> railroadObj = FieldFactory::createRailroad(
			railroads[i].name,
			railroads[i].price);

		fields[railroads[i].boardPos] = std::move(railroadObj);
	}
}

void Board::initializeUtilities(const Vector<BoardUtilities::UtilityData> utilities)
{
	for (size_t i = 0; i < utilities.getSize(); i++)
	{
		std::unique_ptr<Utility> utilityObj = FieldFactory::createUtility(
			utilities[i].name,
			utilities[i].price);

		fields[utilities[i].boardPos] = std::move(utilityObj);
	}
}

void Board::initializeCardFields(Vector<BoardUtilities::CardFieldData> data, Deck& deck)
{
	for (size_t i = 0; i < data.getSize(); i++)
	{
		std::unique_ptr<CardField> cardFieldObj = FieldFactory::createCardField(
			data[i].name,
			deck);

		fields[data[i].boardPos] = std::move(cardFieldObj);
	}
}

void Board::initializeCornerFields(Vector<BoardUtilities::TextFieldData> data)
{
	for (size_t i = 0; i < data.getSize(); i++)
	{
		std::unique_ptr<TextField> textFieldObj = FieldFactory::createTextField(
			data[i].name);

		fields[data[i].boardPos] = std::move(textFieldObj);
	}
}

void Board::initializeTaxFields(Vector<BoardUtilities::TaxFieldData> data)
{
	for (size_t i = 0; i < data.getSize(); i++)
	{
		std::unique_ptr<TaxField> textFieldObj = FieldFactory::createTaxField(
			data[i].name,
			data[i].tax);

		fields[data[i].boardPos] = std::move(textFieldObj);
	}
}

Board::Board(Deck& communityDeck, Deck& chanceDeck)
	: fields(BoardUtilities::ALL_FIELDS)
{
	initializeProperties(BoardUtilities::getPropertiesData());
	initializeRailroads(BoardUtilities::getRailroadsData());
	initializeUtilities(BoardUtilities::getUtilityData());
	initializeCardFields(BoardUtilities::getCommunityDeckData(), communityDeck);
	initializeCardFields(BoardUtilities::getChanceDeckData(), chanceDeck);
	initializeCornerFields(BoardUtilities::getCornerFieldsData());
	initializeTaxFields(BoardUtilities::getTaxFieldsData());
}

const Field* Board::getField(size_t index) const
{
	return fields[index].get();
}

Field* Board::getField(size_t index)
{
	return fields[index].get();
}

Field* Board::getFieldByName(const String& name)
{
	for (size_t i = 0; i < fields.getSize(); i++)
	{
		if (fields[i] && fields[i]->getName() == name)
		{
			return fields[i].get();
		}
	}
	return nullptr;
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
