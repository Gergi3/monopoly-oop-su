#pragma once

class GameEngine;
class Field;
class Player;

class Command
{
public:
	virtual void execute(GameEngine& engine, Field* field, Player& player) = 0;
	virtual Command* clone() const = 0;
	virtual ~Command() = default;
};

