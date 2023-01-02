#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <limits>
using namespace std;

const int MAX_ATK = numeric_limits<int>::max();

enum Role
{
    WARRIOR,
    ARCHER,
    MAGE
};

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player
{
private:
    // coordinates
    int x, y;
    // user defined nickname
    string name;
    // current direction
    Direction cur_dir = Direction::UP;
    virtual void level_up() = 0;

protected:
    // attack and defence
    int atk, def;
    // current and max health point
    int cur_hp, max_hp;
    // current and max mana point
    int cur_mp = 3, max_mp = 3;
    // current and max experience point
    int cur_exp = 0, max_exp = 8;
    // current level
    int level = 1;

public:
    Player(int x_, int y_, const string &name_);
    virtual ~Player();
    string get_name() const;
    Direction get_direction() const;
    string get_display_str() const;

    void get_position(int &x_, int &y_) const;
    void get_atk_def(int &atk_, int &def_) const;
    void get_hp(int &cur, int &max) const;
    void get_mp(int &cur, int &max) const;
    void get_exp(int &cur, int &max) const;
    int get_level() const;
    bool is_alive() const;
    void move(Direction d, int step);
    void recover_hp(int hp);
    void charge_mp();
    void gain_exp(int exp);

    virtual void attacked_by(int atk_);
    virtual Role get_role() const = 0;

    // role specific attack range
    virtual int get_range() const = 0;

    // role specific skill
    // if skill are succesfully used, return 0
    // attack of the skill will be stored in atk_,
    // and the range of that attack will be stored in range
    // if no skill is used, (role is warrior or MP is not enough), return 1
    virtual int skill(int &atk_, int &range) = 0;
};

#endif
