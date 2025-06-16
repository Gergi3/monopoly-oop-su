#pragma once
class Die
{
	mutable unsigned lastRoll;

public:
	explicit Die();
	unsigned roll() const;
	unsigned getLastRoll() const;
};

