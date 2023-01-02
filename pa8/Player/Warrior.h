#ifndef WARRIOR_H
#define WARRIOR_H
#include <string>
#include "Player.h"

class Warrior : public Player
{
private:
    void level_up() override;

public:
    Warrior(int x_, int y_, const string &name_);
    ~Warrior();
    Role get_role() const override;
    int get_range() const override;
    int skill(int &atk, int &range) override;
    void attacked_by(int atk_) override;
};

#endif
