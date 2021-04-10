#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "PlayerNode.hpp"

class VengPlayer {
public:
    char* Username;
    PlayerNode* pN;
    int Health;
    int Armor;

    int Ammo357;
    int AmmoBkshot;
    int Ammo9mm;
    int Ammo556mm;

    VengPlayer();
private:

};

#endif