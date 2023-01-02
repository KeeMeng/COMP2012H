#ifndef TERREIN_H
#define TERREIN_H
#include "../MapUnit.h"

class Terrain : public MapUnit
{
public:
    Terrain(int x, int y);
    ~Terrain();
    UnitType get_unit_type() const override;
};

#endif
