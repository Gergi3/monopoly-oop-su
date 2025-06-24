#pragma once

namespace PlayerConstants
{
	// Ownership validation
	constexpr const char* NO_PROP_OWNER_ERR = "Property has no owner!";
	constexpr const char* ALREADY_OWNED_PROP_ERR = "Property already has an owner!";
	constexpr const char* NOT_OWNER_ERR = "You do not own this ";
	constexpr const char* SELL_PROPERTY_TO_SELF_ERR = "You cannot sell a property to yourself.";
	constexpr const char* PAY_RENT_TO_SELF_ERR = "You cannot pay rent to yourself.";

	// House building
	constexpr const char* HOUSE_BUILD_WHILE_NO_FULL_GROUP_ERR = "You must own all properties in the color group to build a house.";
	constexpr const char* CANT_BUILD_HOUSE_ERR = "Cannot build a house on this property due to uneven development.";
	constexpr const char* MAXIMUM_HOUSES_REACHED_ERR = "This property already has the maximum number of houses.";
	constexpr const char* NOT_ENOUGH_HOUSE_MONEY_ERR = "Not enough money to build a house.";

	// House demolishing
	constexpr const char* HOUSE_DEMOLISH_WHILE_NO_FULL_GROUP_ERR = "You must own the full color group to demolish a house.";
	constexpr const char* NO_HOUSES_TO_DEMOLISH_ERR = "This property has no houses to demolish.";
	constexpr const char* CANT_DEMOLISH_HOUSE_ERR = "Cannot demolish a house on this property due to uneven development.";

	// Property selling
	constexpr const char* PROPERTY_SELL_WHILE_HOUSES_PRESENT_ERR = "You cannot sell a property while houses exist in its color group.";
	constexpr const char* INVALID_PROP_SELL_PRICE_ERR = "Cannot sell a property for zero or negative price.";
	constexpr const char* INSUFFICIENT_PROP_BUYER_MONEY_ERR = "Buyer does not have enough money to purchase the property.";

	// Property purchasing
	constexpr const char* NOT_ENOUGH_OWNERSHIP_MONEY_ERR = "Not enough money to buy this!";

	// Railroad
	constexpr const char* RAILROAD_ALREADY_OWNED_ERR = "Railroad already has an owner!";
	constexpr const char* NOT_RAILROAD_OWNER_ERR = "You do not own this railroad!";
	constexpr const char* SELL_RAILROAD_TO_SELF_ERR = "You cannot sell a railroad to yourself.";
	constexpr const char* INVALID_RAILROAD_SELL_PRICE_ERR = "Cannot sell a railroad for zero or negative price.";
	constexpr const char* INSUFFICIENT_RAILROAD_BUYER_MONEY_ERR = "Buyer does not have enough money to purchase the railroad.";

	// Utility
	constexpr const char* UTILITY_ALREADY_OWNED_ERR = "Utility already has an owner!";
	constexpr const char* NOT_UTILITY_OWNER_ERR = "You do not own this property!";
	constexpr const char* SELL_UTILITY_TO_SELF_ERR = "You cannot sell a utility to yourself.";
	constexpr const char* INVALID_UTILITY_SELL_PRICE_ERR = "Cannot sell a utility for zero or negative price.";
	constexpr const char* INSUFFICIENT_UTILITY_BUYER_MONEY_ERR = "Buyer does not have enough money to purchase the utility.";
}