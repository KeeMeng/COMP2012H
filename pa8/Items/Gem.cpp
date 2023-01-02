#include "Gem.h"

// implemented code
Gem::Gem(int x, int y, GemType gem_type): Item(x, y) {
	gtype = gem_type;
}

Gem::~Gem() {}

void Gem::triggered_by(Player& p) {
	if (is_valid()) {
		if (gtype == GemType::RUBY && p.get_role() == Role::WARRIOR) {
			p.charge_mp();
		} else if (gtype == GemType::EMERALD && p.get_role() == Role::ARCHER) {
			p.charge_mp();
		} else if (gtype == GemType::SAPPHIRE && p.get_role() == Role::MAGE) {
			p.charge_mp();
		}
		invalidate();
	}
}

string Gem::get_item_str() const {
	if (gtype == GemType::RUBY) {
		return SYM_RUBY;
	} else if (gtype == GemType::EMERALD) {
		return SYM_EMERALD;
	} else if (gtype == GemType::SAPPHIRE) {
		return SYM_SAPPHIRE;
	} else {
		return "";
	}
}
