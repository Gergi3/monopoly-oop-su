#include "Bank.h"
#include "Board.h"
#include "BoardUtilities.h"
#include "CardField.h"
#include "Command.h"
#include "CommandHandler.h"
#include "CommandHandlerConstants.h"
#include "Console.h"
#include "Deck.h"
#include "Die.h"
#include "Field.h"
#include "FieldType.h"
#include "GameEngine.h"
#include "GameEngineConstants.h"
#include "Menu.h"
#include "Player.h"
#include "Property.h"
#include "Renderer.h"
#include "String.h"
#include "TaxField.h"
#include "Typedefs.h"
#include "Vector.hpp"
#include <ctime>
#include <fstream>
#include <memory>
#include <stdexcept>

using namespace GameEngineConstants;

GameEngine::GameEngine(
	Renderer& renderer,
	Console& console,
	Board& board,
	Bank& bank,
	Menu& menu,
	Deck& communityDeck,
	Deck& chanceDeck,
	CommandHandler& commandHandler,
	unsigned dieCount
)
	: renderer(renderer),
	console(console),
	board(board),
	dice(Vector<Die>(dieCount)),
	bank(bank),
	menu(menu),
	communityDeck(communityDeck),
	chanceDeck(chanceDeck),
	commandHandler(commandHandler)
{
	setRandomSeed();
}

void GameEngine::startGameLoop(bool readLastGame)
{
	if (readLastGame)
	{
		readGameState();
	}

	console.setupConsole();
	if (!readLastGame)
	{
		renderer.drawBoard(board, getPlayers());
		promptForPlayers();
	}

	console.clear();
	renderer.drawBoard(board, getPlayers());
	renderer.drawPlayers(getPlayers());

	turnLoop();
}

void GameEngine::setRandomSeed()
{
	unsigned seed = static_cast<unsigned>(std::time(nullptr));
	std::srand(seed);
}

void GameEngine::promptForPlayers()
{
	Options options;
	for (size_t i = 2; i <= 6; i++)
	{
		options.push_back({ i, String(i) + " Players" });
	}

	Option selected = menu.selectOption(options, "Choose player count:");

	for (size_t i = 1; i <= selected.key; i++)
	{
		String playerName = String("P") + i;
		players.push_back(std::make_unique<Player>(playerName, STARTING_MONEY, 0));
	}
}

void GameEngine::turnLoop()
{
	Vector<Player*> rawPlayers = getPlayers();

	while (!isGameOver())
	{
		saveGameState();

		if (playerIndex == rawPlayers.getSize())
		{
			playerIndex = 0;
		}
		Player& player = *rawPlayers[playerIndex];

		if (player.isEliminated())
		{
			continue;
		}

		if (player.isInJail() && player.getTurnsInJailCount() >= TURNS_IN_JAIL_BEFORE_OUT_OPTIONS)
		{
			executePlayerCommand(commandHandler, CommandHandlerConstants::JAIL_ESCAPE_MENU, nullptr, player);
		}

		menu.showMessage(player.getName() + "\'s turn:", "Roll dice!");

		bool areRepeated = rollDiceFor(player);
		renderGameState();
		if (areRepeated && repeatedRolls + 1 < ROLLS_BEFORE_JAIL && !player.isInJail())
		{
			menu.showMessage(REPEATED_MSG);
			repeatedRolls++;
		}
		else if (areRepeated && repeatedRolls + 1 >= ROLLS_BEFORE_JAIL && !player.isInJail())
		{
			menu.showMessage(THREE_IN_A_ROW_MSG);
			player.putInJail();
			repeatedRolls = 0;
			playerIndex++;
			continue;
		}
		else if (areRepeated && player.isInJail())
		{
			menu.showMessage(JAIL_ESCAPE_MSG);
			player.freeFromJail();
		}
		else if (!areRepeated && player.isInJail())
		{
			player.incrementTurnsInJail();
			menu.showMessage(JAIL_ESCAPE_FAIL_MSG);
			playerIndex++;
			continue;
		}

		Field* field = nullptr;
		while (true)
		{
			size_t oldPos = player.getBoardPos();
			field = board.getField(player.getBoardPos());
			handleLandingEvent(player, field);

			if (oldPos == player.getBoardPos())
			{
				break;
			}
		}

		while (true)
		{
			try
			{
				executePlayerCommand(commandHandler, CommandHandlerConstants::DEFAULT_MENU, field, player);
				break;
			}
			catch (std::invalid_argument& ex)
			{
				menu.showMessage(ex.what());
			}
			catch (std::logic_error& ex)
			{
				menu.showMessage(ex.what());
			}
		}

		renderGameState();
		if (!areRepeated)
		{
			playerIndex++;
			repeatedRolls = 0;
		}
	}

	console.clear();
	bool hasWinner = false;
	for (size_t i = 0; i < players.getSize(); i++)
	{
		if (!players[i]->isEliminated())
		{
			menu.showMessage("Game over! " + players[i]->getName() + " won!", "Yaay!");
			hasWinner = true;
		}
	}
	if (!hasWinner)
	{
		// shouldn't reach, but just incase
		menu.showMessage("Game over! Nobody won, all players are bankrupt/eliminated!");
	}
}

bool GameEngine::isGameOver() const
{
	size_t activePlayers = 0;
	for (size_t i = 0; i < players.getSize(); i++)
	{
		if (!players[i]->isEliminated())
		{
			activePlayers++;
		}
	}
	return activePlayers <= 1;
}

void GameEngine::renderGameState() const
{
	renderer.drawBoard(board, getPlayers());
	renderer.drawDiceCentered(dice);
	renderer.drawPlayers(getPlayers());
}

bool GameEngine::rollDiceFor(Player& player) const
{
	bool areRepeated = true;
	unsigned rolled = 0;
	unsigned lastRoll = 0;
	for (size_t i = 0; i < dice.getSize(); i++)
	{
		unsigned currentRoll = dice[i].roll();

		if (i != 0 && currentRoll != lastRoll)
		{
			areRepeated = false;
		}

		rolled += currentRoll;
		lastRoll = currentRoll;
	}
	player.setDiceRoll(rolled);

	if (!player.isInJail() || (player.isInJail() && areRepeated))
	{
		size_t oldPos = player.getBoardPos();
		size_t newPos = (oldPos + rolled) % BoardUtilities::ALL_FIELDS;
		player.setBoardPos(newPos);
		if (newPos < oldPos)
		{
			bank.giveMoney(player, STEP_ON_START_MONEY);
			renderGameState();
			menu.showMessage(PASS_START_MSG);
		}
	}

	return areRepeated;
}

void GameEngine::handleLandingEvent(Player& player, Field* field)
{
	if (!field)
	{
		return;
	}

	switch (field->getType())
	{
		case FieldType::Utility:
		case FieldType::Railroad:
		case FieldType::Property:
		{
			OwnedField& asOwned = dynamic_cast<OwnedField&>(*field);
			PricedField& asPriced = dynamic_cast<PricedField&>(*field);
			if (asOwned.getOwner() && asOwned.getOwner() != &player)
			{
				player.payRentTo(asOwned, bank);
				renderGameState();

				String msg = String("You (") + player.getName() + ") just payed "
					+ asPriced.getRent() + "$ for rent to " + asOwned.getOwner()->getName();
				menu.showMessage(msg);
			}
			break;
		}
		case FieldType::CardField:
		{
			CardField& asCardField = dynamic_cast<CardField&>(*field);
			menu.showMessage("You stepped on " + asCardField.getName(), "Draw a card!");

			const Card* card = asCardField.getDeck().drawCard();
			card->applyEffect(player);

			renderGameState();
			menu.showMessage("You got: " + card->getName());
			break;
		}
		case FieldType::TextField:
		{
			if (player.getBoardPos() == GameEngineConstants::JAIL_POS)
			{
				player.putInJail();
				renderGameState();
				menu.showMessage("You got jailed for walking by the police station!");
			}
			break;
		}
		case FieldType::TaxField:
		{
			TaxField& taxField = dynamic_cast<TaxField&>(*field);
			bank.takeMoney(player, taxField.getTax());
			renderGameState();
			menu.showMessage(String("You payed taxes! (-") + taxField.getTax() + "$)");
			break;
		}
	}
}

void GameEngine::saveGameState()
{
	std::ofstream ofs(GAME_FILENAME.c_str(), std::ios::binary);
	ofs.write((const char*)&playerIndex, sizeof(playerIndex));
	ofs.write((const char*)&repeatedRolls, sizeof(repeatedRolls));
	size_t playersSize = players.getSize();
	ofs.write((const char*)&playersSize, sizeof(playersSize));

	for (size_t i = 0; i < players.getSize(); i++)
	{
		players[i]->serialize(ofs);
	}

	ofs.close();
}

void GameEngine::readGameState()
{
	std::ifstream ifs(GAME_FILENAME.c_str(), std::ios::binary);
	ifs.read((char*)&playerIndex, sizeof(playerIndex));
	ifs.read((char*)&repeatedRolls, sizeof(repeatedRolls));
	size_t playersSize = 0;
	ifs.read((char*)&playersSize, sizeof(playersSize));

	for (size_t i = 0; i < playersSize; i++)
	{
		std::unique_ptr<Player> player = std::make_unique<Player>();
		player->deserialize(ifs, board);
		players.push_back(std::move(player));
	}
}

void GameEngine::executePlayerCommand(
	CommandHandler& handler,
	const Option& option,
	Field* field,
	Player& player)
{
	renderGameState();

	Command* command = handler.createCommand(option);
	if (!command)
	{
		return;
	}

	try
	{
		command->execute(*this, field, player);
	}
	catch (...)
	{
		delete command;
		throw;
	}
}

Vector<Player*> GameEngine::getPlayers()
{
	Vector<Player*> players(this->players.getSize(), nullptr);
	for (size_t i = 0; i < players.getSize(); i++)
	{
		players[i] = this->players[i].get();
	}
	return players;
}

const Vector<Player*> GameEngine::getPlayers() const
{
	Vector<Player*> players(this->players.getSize(), nullptr);
	for (size_t i = 0; i < players.getSize(); i++)
	{
		players[i] = this->players[i].get();
	}
	return players;
}

Renderer& GameEngine::getRenderer()
{
	return renderer;
}

const Renderer& GameEngine::getRenderer() const
{
	return renderer;
}

Console& GameEngine::getConsole()
{
	return console;
}

const Console& GameEngine::getConsole() const
{
	return console;
}

Board& GameEngine::getBoard()
{
	return board;
}

const Board& GameEngine::getBoard() const
{
	return board;
}

Bank& GameEngine::getBank()
{
	return bank;
}

const Bank& GameEngine::getBank() const
{
	return bank;
}

Menu& GameEngine::getMenu()
{
	return menu;
}

const Menu& GameEngine::getMenu() const
{
	return menu;
}

CommandHandler& GameEngine::getCommandHandler()
{
	return commandHandler;
}

const CommandHandler& GameEngine::getCommandHandler() const
{
	return commandHandler;
}

Deck& GameEngine::getCommunityDeck()
{
	return communityDeck;
}

const Deck& GameEngine::getCommunityDeck() const
{
	return communityDeck;
}

Deck& GameEngine::getChanceDeck()
{
	return chanceDeck;
}

const Deck& GameEngine::getChanceDeck() const
{
	return chanceDeck;
}
