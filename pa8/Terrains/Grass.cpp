#include "Grass.h"

// implemented code
Grass::Grass(int x, int y): Terrain(x, y) {}

Grass::~Grass() {}

bool Grass::is_blocked() const {
	return false;
}

string Grass::get_display_str() const {
	return SYM_GRASS;
}
