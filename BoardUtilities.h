#pragma once
#include "ColorGroup.h"
#include "String.h"
#include "Vector.hpp"

namespace BoardUtilities
{
	constexpr size_t FIELDS_PER_SIDE = 11;
	constexpr size_t ALL_FIELDS = FIELDS_PER_SIDE * 4 - 4;

	constexpr size_t GO_POS = 0;
	constexpr size_t READING_RAILROAD_POS = 5;
	constexpr size_t ST_CHARLES_POS = 11;
	constexpr size_t ILLINOIS_POS = 24;
	constexpr size_t BOARDWALK_POS = 39;

	struct TaxFieldData
	{
		String name = "";
		size_t boardPos = 0;
		int tax = 0;
	};

	struct TextFieldData
	{
		String name = "";
		size_t boardPos = 0;
	};

	struct CardFieldData
	{
		String name = "";
		size_t boardPos = 0;
	};

	struct UtilityData
	{
		String name = "";
		size_t boardPos = 0;
		int price = 150;
	};

	struct RailroadData
	{
		String name = "";
		size_t boardPos = 0;
		int price = 200;
	};

	struct PropertyData
	{
		String name = "";
		size_t boardPos = 0;
		int price = 0;
		int housePrice = 0;
		Vector<int> rentTable;
		ColorGroup colorGroup = ColorGroup::Blue;
	};

	inline Vector<size_t> getUtilityPositions()
	{
		Vector<size_t> v;
		v.push_back(12);
		v.push_back(28);
		return v;
	}

	inline Vector<size_t> getRailroadPositions()
	{
		Vector<size_t> v;
		v.push_back(5);
		v.push_back(15);
		v.push_back(25);
		v.push_back(35);
		return v;
	}

	static const Vector<size_t> RAILROAD_POSITIONS = getRailroadPositions();
	static const Vector<size_t> UTILITY_POSITIONS = getUtilityPositions();

	inline Vector<int> makeRentTable(const int* rents, size_t count)
	{
		Vector<int> v;
		for (size_t i = 0; i < count; i++)
		{
			v.push_back(rents[i]);
		}
		return v;
	}

	inline void addBrownProperties(Vector<PropertyData>& props)
	{
		int rents1[] = { 2, 10, 30, 90, 160, 250 };
		int rents2[] = { 4, 20, 60, 180, 320, 450 };
		props.push_back(PropertyData{ "Mediterranean Avenue", 1, 60, 50, makeRentTable(rents1, 6), ColorGroup::LightYellow });
		props.push_back(PropertyData{ "Baltic Avenue", 3, 60, 50, makeRentTable(rents2, 6), ColorGroup::LightYellow });
	}

	inline void addLightBlueProperties(Vector<PropertyData>& props)
	{
		int rents1[] = { 6, 30, 90, 270, 400, 550 };
		int rents2[] = { 8, 40, 100, 300, 450, 600 };
		props.push_back(PropertyData{ "Oriental Avenue", 6, 100, 50, makeRentTable(rents1, 6), ColorGroup::LightBlue });
		props.push_back(PropertyData{ "Vermont Avenue", 8, 100, 50, makeRentTable(rents1, 6), ColorGroup::LightBlue });
		props.push_back(PropertyData{ "Connecticut Avenue", 9, 120, 50, makeRentTable(rents2, 6), ColorGroup::LightBlue });
	}

	inline void addPinkProperties(Vector<PropertyData>& props)
	{
		int rents1[] = { 10, 50, 150, 450, 625, 750 };
		int rents2[] = { 12, 60, 180, 500, 700, 900 };
		props.push_back(PropertyData{ "St. Charles Place", ST_CHARLES_POS, 140, 100, makeRentTable(rents1, 6), ColorGroup::Pink });
		props.push_back(PropertyData{ "States Avenue", 13, 140, 100, makeRentTable(rents1, 6), ColorGroup::Pink });
		props.push_back(PropertyData{ "Virginia Avenue", 14, 160, 100, makeRentTable(rents2, 6), ColorGroup::Pink });
	}

	inline void addOrangeProperties(Vector<PropertyData>& props)
	{
		int rents1[] = { 14, 70, 200, 550, 750, 950 };
		int rents2[] = { 16, 80, 220, 600, 800, 1000 };
		props.push_back(PropertyData{ "St. James Place", 16, 180, 100, makeRentTable(rents1, 6), ColorGroup::Orange });
		props.push_back(PropertyData{ "Tennessee Avenue", 18, 180, 100, makeRentTable(rents1, 6), ColorGroup::Orange });
		props.push_back(PropertyData{ "New York Avenue", 19, 200, 100, makeRentTable(rents2, 6), ColorGroup::Orange });
	}

	inline void addRedProperties(Vector<PropertyData>& props)
	{
		int rents1[] = { 18, 90, 250, 700, 875, 1050 };
		int rents2[] = { 20, 100, 300, 750, 925, 1100 };
		props.push_back(PropertyData{ "Kentucky Avenue", 21, 220, 150, makeRentTable(rents1, 6), ColorGroup::Red });
		props.push_back(PropertyData{ "Indiana Avenue", 23, 220, 150, makeRentTable(rents1, 6), ColorGroup::Red });
		props.push_back(PropertyData{ "Illinois Avenue", ILLINOIS_POS, 240, 150, makeRentTable(rents2, 6), ColorGroup::Red });
	}

	inline void addYellowProperties(Vector<PropertyData>& props)
	{
		int rents1[] = { 22, 110, 330, 800, 975, 1150 };
		int rents2[] = { 24, 120, 360, 850, 1025, 1200 };
		props.push_back(PropertyData{ "Atlantic Avenue", 26, 260, 150, makeRentTable(rents1, 6), ColorGroup::Yellow });
		props.push_back(PropertyData{ "Ventnor Avenue", 27, 260, 150, makeRentTable(rents1, 6), ColorGroup::Yellow });
		props.push_back(PropertyData{ "Marvin Gardens", 29, 280, 150, makeRentTable(rents2, 6), ColorGroup::Yellow });
	}

	inline void addGreenProperties(Vector<PropertyData>& props)
	{
		int rents1[] = { 26, 130, 390, 900, 1100, 1275 };
		int rents2[] = { 28, 150, 450, 1000, 1200, 1400 };
		props.push_back(PropertyData{ "Pacific Avenue", 31, 300, 200, makeRentTable(rents1, 6), ColorGroup::Green });
		props.push_back(PropertyData{ "North Carolina Ave", 32, 300, 200, makeRentTable(rents1, 6), ColorGroup::Green });
		props.push_back(PropertyData{ "Pennsylvania Avenue", 34, 320, 200, makeRentTable(rents2, 6), ColorGroup::Green });
	}

	inline void addBlueProperties(Vector<PropertyData>& props)
	{
		int rents1[] = { 35, 175, 500, 1100, 1300, 1500 };
		int rents2[] = { 50, 200, 600, 1400, 1700, 2000 };
		props.push_back(PropertyData{ "Park Place", 37, 350, 200, makeRentTable(rents1, 6), ColorGroup::Blue });
		props.push_back(PropertyData{ "Boardwalk", BOARDWALK_POS, 400, 200, makeRentTable(rents2, 6), ColorGroup::Blue });
	}

	inline Vector<PropertyData> getPropertiesData()
	{
		Vector<PropertyData> props;

		addBrownProperties(props);
		addLightBlueProperties(props);
		addPinkProperties(props);
		addOrangeProperties(props);
		addRedProperties(props);
		addYellowProperties(props);
		addGreenProperties(props);
		addBlueProperties(props);

		return props;
	}

	inline Vector<RailroadData> getRailroadsData()
	{
		Vector<RailroadData> railroads;

		railroads.push_back({ "Reading Railroad", RAILROAD_POSITIONS[0]});
		railroads.push_back({ "Pennsylvania Railroad", RAILROAD_POSITIONS[1] });
		railroads.push_back({ "B&O Railroad", RAILROAD_POSITIONS[2] });
		railroads.push_back({ "Short Line", RAILROAD_POSITIONS[3] });

		return railroads;
	}

	inline Vector<UtilityData> getUtilityData()
	{
		Vector<UtilityData> utilities;

		utilities.push_back({ "Electric Company", UTILITY_POSITIONS[0]});
		utilities.push_back({ "Water Works", UTILITY_POSITIONS[1]});

		return utilities;
	}

	inline Vector<CardFieldData> getCommunityDeckData()
	{
		Vector<CardFieldData> cardFieldData;

		cardFieldData.push_back({ "Community Chest", 2 });
		cardFieldData.push_back({ "Community Chest", 17 });
		cardFieldData.push_back({ "Community Chest", 33 });

		return cardFieldData;
	}

	inline Vector<CardFieldData> getChanceDeckData()
	{
		Vector<CardFieldData> cardFieldData;

		cardFieldData.push_back({ "Draw Chance", 7 });
		cardFieldData.push_back({ "Draw Chance", 22 });
		cardFieldData.push_back({ "Draw Chance", 36 });

		return cardFieldData;
	}

	inline Vector<TextFieldData> getCornerFieldsData()
	{
		Vector<TextFieldData> textFieldData;

		textFieldData.push_back({ "Go!", 0 });
		textFieldData.push_back({ "Just Visiting!", 10 });
		textFieldData.push_back({ "Free Parking!", 20 });
		textFieldData.push_back({ "Jail!", 30 });

		return textFieldData;
	}

	inline Vector<TaxFieldData> getTaxFieldsData()
	{
		Vector<TaxFieldData> textFieldData;

		textFieldData.push_back({ "Income Tax!", 4, 200 });
		textFieldData.push_back({ "Super Tax!", 38, 100 });

		return textFieldData;
	}

}