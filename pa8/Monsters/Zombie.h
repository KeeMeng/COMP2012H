#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <string>
#include "Monster.h"
#include "../Player/Player.h"


class Zombie : public Monster
{
public:
    Zombie(int x, int y);
    ~Zombie();
    string get_monster_str() const override;
    void action(Player &p, MapUnit *map[][MAP_SIZE]) override;
};

#endif
