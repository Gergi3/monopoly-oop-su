#include "Bank.h"
#include "Board.h"
#include "Console.h"
#include "GameEngine.h"
#include "GameEngineConstants.h"
#include "Menu.h"
#include "Renderer.h"
#include "StreamHelpers.h"

int main()
{
	Option NEW_GAME = { 0, "Start New Game" };
	Option CONTINUE = { 1, "Continue Last Game" };
	Option EXIT = { 2, "EXIT" };

	Console* console = new Console();
	Renderer* renderer = new Renderer(*console);
	Bank* bank = new Bank();
	Deck* communityDeck = new Deck(DeckType::Community, *bank);
	Deck* chanceDeck = new Deck(DeckType::Chance, *bank);
	Board* board = new Board(*communityDeck, *chanceDeck);
	Menu* menu = new Menu(*renderer, *console);
	CommandHandler* commandHandler = new CommandHandler();

	Options options;
	options.push_back(NEW_GAME);
	if (StreamHelpers::fileExists(GameEngineConstants::GAME_FILENAME))
	{
		options.push_back(CONTINUE);
	}
	options.push_back(EXIT);
	Option selected = menu->selectOption(options, "Welcome to MonOOpoly!");
	if (selected == EXIT)
	{
		return 0;
	}

	GameEngine* gameEngine = new GameEngine(
		*renderer,
		*console,
		*board,
		*bank,
		*menu,
		*communityDeck,
		*chanceDeck,
		*commandHandler
	);

	gameEngine->startGameLoop(selected == CONTINUE);

	delete renderer;
	delete board;
	delete bank;
	delete menu;
	delete console;
	delete gameEngine;

	return 0;
}
