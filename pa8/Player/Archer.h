#ifndef ARCHER_H
#define ARCHER_H
#include <string>
#include "Player.h"

class Archer : public Player
{
private:
    void level_up() override;

public:
    Archer(int x_, int y_, const string &name_);
    ~Archer();
    int get_range() const override;
    int skill(int &atk, int &range) override;
    Role get_role() const override;
};

#endif
