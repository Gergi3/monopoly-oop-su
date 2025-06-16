#include "Board.h"
#include "GameEngine.h"
#include "MathHelpers.h"
#include "BoardUtilities.h"
#include "GameEngineConstants.h"
#include "FieldType.h"
#include "Property.h"
#include <ctime>
#include <random>

using namespace GameEngineConstants;

GameEngine::GameEngine(
	Renderer& renderer,
	Console& console,
	Board& board,
	Bank& bank,
	unsigned dieCount
)
	: renderer(renderer),
	console(console),
	board(board),
	dice(Vector<Die>(dieCount)),
	bank(bank)
{
	initializeRandomSeed();
}

void GameEngine::startGameLoop()
{
	console.setupConsole();
	renderer.drawBoard(board, getPlayerPointers());
	initializePlayers();

	console.clear();
	renderer.drawBoard(board, getPlayerPointers());
	renderer.drawPlayers(getPlayerPointers());

	gameplayTurnLoop();
}

void GameEngine::initializeRandomSeed()
{
	seed = static_cast<unsigned>(std::time(nullptr));
	std::srand(seed);
}

void GameEngine::initializePlayers()
{
	Options options;
	for (size_t i = 2; i <= 6; i++)
	{
		options.push_back({ i, String(i) + " Players" });
	}

	Option selected = promptOptionSelection(options, "Choose player count:");

	for (size_t i = 1; i <= selected.key; i++)
	{
		// TODO: Add custom naming option
		String playerName = String("P") + i;
		players.push_back(std::make_unique<Player>(playerName, DEFAULT_STARTING_CASH, 0));

		// TODO: REMOVE ONLY FOR TESTING
		if (i == 1)
		{
			Property* prop1 = board.getPropertiesMutable()[0];
			Property* prop2 = board.getPropertiesMutable()[1];

			players[0].get()->buyProperty(*prop1, bank);
			players[0].get()->buyProperty(*prop2, bank);
		}
	}
}

void GameEngine::gameplayTurnLoop()
{
	Vector<Player*> rawPlayers = getPlayerPointers();
	size_t playerIndex = 0;
	while (!isGameOver())
	{
		if (playerIndex == rawPlayers.getSize())
		{
			playerIndex = 0;
		}
		Player& player = *rawPlayers[playerIndex];

		displayMessagePrompt(player.getName() + "\'s turn:", "Roll dice!");
		rollAllDiceFor(player);

		Field* field = board.getField(player.getBoardPos());
		handleLandingEvent(player, field);

		while (true)
		{
			try
			{
				executePlayerCommand(DEFAULT_MENU, field, player);
				break;
			}
			catch (std::invalid_argument& ex)
			{
				displayMessagePrompt(ex.what());
			}
			catch (std::logic_error& ex)
			{
				displayMessagePrompt(ex.what());
			}
		}

		renderGameState();
		playerIndex++;
	}
}

bool GameEngine::isGameOver() const
{
	size_t activePlayers = 0;
	for (const auto& player : players)
	{
		if (!player->isBankrupt())
		{
			activePlayers++;
		}
	}
	return activePlayers <= 1;
}

void GameEngine::renderGameState() const
{
	renderer.drawBoard(board, getPlayerPointers());
	renderer.drawDiceCentered(dice);
	renderer.drawPlayers(getPlayerPointers());
}

Vector<unsigned> GameEngine::rollAllDiceFor(Player& player) const
{
	unsigned rolled = 0;
	Vector<unsigned> rolls = Vector<unsigned>(dice.getSize());
	for (size_t i = 0; i < dice.getSize(); i++)
	{
		unsigned currentRoll = dice[i].roll();
		rolled += currentRoll;
		rolls[i] = currentRoll;
	}

	if (!player.isBankrupt())
	{
		size_t newPos = (player.getBoardPos() + rolled) % BoardUtilities::ALL_FIELDS;
		player.setBoardPos(newPos);
		return rolls;
	}

	return rolls;
}

void GameEngine::handleLandingEvent(Player& player, Field* field)
{
	if (!field)
	{
		return;
	}

	switch (field->getType())
	{
		case FieldType::Property:
		{
			Property& property = dynamic_cast<Property&>(*field);
			if (property.getOwner() && property.getOwner() != &player)
			{
				player.payRentTo(property, bank);
				renderGameState();

				String msg = String("You (") + player.getName() + ") just payed "
					+ property.getRent() + "$ for rent to " + property.getOwner()->getName();
				displayMessagePrompt(msg);
			}
		}
	}
}

void GameEngine::executePlayerCommand(const Option& option, Field* field, Player& player)
{
	renderGameState();

	if (option == END_TURN)
	{
		return;
	}
	else if (option == BUY_PROPERTY && field)
	{
		executeBuyProperty(field, player);
	}
	else if (option == SELL_PROPERTY)
	{
		executeSellProperty(field, player);
	}
	else if (option == BUILD_HOUSE)
	{
		executeBuildHouse(field, player);
	}
	else if (option == DEMOLISH_HOUSE)
	{
		executeDemolishHouse(field, player);
	}
	else if (option == DEFAULT_MENU)
	{
		executeDefaultMenu(field, player);
	}
}

void GameEngine::executeBuyProperty(Field* field, Player& player)
{
	Property& property = dynamic_cast<Property&>(*field);
	player.buyProperty(property, bank);
}

void GameEngine::executeSellProperty(Field* field, Player& player)
{
	MutableProperties& ownedProps = player.getOwnedProperties();
	if (ownedProps.getSize() == 0)
	{
		throw std::logic_error("You don’t own any properties to sell.");
	}

	Vector<Player*> playersRaw = getPlayerPointers();

	Options propertyOptions = generateOptionsFrom(ownedProps, [](Property* p) { return p->getName(); });
	Options playerOptions = generateOptionsFrom(playersRaw, [](Player* p) { return p->getName(); })
		.filterBy([player](Option opt) { return opt.value != player.getName(); });

	String optionTitle = player.getName() + "\'s owned properties to sell:";
	Option selectedProperty = promptOptionSelection(propertyOptions, optionTitle);

	String playerTitle = String("Select player to sell ") + selectedProperty.value + " to:";
	Option selectedPlayer = promptOptionSelection(playerOptions, playerTitle);

	Player& buyer = *playersRaw[selectedPlayer.key];
	Property& propToSell = *ownedProps[selectedProperty.key];
	unsigned price = promptPriceSelection("Choose a price to sell " + selectedProperty.value + " for:");

	player.ensureCanSellPropertyTo(propToSell, buyer, price, board.getProperties());

	Options buyerOptions;
	buyerOptions.push_back(ACCEPT_DEAL);
	buyerOptions.push_back(REJECT_DEAL);
	Option selected = promptOptionSelection(buyerOptions, player.getName() + " offers you (" + buyer.getName()
		+ ") his property (" + propToSell.getName() + ") for " + price + "!");

	if (selected == ACCEPT_DEAL)
	{
		player.sellPropertyTo(propToSell, buyer, price, board.getProperties(), bank);
		renderGameState();
		String successMessage = String("Successfully sold ") + propToSell.getName()
			+ " to " + buyer.getName() + " for $" + price + "!";
		displayMessagePrompt(successMessage);
	}
	else if (selected == REJECT_DEAL)
	{
		displayMessagePrompt("Your offer was rejected!");
	}
}

void GameEngine::executeBuildHouse(Field* field, Player& player)
{
	MutableProperties& ownedProps = player.getOwnedProperties();
	if (ownedProps.getSize() == 0)
	{
		throw std::logic_error("No properties to build houses on!");
	}

	Options propertyOptions = generateOptionsFrom(
		ownedProps,
		[](Property* p) { return p->getName() + " (-$" + p->getHousePrice() + ")"; });

	Option selected = promptOptionSelection(propertyOptions, player.getName() + "\'s owned properties to build house on:");

	player.buildHouseOn(*ownedProps[selected.key], board.getProperties(), bank);
}

void GameEngine::executeDemolishHouse(Field* field, Player& player)
{
	MutableProperties& ownedProps = player.getOwnedProperties();
	if (ownedProps.getSize() == 0)
	{
		throw std::logic_error("No properties to demolish houses on!");
	}

	Options propertyOptions = generateOptionsFrom(
		ownedProps,
		[](Property* p) { return p->getName() + " (+$" + p->getHouseSellPrice() + ")"; });

	Option selected = promptOptionSelection(propertyOptions, player.getName() + "\'s owned properties to demolish a house from:");

	player.demolishHouseOn(*ownedProps[selected.key], bank);
}

void GameEngine::executeDefaultMenu(Field* field, Player& player)
{
	Options options;

	options.push_back(END_TURN);

	options.push_back(SELL_PROPERTY);
	options.push_back(BUILD_HOUSE);
	options.push_back(DEMOLISH_HOUSE);

	if (field && field->getType() == FieldType::Property)
	{
		Property& property = dynamic_cast<Property&>(*field);

		if (!property.getOwner())
		{
			options.insert(1, BUY_PROPERTY);
		}
	}

	Option selected = promptOptionSelection(options, player.getName() + "\'s turn:");
	executePlayerCommand(selected, field, player);
	if (selected != END_TURN)
	{
		executePlayerCommand(DEFAULT_MENU, field, player);
	}
}

Option GameEngine::promptOptionSelection(const Options& options, const String& title)
{
	Vector<Key> keys;
	keys.push_back(Key::UP);
	keys.push_back(Key::DOWN);
	keys.push_back(Key::ENTER);

	size_t selected = 0;

	while (true)
	{
		renderer.drawPromptMenu(options, title, selected);

		Key keyPressed = console.listenFor(keys);
		switch (keyPressed)
		{
			case Key::UP:
				selected = (selected - 1 + options.getSize()) % options.getSize();
				break;
			case Key::DOWN:
				selected = (selected + 1) % options.getSize();
				break;
			case Key::ENTER:
				return options[selected];
				break;
		}
	}
}

unsigned GameEngine::promptPriceSelection(const String& title, unsigned currentPrice, unsigned increment, unsigned min, unsigned max)
{
	Vector<Key> keys;
	keys.push_back(Key::UP);
	keys.push_back(Key::DOWN);
	keys.push_back(Key::ENTER);

	while (true)
	{
		renderer.drawNumberPromptMenu(currentPrice, title);

		Key keyPressed = console.listenFor(keys);
		switch (keyPressed)
		{
			case Key::UP:
				currentPrice += increment;
				break;
			case Key::DOWN:
				currentPrice -= currentPrice > increment + min ? increment : min;
				break;
			case Key::ENTER:
				return currentPrice;
				break;
		}
	}
}

void GameEngine::displayMessagePrompt(const String& title, const String& backOption)
{
	Options options;
	options.push_back({ 99999, backOption });
	promptOptionSelection(options, title);
}

Vector<Player*> GameEngine::getPlayerPointers() const
{
	Vector<Player*> rawPlayers = Vector<Player*>(players.getSize(), nullptr);
	for (size_t i = 0; i < players.getSize(); i++)
	{
		rawPlayers[i] = players[i].get();
	}
	return rawPlayers;
}
