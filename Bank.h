#pragma once

class Player;

class Bank
{
public:
	void giveMoney(Player& player, int amount) const;
	void takeMoney(Player& player, int amount) const;
	void transfer(Player& from, Player& to, int amount) const;
};

