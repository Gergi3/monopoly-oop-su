#pragma once
#include "Card.h"
#include "PaymentType.h"

class Bank;

class PaymentCard : public Card
{
	PaymentType type;
	int amount;
	Bank& bank;

	void setAmount(int amount);
public:
	PaymentCard(const String& name, PaymentType type, int amount, Bank& bank);
	
	void applyEffect(Player& player) const override;
	Card* clone() const override;
};

