#pragma once
#include "BoardUtilities.h"
#include "Field.h"
#include "Typedefs.h"
#include "Vector.hpp"

class Property;

class Board
{
	Vector<std::unique_ptr<Field>> fields;

	void initializeProperties(const Vector<BoardUtilities::PropertyData> group);
	void initializeProperties();

public:
	Board();

	const Field* getField(size_t index) const;
	Field* getField(size_t index);
	Vector<Field*> getFields() const;

	Properties getProperties() const;
	MutableProperties getPropertiesMutable();
};

