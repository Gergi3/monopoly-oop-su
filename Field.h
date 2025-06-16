#pragma once
#include "FieldType.h"
#include "ITileable.h"

class Field : public ITileable
{
public:
	virtual ~Field() = default;
	virtual FieldType getType() const = 0;
};

