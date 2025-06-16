#include "Bank.h"
#include "Board.h"
#include "Console.h"
#include "GameEngine.h"
#include "Renderer.h"

Vector<String> arr1;
Vector<String> arr2;


int main()
{
	Console console;
	Renderer renderer = Renderer(console);
	Board board;
	Bank bank;
	GameEngine gameEngine = GameEngine(renderer, console, board, bank);
	
	gameEngine.startGameLoop();

	return 0;

}
