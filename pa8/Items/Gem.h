#ifndef GEM_H
#define GEM_H
#include "Item.h"
#include <string>

enum GemType
{
    EMERALD,
    RUBY,
    SAPPHIRE
};

class Gem : public Item
{
private:
    GemType gtype;

public:
    Gem(int x, int y, GemType gem_type);
    ~Gem();
    void triggered_by(Player &p) override;
    string get_item_str() const override;
};

#endif
