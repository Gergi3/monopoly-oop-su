#pragma once
#include "CommandHandler.h"
#include "Console.h"
#include "Vector.hpp"
#include "Player.h"

class Property;
class Renderer;
class Menu;
class Die;
class Board;
class Bank;
class Deck;

class GameEngine
{
	Renderer& renderer;
	Console& console;
	Board& board;
	Bank& bank;
	Menu& menu;
	Deck& communityDeck;
	Deck& chanceDeck;
	CommandHandler& commandHandler;
	Vector<Die> dice;
	Vector<std::unique_ptr<Player>> players;

	size_t playerIndex = 0;
	size_t repeatedRolls = 0;

	void setRandomSeed();
	void promptForPlayers();
	void turnLoop();

	void handleLandingEvent(Player& player, Field* field);

	void saveGameState();
	void readGameState();

public:
	GameEngine() = delete;
	GameEngine(
		Renderer& renderer,
		Console& console,
		Board& board,
		Bank& bank,
		Menu& menu,
		Deck& communityDeck,
		Deck& chanceDeck,
		CommandHandler& commandHandler,
		unsigned dieCount = 2);

	void startGameLoop(bool readLastGame = false);
	void renderGameState() const;

	bool isGameOver() const;

	bool rollDiceFor(Player& player) const;

	void executePlayerCommand(CommandHandler& handler, const Option& option, Field* field, Player& player);

	Vector<Player*> getPlayers();
	const Vector<Player*> getPlayers() const;

	Renderer& getRenderer();
	const Renderer& getRenderer() const;

	Console& getConsole();
	const Console& getConsole() const;

	Board& getBoard();
	const Board& getBoard() const;

	Bank& getBank();
	const Bank& getBank() const;

	Menu& getMenu();
	const Menu& getMenu() const;

	CommandHandler& getCommandHandler();
	const CommandHandler& getCommandHandler() const;

	Deck& getCommunityDeck();
	const Deck& getCommunityDeck()const;

	Deck& getChanceDeck();
	const Deck& getChanceDeck()const;
};

