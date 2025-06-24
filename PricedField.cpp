#include "PricedField.h"
#include "PricedFieldValidation.h"

PricedField::PricedField(const String& name, int price) 
	: Field(name)
{
	setPrice(price);
}

void PricedField::setPrice(int price)
{
	if (!PricedFieldValidation::isValidPrice(price))
	{
		throw std::invalid_argument(PricedFieldValidation::PRICE_ERR.c_str());
	}

	this->price = price;
}

int PricedField::getPrice() const
{
	return price;
}