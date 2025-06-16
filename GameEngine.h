#pragma once
#pragma once
#include "Bank.h"
#include "Board.h"
#include "Console.h"
#include "Die.h"
#include "GameEngine.h"
#include "GameEngineConstants.h"
#include "Player.h"
#include "Renderer.h"
#include "Vector.hpp"

class Property;

class GameEngine
{
	unsigned seed = 0;
	Renderer& renderer;
	Console& console;
	Board& board;
	Bank& bank;
	Vector<Die> dice;
	Vector<std::unique_ptr<Player>> players;
	void initializeRandomSeed();
	void initializePlayers();
	void gameplayTurnLoop();
	bool isGameOver() const;

	void renderGameState() const;

	Vector<unsigned> rollAllDiceFor(Player& player) const;
	void handleLandingEvent(Player& player, Field* field);

	void executePlayerCommand(const Option& option, Field* field, Player& player);
	void executeBuyProperty(Field* field, Player& player);
	void executeSellProperty(Field* field, Player& player);
	void executeBuildHouse(Field* field, Player& player);
	void executeDemolishHouse(Field* field, Player& player);
	void executeDefaultMenu(Field* field, Player& player);

	Option promptOptionSelection(const Options& options, const String& title);
	unsigned promptPriceSelection(
		const String& title,
		unsigned currentPrice = 50,
		unsigned increment = 25,
		unsigned min = 0,
		unsigned max = 100'000);
	void displayMessagePrompt(const String& title, const String& backOption = "Ok!");

	Vector<Player*> getPlayerPointers() const;

	template<typename T, typename Predicate>
	Options generateOptionsFrom(Vector<T> objs, Predicate func);

public:
	GameEngine() = delete;
	GameEngine(
		Renderer& renderer,
		Console& console,
		Board& board,
		Bank& bank,
		unsigned dieCount = 2);

	void startGameLoop();
};

template<typename T, typename Predicate>
Options GameEngine::generateOptionsFrom(Vector<T> objs, Predicate func)
{
	Options options;
	for (size_t i = 0; i < objs.getSize(); i++)
	{
		options.push_back({ i, func(objs[i])});
	}
	return options;
}
