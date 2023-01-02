#ifndef MAP_UNIT_H
#define MAP_UNIT_H
#include <string>
#include "Player/Player.h"
using namespace std;

const string SYM_EMPTY = "   "; //Display string for EmptyLand units
const string SYM_GRASS = "~~~"; //Display string for Grass units
const string SYM_WALL = "###"; //Display string for Wall units
const string SYM_DANGER = "!!!"; //Display string for undiscovered Monster units
const string SYM_ITEM = "???"; //Display string for undiscovered Item units
const string SYM_EMERALD = "EMR"; //Display string for discovered Emerald Gem units
const string SYM_SAPPHIRE = "SPR"; //Display string for discovered Sapphire Gem units
const string SYM_RUBY = "RBY"; //Display string for discovered Ruby Gem units
const string SYM_BOOK = " BK"; //Display string for discovered Book units
const string SYM_MEDICINE = "+++"; //Display string for discovered Medicine units
const int MAP_SIZE = 20; //Size of the game map

enum UnitType
{
    ITEM,
    MONSTER,
    TERRAIN
};

class MapUnit
{
private:
    bool valid = true;
    bool discovered = false;

protected:
    int x, y;
    void invalidate();

public:
    MapUnit(int x_, int y_);
    virtual ~MapUnit();
    int get_x() const;
    int get_y() const;
    bool is_discovered() const;
    void set_discovered();
    bool is_valid() const;
    virtual void triggered_by(Player &p);
    virtual int attacked_by(int atk);
    virtual UnitType get_unit_type() const = 0;
    virtual bool is_blocked() const = 0;
    virtual string get_display_str() const = 0;
};

#endif
