#ifndef MONSTER_H
#define MONSTER_H
#include "../MapUnit.h"
#include "../Player/Player.h"
#include "../Terrains/EmptyLand.h"

class Monster : public MapUnit
{
private:
    bool active = false;

protected:
    int cur_hp, max_hp;
    int atk, def;

public:
    Monster(int x, int y);
    ~Monster();
    bool is_active() const;
    void set_active();
    void recover_hp(int hp);
    UnitType get_unit_type() const override;
    bool is_blocked() const override;
    string get_display_str() const override;
    int attacked_by(int atk_) override;
    void follow(const Player &p, MapUnit *map[][MAP_SIZE]);
    virtual string get_monster_str() const = 0;
    virtual void action(Player &p, MapUnit *map[][MAP_SIZE]) = 0;
};

#endif
