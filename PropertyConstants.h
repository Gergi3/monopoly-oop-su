#pragma once

namespace PropertyConstants
{
	constexpr const char* NO_PROP_OWNER_ERR = "Property has no owner.";
	constexpr const char* ALREADY_OWNED_PROP_ERR = "Property is already owned.";
	constexpr const char* NOT_OWNED_ERR = "Property is not owned by the player.";
	constexpr const char* OWNED_ERR = "Property is already owned by the player.";

	constexpr const char* NULL_PLAYER_ERR = "Player can't be null.";
	constexpr const char* NOT_ENOUGH_HOUSE_MONEY_ERR = "Player does not have enough money to buy a house.";
	constexpr const char* NO_HOUSE_EXISTS_ERR = "There is no house owned on this property.";
	constexpr const char* SELL_PROPERTY_WHEN_HOUSES_PRESENT_ERR = "Cannot sell property while it has houses, you must first sell all houses of property.";
	
	constexpr const char* MAX_HOUSES_ERR = "Cannot buy more houses, maximum reached.";
}
