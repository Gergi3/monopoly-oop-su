#pragma once
#include "Color.h"
#include "Key.h"
#include "String.h"
#include "Vector.hpp"
#include <windows.h>

class Console
{
public:
	Console();

	void setupConsole() const;
	void maximize() const;
	void configureDrawingDimensions() const;
	void disableResize() const;
	void setColor(Color color) const;
	void enableConsoleEcho() const;
	void enableConsoleInputBuffer() const;
	void disableConsoleEcho() const;
	void disableConsoleInputBuffer() const;
	DWORD getConsoleMode() const;
	void setConsoleMode(DWORD mode) const;

	void moveCursorTo(int x, int y) const;
	void clear() const;
	void display(const String& str) const;
	void displayAt(int x, int y, const String& str) const;
	Key listenFor(Vector<Key> keys) const;
};

