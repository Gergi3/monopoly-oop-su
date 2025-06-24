#include "Board.h"
#include "Command.h"
#include "GameEngine.h"
#include "Menu.h"
#include "Player.h"
#include "SellUtilityCommand.h"
#include "String.h"
#include "Typedefs.h"
#include "Utility.h"
#include "Vector.hpp"
#include <stdexcept>

String SellUtilityCommand::getApprovalTitle(Player& seller, Player& buyer, Utility& utilityToSell, unsigned price)
{
	return seller.getName() + " offers you (" + buyer.getName() + ") his utility ("
		+ utilityToSell.getName() + ") for " + price + "!";
}

String SellUtilityCommand::getSuccessMessage(Utility& utilityToSell, Player& buyer, unsigned price)
{
	return String("Successfully sold ") + utilityToSell.getName()
		+ " to " + buyer.getName() + " for $" + price + "!";
}

String SellUtilityCommand::getPriceTitle(Utility& utilityToSell)
{
	return "Choose a price to sell " + utilityToSell.getName() + " for:";
}

String SellUtilityCommand::getPlayerTitle(Utility& utility)
{
	return String("Select player to sell ") + utility.getName() + " to:";
}

String SellUtilityCommand::getPlayerLabel(Player* player)
{
	return player->getName();
}

String SellUtilityCommand::getUtilityLabel(Utility* utility)
{
	return utility->getName();
}

String SellUtilityCommand::getUtilityTitle(Player& player)
{
	return player.getName() + "\'s owned utilitys to sell:";
}

Utility& SellUtilityCommand::askForUtility(Menu& menu, Player& player) const
{
	Vector<Utility*>& ownedUtilitys = player.getOwnedUtilities();
	if (ownedUtilitys.getSize() == 0)
	{
		throw std::logic_error("You don't own any utilitys to sell.");
	}

	Options options = menu.generateOptionsFrom(ownedUtilitys, getUtilityLabel);

	String title = getUtilityTitle(player);
	Option selected = menu.selectOption(options, title);

	return *ownedUtilitys[selected.key];
}

Player& SellUtilityCommand::askForPlayer(Menu& menu, Utility& utilityToSell, Player& player, Vector<Player*> players)const
{
	Options options = menu
		.generateOptionsFrom(players, getPlayerLabel)
		.filterBy([player](Option opt) { return opt.value != player.getName(); });

	String title = getPlayerTitle(utilityToSell);
	Option selected = menu.selectOption(options, title);

	return *players[selected.key];
}

unsigned SellUtilityCommand::askForPrice(Menu& menu, Utility& utilityToSell) const
{
	String title = getPriceTitle(utilityToSell);
	return menu.selectPrice(title);
}

bool SellUtilityCommand::askBuyerForApproval(Menu& menu, Player& seller, Player& buyer, Utility& utilityToSell, unsigned price) const
{
	Options buyerOptions;
	buyerOptions.push_back(ACCEPT_DEAL);
	buyerOptions.push_back(REJECT_DEAL);

	String title = getApprovalTitle(seller, buyer, utilityToSell, price);
	Option selected = menu.selectOption(buyerOptions, title);

	return selected == ACCEPT_DEAL;
}

void SellUtilityCommand::handleRejection(Menu& menu) const
{
	menu.showMessage("Your offer was rejected!");
}

void SellUtilityCommand::handleApproval(GameEngine& engine, Menu& menu, Player& seller, Player& buyer, Utility& utilityToSell, unsigned price) const
{
	seller.sellUtilityTo(utilityToSell, buyer, price, engine.getBank());
	engine.renderGameState();

	String message = getSuccessMessage(utilityToSell, buyer, price);
	menu.showMessage(message);
}

void SellUtilityCommand::execute(GameEngine& engine, Field* field, Player& seller)
{
	Menu& menu = engine.getMenu();
	Board& board = engine.getBoard();
	Vector<Player*> players = engine.getPlayers();

	Utility& utilityToSell = askForUtility(menu, seller);

	Options options;
	options.push_back(TO_BANK);
	options.push_back(TO_PLAYER);
	Option selected = menu.selectOption(options, "To who do you want to sell?");

	if (selected == TO_BANK)
	{
		seller.sellUtilityToBank(utilityToSell, engine.getBank());
		engine.renderGameState();
		menu.showMessage("Utility successfully sold!");
		return;
	}
	else if (selected == TO_PLAYER)
	{
		Player& buyer = askForPlayer(menu, utilityToSell, seller, players);
		unsigned price = askForPrice(menu, utilityToSell);

		seller.ensureCanSellUtilityTo(utilityToSell, buyer, price);

		bool isApproved = askBuyerForApproval(menu, seller, buyer, utilityToSell, price);
		if (!isApproved)
		{
			handleRejection(menu);
			return;
		}

		handleApproval(engine, menu, seller, buyer, utilityToSell, price);
	}

}

Command* SellUtilityCommand::clone() const
{
	return new SellUtilityCommand(*this);
}
