#pragma once

namespace PlayerConstants
{
	// Ownership validation
	constexpr const char* NO_OWNER_ERR = "Property has no owner!";
	constexpr const char* ALREADY_OWNED_ERR = "Property already has an owner!";
	constexpr const char* NOT_OWNER_ERR = "You do not own this property!";
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
	constexpr const char* INVALID_SELL_PRICE_ERR = "Cannot sell a property for zero or negative price.";
	constexpr const char* INSUFFICIENT_BUYER_MONEY_ERR = "Buyer does not have enough money to purchase the property.";

	// Property purchasing
	constexpr const char* NOT_ENOUGH_OWNERSHIP_MONEY_ERR = "Not enough money to buy this property.";
}