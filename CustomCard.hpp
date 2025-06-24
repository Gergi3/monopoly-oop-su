#pragma once
#include "Card.h"

template<typename Predicate>
class CustomCard : public Card
{
	Predicate effect;

public:
	CustomCard(const String& name, Predicate effect);

	void applyEffect(Player& player) const override;
	Card* clone() const override;
};

template<typename Predicate>
CustomCard<Predicate>::CustomCard(const String& name, Predicate effect) 
	: Card(name), effect(effect)
{}

template<typename Predicate>
void CustomCard<Predicate>::applyEffect(Player& player) const
{
	effect(player);
}

template<typename Predicate>
Card* CustomCard<Predicate>::clone() const
{
	return new CustomCard<Predicate>(*this);
}
