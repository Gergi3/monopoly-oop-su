#include "Board.h"
#include "Command.h"
#include "GameEngine.h"
#include "Menu.h"
#include "Player.h"
#include "Railroad.h"
#include "SellRailroadCommand.h"
#include "String.h"
#include "Typedefs.h"
#include "Vector.hpp"
#include <stdexcept>

String SellRailroadCommand::getApprovalTitle(Player& seller, Player& buyer, Railroad& railroadToSell, unsigned price)
{
	return seller.getName() + " offers you (" + buyer.getName() + ") his railroad ("
		+ railroadToSell.getName() + ") for " + price + "!";
}

String SellRailroadCommand::getSuccessMessage(Railroad& railroadToSell, Player& buyer, unsigned price)
{
	return String("Successfully sold ") + railroadToSell.getName()
		+ " to " + buyer.getName() + " for $" + price + "!";
}

String SellRailroadCommand::getPriceTitle(Railroad& railroadToSell)
{
	return "Choose a price to sell " + railroadToSell.getName() + " for:";
}

String SellRailroadCommand::getPlayerTitle(Railroad& railroad)
{
	return String("Select player to sell ") + railroad.getName() + " to:";
}

String SellRailroadCommand::getPlayerLabel(Player* player)
{
	return player->getName();
}

String SellRailroadCommand::getRailroadLabel(Railroad* railroad)
{
	return railroad->getName();
}

String SellRailroadCommand::getRailroadTitle(Player& player)
{
	return player.getName() + "\'s owned railroads to sell:";
}

Railroad& SellRailroadCommand::askForRailroad(Menu& menu, Player& player) const
{
	Vector<Railroad*>& ownedRailroads = player.getOwnedRailroads();
	if (ownedRailroads.getSize() == 0)
	{
		throw std::logic_error("You don't own any railroads to sell.");
	}

	Options options = menu.generateOptionsFrom(ownedRailroads, getRailroadLabel);

	String title = getRailroadTitle(player);
	Option selected = menu.selectOption(options, title);

	return *ownedRailroads[selected.key];
}

Player& SellRailroadCommand::askForPlayer(Menu& menu, Railroad& railroadToSell, Player& player, Vector<Player*> players)const
{
	Options options = menu
		.generateOptionsFrom(players, getPlayerLabel)
		.filterBy([player](Option opt) { return opt.value != player.getName(); });

	String title = getPlayerTitle(railroadToSell);
	Option selected = menu.selectOption(options, title);

	return *players[selected.key];
}

unsigned SellRailroadCommand::askForPrice(Menu& menu, Railroad& railroadToSell) const
{
	String title = getPriceTitle(railroadToSell);
	return menu.selectPrice(title);
}

bool SellRailroadCommand::askBuyerForApproval(Menu& menu, Player& seller, Player& buyer, Railroad& railroadToSell, unsigned price) const
{
	Options buyerOptions;
	buyerOptions.push_back(ACCEPT_DEAL);
	buyerOptions.push_back(REJECT_DEAL);

	String title = getApprovalTitle(seller, buyer, railroadToSell, price);
	Option selected = menu.selectOption(buyerOptions, title);

	return selected == ACCEPT_DEAL;
}

void SellRailroadCommand::handleRejection(Menu& menu) const
{
	menu.showMessage("Your offer was rejected!");
}

void SellRailroadCommand::handleApproval(GameEngine& engine, Menu& menu, Player& seller, Player& buyer, Railroad& railroadToSell, unsigned price) const
{
	seller.sellRailroadTo(railroadToSell, buyer, price, engine.getBank());
	engine.renderGameState();

	String message = getSuccessMessage(railroadToSell, buyer, price);
	menu.showMessage(message);
}

void SellRailroadCommand::execute(GameEngine& engine, Field* field, Player& seller)
{
	Menu& menu = engine.getMenu();
	Board& board = engine.getBoard();
	Vector<Player*> players = engine.getPlayers();

	Railroad& railroadToSell = askForRailroad(menu, seller);
	Player& buyer = askForPlayer(menu, railroadToSell, seller, players);
	unsigned price = askForPrice(menu, railroadToSell);

	seller.ensureCanSellRailroadTo(railroadToSell, buyer, price);

	bool isApproved = askBuyerForApproval(menu, seller, buyer, railroadToSell, price);
	if (!isApproved)
	{
		handleRejection(menu);
		return;
	}

	handleApproval(engine, menu, seller, buyer, railroadToSell, price);
}

Command* SellRailroadCommand::clone() const
{
	return new SellRailroadCommand(*this);
}
