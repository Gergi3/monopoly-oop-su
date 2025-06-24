#pragma once
#include "Command.h"
#include "Pair.hpp"
#include "String.h"
#include "Typedefs.h"

class Menu;
class GameEngine;
class Field;
class Player;
class Utility;

class SellUtilityCommand : public Command
{
	const Option ACCEPT_DEAL = { 1, "Accept deal!" };
	const Option REJECT_DEAL = { 2, "Reject deal!" };

	static String getSuccessMessage(Utility& utilityToSell, Player& buyer, unsigned price);
	static String getApprovalTitle(Player& seller, Player& buyer, Utility& utilityToSell, unsigned price);

	static String getPriceTitle(Utility& utilityToSell);

	static String getPlayerTitle(Utility& railroaderty);
	static String getPlayerLabel(Player* player);

	static String getUtilityTitle(Player& player);
	static String getUtilityLabel(Utility* player);

	Utility& askForUtility(Menu& menu, Player& player)const;
	Player& askForPlayer(Menu& menu, Utility& utilityToSell, Player& player, Vector<Player*> players)const;
	unsigned askForPrice(Menu& menu, Utility& utilityToSell) const;
	bool askBuyerForApproval(Menu& menu, Player& seller, Player& buyer, Utility& utilityToSell, unsigned price) const;

	void handleRejection(Menu& menu) const;
	void handleApproval(GameEngine& engine, Menu& menu, Player& seller, Player& buyer, Utility& utilityToSell, unsigned price) const;

public:
	void execute(GameEngine& engine, Field* field, Player& player) override;
	Command* clone() const override;
};

