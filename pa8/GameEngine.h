#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <cmath>
#include <iostream>
#include <limits>
#include "GameUI.h"
#include "MapUnit.h"
#include "Terrains/Terrain.h"
#include "Terrains/Wall.h"
#include "Terrains/Grass.h"
#include "Terrains/EmptyLand.h"
#include "Items/Item.h"
#include "Items/Gem.h"
#include "Items/Book.h"
#include "Items/Medicine.h"
#include "Monsters/Monster.h"
#include "Monsters/Zombie.h"
#include "Monsters/Warlock.h"
#include "Monsters/ShadowPriest.h"
#include "Player/Player.h"
#include "Player/Mage.h"
#include "Player/Warrior.h"
#include "Player/Archer.h"

struct MonsterNode
{
    Monster *data;
    MonsterNode *next;
};

class GameEngine
{
private:
    MapUnit *map[MAP_SIZE][MAP_SIZE];
    MonsterNode *head = nullptr;
    Player *player;
    GameUI ui;

    char input();

    void create_player(int x, int y, const string &name, Role role);
    void activate_monster(Monster *monster);
    void activate_monsters();
    void deactivate_monster(Monster const *const monster);
    void player_move(Direction d);
    void player_discover();
    void player_attack();
    void player_skill();
    void monster_follow();
    void monster_act();
    void print_active_monsters();
    bool player_win() const;

public:
    GameEngine();
    ~GameEngine();
    void run();
};

#endif
