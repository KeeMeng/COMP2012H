#ifndef UI_H
#define UI_H
#include "Player/Player.h"
#include "MapUnit.h"
#include <iostream>
#include <string>

using namespace std;

const int UI_WIDTH = 80;   // Width of all interface
const int MAP_HEIGHT = 16; // Height of the main interface

const string NAME_STR = "Name: ";
const string ROLE_STR = "Role: ";
const string HP_STR = "Health     Point: ";
const string ATK_STR = "Attack Point: ";
const string DFS_STR = "Defence Point: ";
const string WPC_STR = "Mana       Point: ";
const string LVL_STR = "Level: ";
const string EXP_STR = "Experience Point: ";
const int MAX_DIGITS = 4;

// component of boundary of map interface
const string LIGHT_HORIZONTAL = " ";
const string LIGHT_VERTICAL = " ";
const string ARC_TOP_LEFT = " ";
const string ARC_TOP_RIGHT = " ";
const string ARC_BOTTOM_LEFT = " ";
const string ARC_BOTTOM_RIGHT = " ";
const string CROSS = " ";
const string VERTICAL_RIGHT = " ";
const string VERTICAL_LEFT = " ";
const string HORIZONTAL_DOWN = " ";
const string HORIZONTAL_UP = " ";

class GameUI
{
private:
    string status_lines[4];
    string map_lines[MAP_HEIGHT];
    string info_lines[4];
    string format_status_column(const string &prefix, const string &value);
    string format_status_string(const string &lvalue, const string &rvalue);
    void refresh_status(Player &p);
    void show_borderline() const;
    void show_status() const;
    void refresh_map(MapUnit *map[][MAP_SIZE], Player &p);
    void show_map() const;
    void show_control() const;
    void clear() const;

public:
    void refresh(MapUnit *map[][MAP_SIZE], Player &p);
    GameUI(){};
    ~GameUI(){};
};

#endif
