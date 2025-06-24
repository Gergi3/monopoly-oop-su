#include "Card.h"
#include "CombinedCard.h"
#include "String.h"
#include "Vector.hpp"
#include <utility>

void CombinedCard::copyFrom(const CombinedCard& other)
{
	cards = Vector<Card*>(other.cards.getCapacity(), nullptr);
	for (size_t i = 0; i < other.cards.getSize(); i++)
	{
		cards[i] = other.cards[i]->clone();
	}
}

void CombinedCard::moveFrom(CombinedCard&& other)
{
	cards = std::move(other.cards);
}

void CombinedCard::free()
{
	for (size_t i = 0; i < cards.getSize(); i++)
	{
		delete cards[i];
	}
}

CombinedCard::CombinedCard(const String& name) : Card(name)
{}	

CombinedCard::CombinedCard(const CombinedCard& other) : Card(other)
{
	copyFrom(other);
}

CombinedCard::CombinedCard(CombinedCard&& other) noexcept : Card(std::move(other))
{
	moveFrom(std::move(other));
}

CombinedCard& CombinedCard::operator=(const CombinedCard& other)
{
	if (this != &other)
	{
		Card::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

CombinedCard& CombinedCard::operator=(CombinedCard&& other) noexcept
{
	if (this != &other)
	{
		Card::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

CombinedCard::~CombinedCard()
{
	free();
}

void CombinedCard::addCard(const Card& card)
{
	cards.push_back(card.clone());
}

void CombinedCard::applyEffect(Player& player) const
{
	for (size_t i = 0; i < cards.getSize(); i++)
	{
		cards[i]->applyEffect(player);
	}
}

Card* CombinedCard::clone() const
{
	return new CombinedCard(*this);
}
