#pragma once
#include "Bank.h"
#include "Card.h"
#include "DeckType.h"
#include "Queue.hpp"
#include <memory>

class Player;

class Deck
{
	MoveQueue<std::unique_ptr<Card>> cards;

	void initializeCommunityDeck(Bank& bank);
	void initializeChanceDeck(Bank& bank);

public:
	Deck(DeckType deckType, Bank& bank);

	const Card* drawCard();
};

