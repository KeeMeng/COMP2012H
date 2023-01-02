#ifndef WALL_H
#define WALL_H
#include "Terrain.h"
#include <string>

class Wall : public Terrain
{
public:
    Wall(int x, int y);
    ~Wall();
    bool is_blocked() const override;
    string get_display_str() const override;
};

#endif