#pragma once
#include "Console.h"
#include "MenuConstants.h"
#include "Typedefs.h"

class Renderer;

class Menu
{
	Renderer& renderer;
	Console& console;

public:
	Menu(Renderer& renderer, Console& console);

	Option selectOption(
		const Options& options, 
		const String& title = MenuConstants::DEFAULT_OPTIONS_TITLE
	) const;
	unsigned selectPrice(
		const String& title,
		unsigned currentPrice = MenuConstants::DEFAULT_CURRENT_PRICE,
		unsigned increment = MenuConstants::DEFAULT_INCREMENT,
		unsigned min = MenuConstants::DEFAULT_MIN,
		unsigned max = MenuConstants::DEFAULT_MAX
	) const;
	
	void showMessage(
		const String& title,
		const String& goBackText = MenuConstants::DEFAULT_GO_BACK_TEXT
	) const;

	template<typename T, typename Predicate>
	Options generateOptionsFrom(Vector<T> objs, Predicate func) const;
};

template<typename T, typename Predicate>
Options Menu::generateOptionsFrom(Vector<T> objs, Predicate func) const
{
	Options options;
	for (size_t i = 0; i < objs.getSize(); i++)
	{
		options.push_back({ i, func(objs[i]) });
	}
	return options;
}
