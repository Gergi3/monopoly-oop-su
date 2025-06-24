#include "Bank.h"
#include "Card.h"
#include "PaymentCard.h"
#include "PaymentCardValidation.h"
#include "PaymentType.h"
#include "String.h"
#include <stdexcept>

void PaymentCard::setAmount(int amount)
{
	if (!PaymentCardValidation::isValidAmount(amount))
	{
		throw std::invalid_argument(PaymentCardValidation::AMOUNT_ERR.c_str());
	}

	this->amount = amount;
}

PaymentCard::PaymentCard(const String& name, PaymentType type, int amount, Bank& bank)
	:Card(name), type(type), bank(bank)
{
	setAmount(amount);
}

void PaymentCard::applyEffect(Player& player) const
{
	switch (type)
	{
		case PaymentType::Pay:
			bank.takeMoney(player, amount);
			break;
		case PaymentType::Recieve:
			bank.giveMoney(player, amount);
			break;
		default:
			throw std::invalid_argument("Invalid card type!");
	}
}

Card* PaymentCard::clone() const
{
	return new PaymentCard(*this);
}
