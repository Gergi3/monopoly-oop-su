#include "Console.h"
#include "Key.h"
#include "Menu.h"
#include "Renderer.h"
#include "String.h"
#include "Typedefs.h"
#include "Vector.hpp"

Menu::Menu(Renderer& renderer, Console& console)
	: renderer(renderer), console(console)
{}

Option Menu::selectOption(const Options& options, const String& title) const
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

unsigned Menu::selectPrice(
	const String& title,
	unsigned currentPrice,
	unsigned increment,
	unsigned min,
	unsigned max) const
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

void Menu::showMessage(const String& title, const String& goBackText) const
{
	Options options;
	options.push_back({ 99999, goBackText });
	selectOption(options, title);
}