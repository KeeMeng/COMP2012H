#ifndef BOOK_H
#define BOOK_H
#include "Item.h"
#include <string>

class Book : public Item
{
public:
    Book(int x, int y);
    ~Book();
    void triggered_by(Player &p) override;
    string get_item_str() const override;
};

#endif
