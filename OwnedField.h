#pragma once
#include "Field.h"
#include "String.h"

class Player;

class OwnedField : virtual public Field
{
protected:
	Player* owner;

public:
	OwnedField(const String& name);
	virtual ~OwnedField() = default;

	void setOwner(Player* owner);
	Player* getOwner() const;
};

