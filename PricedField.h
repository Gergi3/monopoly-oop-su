#pragma once
#include "Field.h"
#include "String.h"

class PricedField : virtual public Field
{
protected:
	int price;

public:
	PricedField(const String& name, int price);
	virtual ~PricedField() = default;
	virtual int getRent() const = 0;

	void setPrice(int price);
	int getPrice() const;
};

