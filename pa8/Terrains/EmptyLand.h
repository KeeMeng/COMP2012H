#ifndef EMPTY_LAND_H
#define EMPTY_LAND_H
#include "Terrain.h"
#include <string>

class EmptyLand : public Terrain
{
public:
    EmptyLand(int x, int y);
    ~EmptyLand();
    bool is_blocked() const override;
    string get_display_str() const override;
};

#endif
