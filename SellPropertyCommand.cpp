#include "Board.h"
#include "Command.h"
#include "GameEngine.h"
#include "Menu.h"
#include "Player.h"
#include "Property.h"
#include "SellPropertyCommand.h"
#include "String.h"
#include "Typedefs.h"
#include "Vector.hpp"
#include <stdexcept>

String SellPropertyCommand::getApprovalTitle(Player& seller, Player& buyer, Property& propToSell, unsigned price) 
{
	return seller.getName() + " offers you (" + buyer.getName() + ") his property (" 
		+ propToSell.getName() + ") for " + price + "!";
}

String SellPropertyCommand::getSuccessMessage(Property& propToSell, Player& buyer, unsigned price) 
{
	return String("Successfully sold ") + propToSell.getName()
		+ " to " + buyer.getName() + " for $" + price + "!";
}

String SellPropertyCommand::getPriceTitle(Property& propToSell) 
{
	return "Choose a price to sell " + propToSell.getName() + " for:";
}

String SellPropertyCommand::getPlayerTitle(Property& property) 
{
	return String("Select player to sell ") + property.getName() + " to:";
}

String SellPropertyCommand::getPlayerLabel(Player* player) 
{
	return player->getName();
}

String SellPropertyCommand::getPropLabel(Property* property) 
{
	return property->getName();
}

String SellPropertyCommand::getPropTitle(Player& player) 
{
	return player.getName() + "'s owned properties to sell:";
}

Property& SellPropertyCommand::askForProp(Menu& menu, Player& player) const
{
	MutableProperties& ownedProps = player.getOwnedProperties();
	if (ownedProps.getSize() == 0)
	{
		throw std::logic_error("You don't own any properties to sell.");
	}

	Options options = menu.generateOptionsFrom(ownedProps, getPropLabel);

	String title = getPropTitle(player);
	Option selected = menu.selectOption(options, title);

	return *ownedProps[selected.key];
}

Player& SellPropertyCommand::askForPlayer(Menu& menu, Property& propToSell, Player& player, Vector<Player*> players)const
{
	Options options = menu
		.generateOptionsFrom(players, getPlayerLabel)
		.filterBy([player](Option opt) { return opt.value != player.getName(); });

	String title = getPlayerTitle(propToSell);
	Option selected = menu.selectOption(options, title);

	return *players[selected.key];
}

unsigned SellPropertyCommand::askForPrice(Menu& menu, Property& propToSell) const
{
	String title = getPriceTitle(propToSell);
	return menu.selectPrice(title);
}

bool SellPropertyCommand::askBuyerForApproval(Menu& menu, Player& seller, Player& buyer, Property& propToSell, unsigned price) const
{
	Options buyerOptions;
	buyerOptions.push_back(ACCEPT_DEAL);
	buyerOptions.push_back(REJECT_DEAL);

	String title = getApprovalTitle(seller, buyer, propToSell, price);
	Option selected = menu.selectOption(buyerOptions, title);

	return selected == ACCEPT_DEAL;
}

void SellPropertyCommand::handleRejection(Menu& menu) const
{
	menu.showMessage("Your offer was rejected!");
}

void SellPropertyCommand::handleApproval(GameEngine& engine, Menu& menu, Player& seller, Player& buyer, Property& propToSell, unsigned price) const
{
	seller.sellPropertyTo(propToSell, buyer, price, engine.getBoard().getProperties(), engine.getBank());
	engine.renderGameState();
	
	String message = getSuccessMessage(propToSell, buyer, price);
	menu.showMessage(message);
}

void SellPropertyCommand::execute(GameEngine& engine, Field* field, Player& seller)
{
	Menu& menu = engine.getMenu();
	Board& board = engine.getBoard();
	Vector<Player*> players = engine.getPlayers();

	Property& propToSell = askForProp(menu, seller);
	Player& buyer = askForPlayer(menu, propToSell, seller, players);
	unsigned price = askForPrice(menu, propToSell);

	seller.ensureCanSellPropertyTo(propToSell, buyer, price, board.getProperties());

	bool isApproved = askBuyerForApproval(menu, seller, buyer, propToSell, price);
	if (!isApproved)
	{
		handleRejection(menu);
		return;
	}

	handleApproval(engine, menu, seller, buyer, propToSell, price);
}

Command* SellPropertyCommand::clone() const
{
	return new SellPropertyCommand(*this);
}
