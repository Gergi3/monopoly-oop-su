#include "Bank.h"
#include "BankValidation.h"
#include "Player.h"

using namespace BankValidation;

void Bank::giveMoney(Player& player, int amount) const
{
	if (!isValidAmount(amount))
	{
		throw std::invalid_argument(AMOUNT_ERR.c_str());
	}

	player.addMoney(amount);
}

void Bank::takeMoney(Player& player, int amount) const
{
	if (!isValidAmount(amount))
	{
		throw std::invalid_argument(AMOUNT_ERR.c_str());
	}

	player.addMoney(-amount);
}

void Bank::transfer(Player& from, Player& to, int amount) const
{
	takeMoney(from, amount);
	giveMoney(to, amount);
}
