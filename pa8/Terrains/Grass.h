#ifndef GRASS_H
#define GRASS_H
#include "Terrain.h"
#include <string>

class Grass : public Terrain
{
public:
    Grass(int x, int y);
    ~Grass();
    bool is_blocked() const override ;
    string get_display_str() const override;
};

#endif
