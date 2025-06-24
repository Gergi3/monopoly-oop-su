#include "Field.h"
#include "FieldValidation.h"

Field::Field(const String& name)
{
	setName(name);
}

void Field::setName(const String& name)
{
	if (!FieldValidation::isValidName(name))
	{
		throw std::invalid_argument(FieldValidation::NAME_ERR.c_str());
	}

	this->name = name;
}

const String& Field::getName() const
{
	return name;
}
