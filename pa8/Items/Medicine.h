#ifndef MEDICINE_H
#define MEDICINE_H
#include "Item.h"
#include <string>

class Medicine : public Item
{
public:
    Medicine(int x, int y);
    ~Medicine();
    void triggered_by(Player &p) override;
    string get_item_str() const override;
};

#endif
