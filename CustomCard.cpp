#include "CustomCard.h"

void CustomCard::applyEffect(Player& player) const
{
	effect(player);
}

Card* CustomCard::clone() const
{
	return new CustomCard(*this);
}
