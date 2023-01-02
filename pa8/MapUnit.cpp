#include <string>
#include "MapUnit.h"
using namespace std;

void MapUnit::invalidate() { valid = false; }

MapUnit::MapUnit(int x_, int y_): x(x_), y(y_) {}
MapUnit::~MapUnit() {}
int MapUnit::get_x() const { return x; }
int MapUnit::get_y() const { return y; }
bool MapUnit::is_discovered() const { return discovered; }
void MapUnit::set_discovered() { discovered = true; }
bool MapUnit::is_valid() const { return valid; }
void MapUnit::triggered_by(Player& p) {}
int MapUnit::attacked_by(int atk) { return 0; }
