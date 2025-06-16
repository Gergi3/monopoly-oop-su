#include "Console.h"
#include "ConsoleConstants.h"
#include "Key.h"
#include "Vector.hpp"
#include <windows.h>

Console::Console()
{
	setupConsole();
}

void Console::setupConsole() const
{
	SetConsoleOutputCP(437); // 437 - Extended ASCII
	clear();
	maximize();
	disableResize();
	configureDrawingDimensions();
}

void Console::clear() const
{
	system(ConsoleConstants::SYSTEM_CLEAR_ARG);
}

void Console::configureDrawingDimensions() const
{
	system(ConsoleConstants::SYSTEM_DIMENSIONS_ARG.c_str());
}

void Console::maximize() const
{
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_MAXIMIZE);
}

void Console::disableResize() const
{
	HWND hwnd = GetConsoleWindow();
	LONG style = GetWindowLongW(hwnd, GWL_STYLE);
	style &= ~WS_MAXIMIZEBOX;
	style &= ~WS_SIZEBOX;
	SetWindowLongW(hwnd, GWL_STYLE, style);
}

void Console::moveCursorTo(int x, int y)const
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Console::setColor(Color color) const
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}

void Console::enableConsoleEcho() const
{
	setConsoleMode(getConsoleMode() | ENABLE_ECHO_INPUT);
}

void Console::enableConsoleInputBuffer() const
{
	setConsoleMode(getConsoleMode() | ENABLE_LINE_INPUT);
}

void Console::display(const String& str)const
{
	std::cout << str;
}

void Console::displayAt(int x, int y, const String& str)const
{
	moveCursorTo(x, y);
	display(str);
}

Key Console::listenFor(Vector<Key> keys) const
{
	disableConsoleEcho();
	disableConsoleInputBuffer();

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	int counter = 0;

	while (true)
	{
		counter++;
		INPUT_RECORD inputRecord;
		DWORD eventsRead = 0;
		ReadConsoleInput(hStdin, &inputRecord, 1, &eventsRead);

		if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown)
		{
			Key key = static_cast<Key>(inputRecord.Event.KeyEvent.wVirtualKeyCode);
			if (keys.contains(key))
			{
				enableConsoleEcho();
				enableConsoleInputBuffer();
				std::cout << counter;
				return key;
			}
		}
	}
}

void Console::disableConsoleEcho() const
{
	setConsoleMode(getConsoleMode() & ~ENABLE_ECHO_INPUT);
}

void Console::disableConsoleInputBuffer() const
{
	setConsoleMode(getConsoleMode() & ~ENABLE_LINE_INPUT);
}

DWORD Console::getConsoleMode() const
{
	DWORD mode = 0;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
	return mode;
}

void Console::setConsoleMode(DWORD mode) const
{
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode);
}
