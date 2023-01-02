#ifndef WARLOCK_H
#define WARLOCK_H
#include <string>
#include "Monster.h"
#include "../Player/Player.h"
#include "Zombie.h"

class Warlock : public Monster
{
public:
    Warlock(int x, int y);
    ~Warlock();
    string get_monster_str() const override;
    void action(Player &p, MapUnit *map[][MAP_SIZE]) override;
};

#endif
