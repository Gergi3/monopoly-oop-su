#pragma once
#include "Tile.h"

class ITileable
{
public:
	virtual ~ITileable() = default;
	virtual Tile toTile() const = 0;
};