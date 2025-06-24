#pragma once
#include "Card.h"
#include "String.h"
#include "Vector.hpp"

class CombinedCard : public Card
{
	void copyFrom(const CombinedCard& other);
	void moveFrom(CombinedCard&& other);
	void free();

protected:
	Vector<Card*> cards;

public:
	CombinedCard(const String& name);
	CombinedCard(const CombinedCard& other);
	CombinedCard(CombinedCard&& other) noexcept;
	CombinedCard& operator=(const CombinedCard& other);
	CombinedCard& operator=(CombinedCard&& other) noexcept;
	~CombinedCard();

	void addCard(const Card& card);

	void applyEffect(Player& player) const override;
	Card* clone() const override;
};
