#pragma once
#include "Player.h"
#include <memory>

class PlayerFactory
{
public:
    static Player* createPlayer()
    {
        return new Player();
    }
};