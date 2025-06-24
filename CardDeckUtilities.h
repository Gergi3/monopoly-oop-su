#pragma once

namespace CardDeckUtilities
{
		constexpr size_t CARDS = 11;

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
			props.push_back(PropertyData{ "St. Charles Place", 11, 140, 100, makeRentTable(rents1, 6), ColorGroup::Pink });
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
			props.push_back(PropertyData{ "Illinois Avenue", 24, 240, 150, makeRentTable(rents2, 6), ColorGroup::Red });
		}

		inline void addYellowProperties(Vector<PropertyData>& props)
		{
			int rents1[] = { 22, 110, 330, 800, 975, 1150 };
			int rents2[] = { 24, 120, 360, 850, 1025, 1200 };
			props.push_back(PropertyData{ "Atlantic Avenue", 26, 260, 150, makeRentTable(rents1, 6), ColorGroup::Yellow });
			props.push_back(PropertyData{ "Ventnor Avenue", 27, 260, 150, makeRentTable(rents1, 6), ColorGroup::Yellow });
			props.push_back(PropertyData{ "Marvin Gardens", 29, 280, 150, makeRentTable(rents2, 6), ColorGroup::Yellow });
		}

		inline void makeGreenProperties(Vector<PropertyData>& props)
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
			props.push_back(PropertyData{ "Boardwalk", 39, 400, 200, makeRentTable(rents2, 6), ColorGroup::Blue });
		}
}