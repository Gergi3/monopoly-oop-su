#pragma once
#include "FieldType.h"
#include "String.h"
#include "Tileable.h"

class Field : public Tileable
{
protected:
	String name;

public:
	Field(const String& name);
	virtual ~Field() = default;

	void setName(const String& name);
	const String& getName() const;

	virtual FieldType getType() const = 0;
};

