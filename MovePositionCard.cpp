#include "BoardUtilities.h"
#include "MovePositionCard.h"

MovePositionCard::MovePositionCard(const String& name, MovePositionType type, unsigned spaces) : Card(name), type(type), spaces(spaces)
{}

void MovePositionCard::applyEffect(Player& player) const
{
	const size_t total = BoardUtilities::ALL_FIELDS;

	switch (type)
	{
		case MovePositionType::Forward:
		{
			size_t newPos = (player.getBoardPos() + spaces) % total;
			player.setBoardPos(newPos);
			break;
		}
		case MovePositionType::Back:
		{
			size_t newPos = (player.getBoardPos() + total - (spaces % total)) % total;
			player.setBoardPos(newPos);
			break;
		}
		case MovePositionType::Goto:
		{
			size_t newPos = spaces % BoardUtilities::ALL_FIELDS;
			player.setBoardPos(newPos);
			break;
		}
		default:
			throw std::logic_error("Invalid card type!");
	}
}
