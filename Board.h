#pragma once
#include "BoardUtilities.h"
#include "Deck.h"
#include "Field.h"
#include "Typedefs.h"
#include "Vector.hpp"
#include <memory>

class Property;

class Board
{
	Vector<std::unique_ptr<Field>> fields;

	void initializeProperties(const Vector<BoardUtilities::PropertyData> group);
	void initializeRailroads(const Vector<BoardUtilities::RailroadData> railroads);
	void initializeUtilities(const Vector<BoardUtilities::UtilityData> utilities);
	void initializeCardFields(Vector<BoardUtilities::CardFieldData> data, Deck& deck);
	void initializeCornerFields(Vector<BoardUtilities::TextFieldData> data);
	void initializeTaxFields(Vector<BoardUtilities::TaxFieldData> data);

public:
	Board(Deck& communityDeck, Deck& chanceDeck);

	const Field* getField(size_t index) const;
	Field* getField(size_t index);
	Field* getFieldByName(const String& name);
	Vector<Field*> getFields() const;

	Properties getProperties() const;
	MutableProperties getPropertiesMutable();
};

