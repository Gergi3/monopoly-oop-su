#include "BoardUtilities.h"
#include "Card.h"
#include "CustomCard.hpp"
#include "Deck.h"
#include "MovePositionCard.h"
#include "MovePositionToNearestCard.h"
#include "PaymentCard.h"
#include "Player.h"
#include "Queue.hpp"
#include <memory>
#include <utility>

static void getOutOfJailFunc(Player& player)
{
	player.incrementJailPasses();
}

static void goToJailFunc(Player& player)
{
	player.putInJail();
}

void Deck::initializeCommunityDeck(Bank& bank)
{
	cards.enqueue(std::make_unique<MovePositionCard>("Advance to Go", MovePositionType::Goto, 0));
	cards.enqueue(std::make_unique<PaymentCard>("Bank error in your favor! (+200$)", PaymentType::Recieve, 200, bank));
	cards.enqueue(std::make_unique<PaymentCard>("Doctor's fees! (-50$)", PaymentType::Pay, 50, bank));
	cards.enqueue(std::make_unique<CustomCard<void(*)(Player&)>>("Get out of Jail Free!", getOutOfJailFunc));
	cards.enqueue(std::make_unique<CustomCard<void(*)(Player&)>>("Go to Jail!", goToJailFunc));
	cards.enqueue(std::make_unique<PaymentCard>("Holiday Fund matures! (+100$)", PaymentType::Recieve, 100, bank));
	cards.enqueue(std::make_unique<PaymentCard>("Income tax refund! (+20$)", PaymentType::Recieve, 20, bank));
	cards.enqueue(std::make_unique<PaymentCard>("Life insurance matures! (+100$)", PaymentType::Recieve, 100, bank));
	cards.enqueue(std::make_unique<PaymentCard>("Hospital fees! (-100$)", PaymentType::Pay, 100, bank));
	cards.enqueue(std::make_unique<PaymentCard>("School fees! (-50$)", PaymentType::Pay, 50, bank));
	cards.enqueue(std::make_unique<PaymentCard>("You have won second prize in a beauty contest! (+10$)", PaymentType::Recieve, 10, bank));
	cards.enqueue(std::make_unique<PaymentCard>("You inherit! (+100$)", PaymentType::Recieve, 50, bank));
}

void Deck::initializeChanceDeck(Bank& bank)
{
	cards.enqueue(std::make_unique<MovePositionCard>("Go back 1 space", MovePositionType::Back, 1));
	cards.enqueue(std::make_unique<MovePositionCard>("Go back 2 spaces", MovePositionType::Back, 2));
	cards.enqueue(std::make_unique<MovePositionCard>("Go back 4 spaces", MovePositionType::Back, 4));
	cards.enqueue(std::make_unique<MovePositionCard>("Go back 5 spaces", MovePositionType::Back, 5));
	cards.enqueue(std::make_unique<MovePositionCard>("Go forward 1 space", MovePositionType::Forward, 1));
	cards.enqueue(std::make_unique<MovePositionCard>("Go forward 2 spaces", MovePositionType::Forward, 2));
	cards.enqueue(std::make_unique<MovePositionCard>("Go forward 4 spaces", MovePositionType::Forward, 4));
	cards.enqueue(std::make_unique<MovePositionCard>("Go forward 5 spaces", MovePositionType::Forward, 5));
	cards.enqueue(std::make_unique<MovePositionCard>("Advance to Go", MovePositionType::Goto, 0));
	cards.enqueue(std::make_unique<MovePositionCard>("Advance to Illinois Ave.", MovePositionType::Goto, BoardUtilities::ILLINOIS_POS));
	cards.enqueue(std::make_unique<MovePositionCard>("Advance to St.Charles Place", MovePositionType::Goto, BoardUtilities::ST_CHARLES_POS));
	cards.enqueue(std::make_unique<MovePositionCard>("Advance to Boardwalk", MovePositionType::Goto, BoardUtilities::BOARDWALK_POS));
	cards.enqueue(std::make_unique<MovePositionCard>("Take a trip to Reading Railroad", MovePositionType::Goto, BoardUtilities::READING_RAILROAD_POS));
	cards.enqueue(std::make_unique<MovePositionToNearestCard>("Advance to nearest Utility", BoardUtilities::UTILITY_POSITIONS));
	cards.enqueue(std::make_unique<MovePositionToNearestCard>("Advance to nearest Railroad", BoardUtilities::RAILROAD_POSITIONS));
	cards.enqueue(std::make_unique<MovePositionToNearestCard>("Advance to nearest Railroad", BoardUtilities::RAILROAD_POSITIONS));
	cards.enqueue(std::make_unique<PaymentCard>("Bank pays you dividend! (+50$)", PaymentType::Recieve, 50, bank));
	cards.enqueue(std::make_unique<PaymentCard>("Pay poor tax! (-15$)", PaymentType::Pay, 15, bank));
	cards.enqueue(std::make_unique<PaymentCard>("Your building loan matures! (+15$)", PaymentType::Recieve, 150, bank));
	cards.enqueue(std::make_unique<CustomCard<void(*)(Player&)>>("Get out of Jail Free!", getOutOfJailFunc));
	cards.enqueue(std::make_unique<CustomCard<void(*)(Player&)>>("Go to Jail!", goToJailFunc));
}

Deck::Deck(DeckType deckType, Bank& bank)
{
	if (deckType == DeckType::Chance)
	{
		initializeChanceDeck(bank);
	}
	else if (deckType == DeckType::Community)
	{
		initializeCommunityDeck(bank);
	}
	cards.shuffle();
}

const Card* Deck::drawCard()
{
	std::unique_ptr<Card> card = std::move(cards.peek());
	cards.dequeue();
	cards.enqueue(std::move(card));
	return cards.peekBack().get();
}
