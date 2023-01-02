#ifndef SHADOW_PRIEST_H
#define SHADOW_PRIEST_H
#include <string>
#include "Monster.h"
#include "../MapUnit.h"
#include "../Player/Player.h"

class ShadowPriest : public Monster
{
public:
    ShadowPriest(int x, int y);
    ~ShadowPriest();
    string get_monster_str() const override;
    void action(Player &p, MapUnit *map[][MAP_SIZE]) override;
};

#endif
