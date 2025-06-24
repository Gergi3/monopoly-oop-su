#pragma once
#include "Tile.h"

class Tileable
{
public:
	virtual ~Tileable() = default;
	virtual Tile toTile() const = 0;
};