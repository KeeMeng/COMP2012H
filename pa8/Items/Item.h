#ifndef ITEM_H
#define ITEM_H
#include "../MapUnit.h"
#include "../Player/Player.h"
#include <string>

class Item : public MapUnit
{
public:
    Item(int x, int y);
    virtual ~Item();
    UnitType get_unit_type() const override;
    bool is_blocked() const override;
    int attacked_by(int atk) override;
    string get_display_str() const override;
    virtual string get_item_str() const = 0;
};

#endif
