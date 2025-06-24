#pragma once
#include "Command.h"
#include "Pair.hpp"
#include "String.h"
#include "Typedefs.h"

class Menu;
class GameEngine;
class Field;
class Player;
class Railroad;

class SellRailroadCommand : public Command
{
	const Option ACCEPT_DEAL = { 1, "Accept deal!" };
	const Option REJECT_DEAL = { 2, "Reject deal!" };

	static String getSuccessMessage(Railroad& railroadToSell, Player& buyer, unsigned price);
	static String getApprovalTitle(Player& seller, Player& buyer, Railroad& railroadToSell, unsigned price);

	static String getPriceTitle(Railroad& railroadToSell);

	static String getPlayerTitle(Railroad& railroaderty);
	static String getPlayerLabel(Player* player);

	static String getRailroadTitle(Player& player);
	static String getRailroadLabel(Railroad* player);

	Railroad& askForRailroad(Menu& menu, Player& player)const;
	Player& askForPlayer(Menu& menu, Railroad& railroadToSell, Player& player, Vector<Player*> players)const;
	unsigned askForPrice(Menu& menu, Railroad& railroadToSell) const;
	bool askBuyerForApproval(Menu& menu, Player& seller, Player& buyer, Railroad& railroadToSell, unsigned price) const;

	void handleRejection(Menu& menu) const;
	void handleApproval(GameEngine& engine, Menu& menu, Player& seller, Player& buyer, Railroad& railroadToSell, unsigned price) const;

public:
	void execute(GameEngine& engine, Field* field, Player& player) override;
	Command* clone() const override;
};

