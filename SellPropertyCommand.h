#pragma once
#include "Command.h"
#include "Pair.hpp"
#include "String.h"
#include "Typedefs.h"

class Menu;
class GameEngine;
class Field;
class Player;

class SellPropertyCommand : public Command
{
	const Option ACCEPT_DEAL = { 1, "Accept deal!" };
	const Option REJECT_DEAL = { 2, "Reject deal!" };

	static String getSuccessMessage(Property& propToSell, Player& buyer, unsigned price);
	static String getApprovalTitle(Player& seller, Player& buyer, Property& propToSell, unsigned price);

	static String getPriceTitle(Property& propToSell);

	static String getPlayerTitle(Property& property);
	static String getPlayerLabel(Player* player);

	static String getPropTitle(Player& player);
	static String getPropLabel(Property* player);

	Property& askForProp(Menu& menu, Player& player)const;
	Player& askForPlayer(Menu& menu, Property& propToSell, Player& player, Vector<Player*> players)const;
	unsigned askForPrice(Menu& menu, Property& propToSell) const;
	bool askBuyerForApproval(Menu& menu, Player& seller, Player& buyer, Property& propToSell, unsigned price) const;

	void handleRejection(Menu& menu) const;
	void handleApproval(GameEngine& engine, Menu& menu, Player& seller, Player& buyer, Property& propToSell, unsigned price) const;

public:
	void execute(GameEngine& engine, Field* field, Player& player) override;
	Command* clone() const override;
};

