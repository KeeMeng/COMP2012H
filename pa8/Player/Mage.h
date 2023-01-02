#ifndef MAGE_H
#define MAGE_H
#include <string>
#include "Player.h"

class Mage : public Player
{
private:
    void level_up() override;

public:
    Mage(int x_, int y_, const string &name_);
    ~Mage();
    int get_range() const override;
    Role get_role() const override;
    int skill(int &atk_, int &range) override;
};

#endif
